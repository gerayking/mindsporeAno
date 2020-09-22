/**
 * This is the C++ adaptation and derivative work of Myia (https://github.com/mila-iqia/myia/).
 *
 * Copyright 2019 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "vm/transform.h"

#include <algorithm>
#include <map>
#include <queue>
#include <stack>
#include <set>
#include <string>
#include <vector>

#include "abstract/abstract_value.h"
#ifdef ENABLE_GE
#include "transform/graph_ir/convert.h"
#endif
#include "ir/graph_utils.h"
#include "utils/ms_context.h"
#include "debug/trace.h"
#include "debug/anf_ir_dump.h"

namespace mindspore {
namespace compile {
using mindspore::abstract::AbstractFunction;
using mindspore::abstract::AbstractFunctionPtr;
using PrimTypePair = std::pair<PrimitivePtr, AbstractFunctionPtr>;
using MapPrimTypeFuncGraph = std::map<PrimTypePair, FuncGraphPtr>;
using TypedPrimitiveAbstractClosurePtr = std::shared_ptr<abstract::TypedPrimitiveAbstractClosure>;

std::vector<PrimitivePtr> nonlinear_ops = {prim::kPrimReturn, prim::kPrimPartial, prim::kPrimSwitch,
                                           prim::kPrimMakeTuple, prim::kPrimBpropCut};
const std::vector<PrimitivePtr> &GetMsNonlinearOps() {
  static const std::vector<PrimitivePtr> ms_nonlinear_ops = {prim::kPrimReturn,   prim::kPrimPartial,
                                                             prim::kPrimSwitch,   prim::kPrimMakeTuple,
                                                             prim::kPrimBpropCut, prim::kPrimSwitchLayer};
  return ms_nonlinear_ops;
}

namespace {
bool ContainMultiTarget(const std::vector<AnfNodePtr> &nodes) {
  auto context_ptr = MsContext::GetInstance();
  MS_EXCEPTION_IF_NULL(context_ptr);
  std::string last_target = context_ptr->device_target();
  for (auto &node : nodes) {
    if (node->isa<CNode>()) {
      std::string cur_target = GetCNodeTarget(node);
      if (last_target != cur_target) {
        return true;
      }
      last_target = cur_target;
    }
  }
  return false;
}

bool ExtractNodes(const FuncGraphPtr &graph, const AnfNodePtr &prior_node, const AnfNodePtr &behind_node,
                  std::vector<AnfNodePtr> *prior_nodes, std::vector<AnfNodePtr> *depend_nodes) {
  MS_EXCEPTION_IF_NULL(prior_node);
  MS_EXCEPTION_IF_NULL(behind_node);
  MS_EXCEPTION_IF_NULL(graph);
  auto manager = graph->manager();
  MS_EXCEPTION_IF_NULL(manager);
  auto &node_users = manager->node_users();
  if (prior_node->isa<Parameter>()) {
    for (auto &user : node_users[prior_node]) {
      auto cnode = user.first->cast<CNodePtr>();
      MS_EXCEPTION_IF_NULL(cnode);
      if (!IsPrimitiveCNode(cnode, prim::kPrimControlDepend)) {
        prior_nodes->emplace_back(cnode);
      }
    }
  } else if (!IsPrimitiveCNode(prior_node, prim::kPrimControlDepend)) {
    prior_nodes->emplace_back(prior_node);
  } else {
    return false;
  }
  if (behind_node->isa<Parameter>()) {
    for (auto &user : node_users[behind_node]) {
      auto cnode = user.first->cast<CNodePtr>();
      MS_EXCEPTION_IF_NULL(cnode);
      if (!IsPrimitiveCNode(cnode, prim::kPrimControlDepend)) {
        depend_nodes->emplace_back(cnode);
      }
    }
  } else if (!IsPrimitiveCNode(behind_node, prim::kPrimControlDepend)) {
    depend_nodes->emplace_back(behind_node);
  } else {
    return false;
  }
  return true;
}

void AddControlEdge(const FuncGraphPtr &graph, const AnfNodePtr &node,
                    std::map<AnfNodePtr, std::vector<AnfNodePtr>> *control_edges,
                    std::map<AnfNodePtr, size_t> *nodes_ref) {
  MS_EXCEPTION_IF_NULL(node);
  auto input_cnode = node->cast<CNodePtr>();
  MS_EXCEPTION_IF_NULL(input_cnode);
  auto prior_node = input_cnode->input(kControlDependPriorIndex);
  auto depend_node = input_cnode->input(kControlDependBehindIndex);
  MS_EXCEPTION_IF_NULL(prior_node);
  MS_EXCEPTION_IF_NULL(depend_node);
  PrimitivePtr prim_ptr = GetValueNode<PrimitivePtr>(input_cnode->input(0));
  MS_EXCEPTION_IF_NULL(prim_ptr);
  ValuePtr mode_ptr = prim_ptr->GetAttr("depend_mode");
  int depend_mode = 0;
  if (mode_ptr != nullptr) {
    depend_mode = GetValue<int>(mode_ptr);
  }
  if ((prior_node->isa<Parameter>() || depend_node->isa<Parameter>()) && depend_mode == 0) {
    return;
  }
  std::vector<AnfNodePtr> prior_nodes;
  std::vector<AnfNodePtr> behind_nodes;
  if (!ExtractNodes(graph, prior_node, depend_node, &prior_nodes, &behind_nodes)) {
    return;
  }
  for (auto &first_node : prior_nodes) {
    for (auto &second_node : behind_nodes) {
      MS_EXCEPTION_IF_NULL(first_node);
      MS_EXCEPTION_IF_NULL(second_node);
      auto iter = control_edges->find(second_node);
      if (iter == control_edges->end()) {
        (void)control_edges->insert(
          std::pair<AnfNodePtr, std::vector<AnfNodePtr>>(second_node, std::vector<AnfNodePtr>{first_node}));
      } else {
        iter->second.emplace_back(first_node);
      }
      auto ref_iter = nodes_ref->find(first_node);
      if (ref_iter != nodes_ref->end()) {
        ref_iter->second++;
      } else {
        (void)nodes_ref->insert(std::pair<AnfNodePtr, size_t>(first_node, 1));
      }
    }
  }
}

void CalcNodeRefCount(const FuncGraphPtr &graph, std::map<AnfNodePtr, size_t> *nodes_ref,
                      std::map<AnfNodePtr, std::vector<AnfNodePtr>> *control_edges) {
  std::queue<AnfNodePtr> queue;
  queue.push(graph->get_return());
  std::set<AnfNodePtr> visited;
  while (!queue.empty()) {
    auto &node = queue.front();
    queue.pop();
    MS_EXCEPTION_IF_NULL(node);
    if (!node->isa<CNode>()) {
      continue;
    }
    auto cnode = node->cast<CNodePtr>();
    MS_EXCEPTION_IF_NULL(cnode);
    for (auto &input : cnode->inputs()) {
      if (IsPrimitiveCNode(input, prim::kPrimControlDepend)) {
        AddControlEdge(graph, input, control_edges, nodes_ref);
      }
      auto iter = nodes_ref->find(input);
      if (iter != nodes_ref->end()) {
        iter->second++;
      } else {
        (void)nodes_ref->insert(std::pair<AnfNodePtr, size_t>(input, 1));
      }
      if (visited.find(input) != visited.end()) {
        continue;
      }
      visited.insert(input);
      queue.push(input);
    }
  }
}

std::vector<AnfNodePtr> OptimizeGetItemOrder(const std::vector<AnfNodePtr> &nodes) {
  std::vector<AnfNodePtr> result;
  std::map<size_t, std::vector<AnfNodePtr>> insert_positions;
  std::map<AnfNodePtr, size_t> node_positions;
  for (auto &node : nodes) {
    if (node->isa<CNode>() && IsPrimitiveCNode(node, prim::kPrimTupleGetItem)) {
      auto cnode = node->cast<CNodePtr>();
      MS_EXCEPTION_IF_NULL(cnode);
      auto &inputs = cnode->inputs();
      if (inputs.size() < 2) {
        MS_LOG(EXCEPTION) << "Invalid get item node";
      }
      auto &parent = inputs[1];
      auto iter = node_positions.find(parent);
      if (iter != node_positions.end()) {
        size_t position = iter->second;
        auto iter_nodes = insert_positions.find(position);
        if (iter_nodes != insert_positions.end()) {
          iter_nodes->second.push_back(node);
        } else {
          (void)insert_positions.insert(
            std::pair<size_t, std::vector<AnfNodePtr>>(position, std::vector<AnfNodePtr>{node}));
        }
        continue;
      }
    }
    result.emplace_back(node);
    node_positions[node] = result.size();
  }

  size_t insert_num = 0;
  for (auto &item : insert_positions) {
    size_t position = item.first + insert_num;
    (void)result.insert(result.begin() + position, item.second.begin(), item.second.end());
    insert_num += item.second.size();
  }
  return result;
}

std::vector<AnfNodePtr> SplitSort(const FuncGraphPtr &graph, const std::string &default_target) {
  std::vector<AnfNodePtr> result;
  std::stack<AnfNodePtr> to_visit;
  std::stack<AnfNodePtr> next_to_visit;
  std::map<AnfNodePtr, size_t> nodes_ref;
  std::map<AnfNodePtr, std::vector<AnfNodePtr>> control_edges;
  CalcNodeRefCount(graph, &nodes_ref, &control_edges);
  std::string handle_target = default_target;
  std::string next_target = "";
  to_visit.push(graph->get_return());
  while (!to_visit.empty() || !next_to_visit.empty()) {
    if (to_visit.empty()) {
      to_visit.swap(next_to_visit);
      handle_target = next_target;
    }
    auto &node = to_visit.top();
    MS_EXCEPTION_IF_NULL(node);
    to_visit.pop();
    result.emplace_back(node);
    if (!node->isa<CNode>()) {
      continue;
    }
    auto cnode = node->cast<CNodePtr>();
    MS_EXCEPTION_IF_NULL(cnode);
    auto node_inputs = cnode->inputs();
    std::reverse(node_inputs.begin(), node_inputs.end());
    auto ctrl_inputs = control_edges.find(node);
    if (ctrl_inputs != control_edges.end()) {
      node_inputs.insert(node_inputs.end(), ctrl_inputs->second.begin(), ctrl_inputs->second.end());
    }
    for (auto &input : node_inputs) {
      auto iter = nodes_ref.find(input);
      if (iter != nodes_ref.end()) {
        iter->second--;
        if (iter->second != 0) {
          continue;
        }
      }
      if (!input->isa<CNode>()) {
        to_visit.push(input);
        continue;
      }
      std::string input_target = GetCNodeTarget(input);
      if (input_target == handle_target) {
        to_visit.push(input);
      } else if (next_to_visit.empty() || input_target == next_target) {
        next_to_visit.push(input);
        next_target = input_target;
      } else {
        MS_LOG(EXCEPTION) << "only support two different target";
      }
    }
  }
  std::reverse(result.begin(), result.end());
  return result;
}

bool IsSubGraph(const AnfNodePtr &node) {
  MS_EXCEPTION_IF_NULL(node);
  if (node->isa<CNode>()) {
    auto cnode = node->cast<CNodePtr>();
    auto &inputs = cnode->inputs();
    if (inputs.empty()) {
      MS_LOG(EXCEPTION) << "Inputs of apply node is empty";
    }

    AnfNodePtr fn = inputs[0];
    if (!IsValueNode<Primitive>(fn)) {
      return false;
    }
    auto node_prim = GetValueNode<PrimitivePtr>(fn);
    if (node_prim->name() == prim::kPrimPartial->name()) {
      return true;
    }
  } else if (IsValueNode<FuncGraph>(node)) {
    return true;
  }
  return false;
}
}  // namespace

CompileGraph::CompileGraph(const BackendPtr &backend, const std::vector<PrimitivePtr> &cut_list)
    : backend_(backend), cut_list_(cut_list) {
  MS_EXCEPTION_IF_NULL(backend_);
  lin_convert_ = backend_->convert_fn();
  if (lin_convert_ == nullptr) {
    MS_LOG(EXCEPTION) << "Attribute 'lin_convert' is null.: " << backend->name();
  }

  is_gevm_convert_ = false;
  if (backend->name() == kGeVm) {
    MS_LOG(INFO) << "Attribute 'is_gevm_convert' is true";
    is_gevm_convert_ = true;
  }
}

bool CompileGraph::IsCut(const AnfNodePtr &node) {
  MS_EXCEPTION_IF_NULL(node);
  if (node->isa<CNode>()) {
    auto cnode = node->cast<CNodePtr>();
    auto &inputs = cnode->inputs();
    if (inputs.empty()) {
      MS_LOG(EXCEPTION) << "Inputs of apply node is empty";
    }

    AnfNodePtr fn = inputs[0];
    if (IsValueNode<FuncGraph>(fn)) {
      auto fg = GetValueNode<FuncGraphPtr>(fn);
      if (fg->has_attr(FUNC_GRAPH_ATTR_GRAPH_KERNEL)) {
        return false;
      }
    }

    if (!IsValueNode<Primitive>(fn)) {
      return true;
    }

    PrimitivePtr node_prim = GetValueNode<PrimitivePtr>(fn);
    for (auto &prim : cut_list_) {
      MS_EXCEPTION_IF_NULL(prim);
      if (prim->name() == node_prim->name()) {
        if (prim->name() == prim::kPrimBpropCut->name()) {
          auto ms_context = MsContext::GetInstance();
          MS_EXCEPTION_IF_NULL(ms_context);
          ms_context->set_enable_pynative_hook(true);
        }

        if (backend_->name() == kMsConvert && prim->name() == prim::kPrimMakeTuple->name()) {
          if (inputs.size() < 2) {
            return false;
          }
          auto ret = IsSubGraph(inputs[1]);
          return ret;
        }

        return true;
      }
    }

#ifdef ENABLE_GE
    if (is_gevm_convert_) {
      auto name = GetCNodeFuncName(cnode);
      auto adpt = transform::DfGraphConvertor::FindAdapter(name);
      if (adpt == nullptr) {
        return true;
      }
    }
#endif
  }

  return false;
}

VectorRef CompileGraph::SplitNodesWithTarget(const std::vector<AnfNodePtr> &input_nodes, const FuncGraphPtr &graph) {
  MS_EXCEPTION_IF_NULL(graph);
  auto nodes = OptimizeGetItemOrder(input_nodes);
  VectorRef splits;
  VectorRef split;
  std::string last_target;
  for (auto &node : nodes) {
    MS_EXCEPTION_IF_NULL(node);
    if (IsCut(node)) {
      if (split.size() != 0) {
        splits.push_back(split);
      }
      splits.push_back(node);
      split.clear();
    } else if (node->isa<CNode>()) {
      std::string cur_target = GetCNodeTarget(node);
      if (cur_target != last_target && !last_target.empty() && split.size() != 0) {
        splits.push_back(split);
        split.clear();
      }
      last_target = cur_target;
      split.push_back(node);
    }
  }
  return splits;
}

VectorRef CompileGraph::SplitNodes(const FuncGraphPtr &graph) {
  MS_EXCEPTION_IF_NULL(graph);
  auto nodes = TopoSort(graph->get_return());
  MS_LOG(DEBUG) << "Split all nodes size:" << nodes.size();

  if (ContainMultiTarget(nodes)) {
    auto context_ptr = MsContext::GetInstance();
    MS_EXCEPTION_IF_NULL(context_ptr);
    std::string default_target = context_ptr->device_target();
    nodes = SplitSort(graph, default_target);
    return SplitNodesWithTarget(nodes, graph);
  }

  VectorRef splits;
  VectorRef split;
  for (auto &node : nodes) {
    MS_EXCEPTION_IF_NULL(node);
    if (IsCut(node)) {
      if (split.size() != 0) {
        splits.push_back(split);
      }
      splits.push_back(node);
      split.clear();
    } else if (node->isa<CNode>()) {
      split.push_back(node);
    }
  }
  return splits;
}

// Push the value node on the stack.
void CompileGraph::Push(const AnfNodePtr &node) {
  MS_EXCEPTION_IF_NULL(node);
  if (slots_.count(node) > 0) {
    MS_LOG(EXCEPTION) << "Push failed node in slots:" << node->DebugString()
                      << " NodeInfo: " << trace::GetDebugInfo(node->debug_info());
  }
  MS_LOG(DEBUG) << "Push node: " << node->DebugString(true) << " height_: " << height_
                << " is parameter: " << node->isa<Parameter>();
  slots_[node] = height_;
  set_height(height_ + 1);
}

void CompileGraph::AddInst(const Instruction &inst, const int &arg) {
  VectorRef args;
  args.push_back(arg);
  AddInst(inst, args);
}

void CompileGraph::AddInst(const Instruction &inst, const ValuePtr &arg) {
  VectorRef args;
  args.push_back(arg);
  AddInst(inst, args);
}

void CompileGraph::AddInst(const Instruction &inst, const VectorRef &args) {
  inst_.push_back(std::make_pair(inst, args));
}

// Gets the stack reference for the node value. If the node is a constant,
// it may actually cause the push in to not be mentioned before.
int CompileGraph::Ref(const AnfNodePtr &node) {
  MS_EXCEPTION_IF_NULL(node);
  MS_LOG(DEBUG) << "Start Ref node " << node->DebugString(true) << " height_: " << height_;
  if (slots_.count(node) == 0 && node->isa<ValueNode>()) {
    if (IsValueNode<FuncGraph>(node)) {
      MS_LOG(DEBUG) << "Push graph.";
      AddInst(Instruction::kGraph, GetValueNode(node));
    } else {
      MS_LOG(DEBUG) << "Push.";
      if (IsValueNode<Primitive>(node)) {
        MS_LOG(EXCEPTION) << "must not be primitive in here NodeInfo: " << trace::GetDebugInfo(node->debug_info());
      } else {
        AddInst(Instruction::kPush, GetValueNode(node));
      }
    }
    Push(node);
  }
  MS_LOG(DEBUG) << "End Ref node end height_: " << height_ << ", slots: " << slots_[node]
                << ", return: " << slots_[node] - height_;
  return slots_[node] - height_;
}

// Make sure the value of node is at the top of the stack.
void CompileGraph::AddInput(const AnfNodePtr &node) {
  MS_EXCEPTION_IF_NULL(node);
  if (slots_.count(node) == 0) {
    MS_LOG(DEBUG) << "Input node is null " << node->DebugString(true);
    (void)Ref(node);
    return;
  }
  AddInst(Instruction::kInput, Ref(node));
  set_height(height_ + 1);
}

// Call back effect in stack
void CompileGraph::Ret(int nargs) { set_height(height_ - nargs); }

void CompileGraph::PushParameters(const FuncGraphPtr &graph) {
  MS_EXCEPTION_IF_NULL(graph);
  std::vector<AnfNodePtr> parameters = graph->parameters();
  for (size_t i = parameters.size(); i != 0; i--) {
    Push(parameters[i - 1]);
    MS_LOG(DEBUG) << "Push parameter " << i - 1 << ": " << parameters[i - 1]->DebugString(true);
  }
}

int CompileGraph::LinConvert(const FuncGraphPtr &graph, const AnfNodePtrList &node_list, const std::string &target) {
  MS_LOG(DEBUG) << "LinConvert start";
  LinConvertResult result;

  result = lin_convert_(node_list, target);

  if (result.run == nullptr) {
    MS_LOG(ERROR) << "LinConvert failed";
    return RET_FAILED;
  }

  if (!(*result.run)) {
    if (result.inputs.size() != result.outputs.size()) {
      MS_EXCEPTION_IF_NULL(graph);
      MS_LOG(EXCEPTION) << "must inputs equal outputs NodeInfo: " << trace::GetDebugInfo(graph->debug_info());
    } else {
      size_t size = result.inputs.size();
      for (size_t i = 0; i < size; i++) {
        Tie(result.inputs[i], result.outputs[i]);
      }
      return RET_CONTINUE;
    }
  }
  AddExternal(result);
  for (auto &o : result.outputs) {
    Push(o);
  }

  return RET_SUCCESS;
}

int CompileGraph::InterpretNode(const FuncGraphPtr &graph, const CNodePtr &node) {
  MS_EXCEPTION_IF_NULL(node);
  MS_LOG(DEBUG) << "Interpret node: " << node->DebugString(true);
  std::vector<AnfNodePtr> node_inputs = node->inputs();
  if (node_inputs.empty()) {
    MS_LOG(EXCEPTION) << "The node->inputs() is empty";
  }
  AnfNodePtr fn = node_inputs[0];
  if (IsValueNode<Primitive>(fn)) {
    PrimitivePtr value = GetValueNode<PrimitivePtr>(fn);
    MS_LOG(DEBUG) << "The fn is primitive " << (*value).name();
    for (size_t i = node_inputs.size() - 1; i > 0; i--) {
      AddInput(node->input(i));
    }
    if (IsPrimitive(fn, prim::kPrimReturn)) {
      AddReturn(node);
      return RET_BREAK;
    }
    if (IsPrimitive(fn, prim::kPrimPartial)) {
      AddPartial(node);
    } else if (IsPrimitive(fn, prim::kPrimSwitch)) {
      AddSwitch(node);
    } else if (IsPrimitive(fn, prim::kPrimSwitchLayer)) {
      AddSwitchLayer(node);
    } else if (IsPrimitive(fn, prim::kPrimMakeTuple)) {
      AddMakeTuple(node);
    } else {
      AddPrimitive(node, value);
    }
  } else {
    int ret = AddCall(graph, node);
    if (ret == RET_BREAK) {
      return ret;
    }
  }
  Push(node);
  return RET_SUCCESS;
}

bool CompileGraph::SplitGraph(const FuncGraphPtr &graph) {
  MS_LOG(DEBUG) << "Start split graph";
  MS_EXCEPTION_IF_NULL(graph);
  VectorRef splits = SplitNodes(graph);

  MS_LOG(DEBUG) << "Split nodes size:" << splits.size();
  for (auto &split : splits) {
    int ret = RET_SUCCESS;
    if (utils::isa<VectorRef>(split)) {
      MS_LOG(DEBUG) << "Start a extern LinConvert";
      std::vector<AnfNodePtr> args;
      auto vec_ref = utils::cast<VectorRef>(split);
      (void)std::transform(vec_ref.begin(), vec_ref.end(), std::back_inserter(args),
                           [](const BaseRef &v) { return utils::cast<AnfNodePtr>(v); });
      if (args.size() > 0) {
        std::string cur_target = GetCNodeTarget(args[0]);
        ret = LinConvert(graph, args, cur_target);
      } else {
        ret = LinConvert(graph, args);
      }
      MS_LOG(DEBUG) << "End a extern LinConvert";
      if (ret == RET_FAILED) {
        return false;
      }
      if (ret == RET_CONTINUE) {
        continue;
      }
    } else {
      MS_LOG(DEBUG) << "Start a cut node";
      if (!(utils::isa<AnfNodePtr>(split) && utils::cast<AnfNodePtr>(split)->isa<CNode>())) {
        MS_LOG(EXCEPTION) << "must be anfnode here NodeInfo: " << trace::GetDebugInfo(graph->debug_info());
      }
      CNodePtr node = utils::cast<AnfNodePtr>(split)->cast<CNodePtr>();
      ret = InterpretNode(graph, node);
      MS_LOG(DEBUG) << "End a cut node";
      if (ret == RET_BREAK) {
        break;
      }
    }
  }
  MS_LOG(DEBUG) << "End split graph";
  return true;
}

InstSet CompileGraph::Run(const FuncGraphPtr &graph) {
  MS_EXCEPTION_IF_NULL(graph);

  Reset();
  PushParameters(graph);
  int param_height = height_;
  MS_LOG(DEBUG) << "'param_height': " << height_ << " to split graph: " << graph->get_return()->DebugString(true);

  if (!SplitGraph(graph)) {
    return inst_;
  }

  AddPadStack(param_height);
  auto ret = inst_;
  Reset();
  return ret;
}

void CompileGraph::AddPadStack(int param_height) {
  int stack_sizes = max_height_ - param_height;
  MS_LOG(DEBUG) << "Pad stack max_height_:" << max_height_ << " param:" << param_height
                << " need_stack:" << stack_sizes;
  if (stack_sizes > 0) {
    VectorRef need_stacks({stack_sizes});
    (void)inst_.insert(inst_.begin(), std::make_pair(Instruction::kPadStack, need_stacks));
  }
}

void CompileGraph::AddTailCall(const AnfNodePtr &fn, size_t size) {
  VectorRef args;
  args.emplace_back(Ref(fn));
  args.emplace_back(height_);
  args.emplace_back(static_cast<int>(size - 1));
  MS_LOG(DEBUG) << "Tail call:" << Ref(fn) << ", " << height_ << ", " << size - 1;
  AddInst(Instruction::kTailCall, args);
}

void CompileGraph::AddPartial(const CNodePtr &node) {
  auto inputs = node->inputs();
  VectorRef args;
  auto fn = inputs[1];
  if (!IsValueNode<FuncGraph>(fn)) {
    MS_LOG(EXCEPTION) << "The type of 1st input of node must be FuncGraph";
  }
  for (size_t i = 1; i < inputs.size(); i++) {
    args.emplace_back(Ref(inputs[i]));
  }
  AddInst(Instruction::kPartial, args);
}

void CompileGraph::AddMakeTuple(const CNodePtr &node) {
  auto inputs = node->inputs();
  VectorRef args;
  for (size_t i = 1; i < inputs.size(); i++) {
    args.emplace_back(Ref(inputs[i]));
  }
  AddInst(Instruction::kTuple, args);
}

void CompileGraph::AddSwitch(const CNodePtr &node) {
  auto inputs = node->inputs();
  if (inputs.size() < 4) {
    MS_LOG(EXCEPTION) << "Length of inputs of primitive " << prim::kPrimSwitch->name() << " is less than 4";
  }
  VectorRef args;
  args.emplace_back(Ref(inputs[1]));
  args.emplace_back(Ref(inputs[2]));
  args.emplace_back(Ref(inputs[3]));
  AddInst(Instruction::kSwitch, args);
}

void CompileGraph::AddSwitchLayer(const CNodePtr &node) {
  auto inputs = node->inputs();
  if (inputs.size() != 3) {
    MS_LOG(EXCEPTION) << "Switch layer must have index and branches.";
  }
  VectorRef args;
  args.emplace_back(Ref(inputs[1]));
  args.emplace_back(Ref(inputs[2]));
  AddInst(Instruction::kSwitchLayer, args);
}

void CompileGraph::AddReturn(const CNodePtr &node) {
  VectorRef args;
  args.emplace_back(Ref(node->input(1)));
  args.emplace_back(height_);
  AddInst(Instruction::kReturn, args);
}

void CompileGraph::AddPrimitive(const CNodePtr &node, const PrimitivePtr &prim) {
  auto inputs = node->inputs();
  VectorRef args;
  args.push_back(prim);
  for (size_t i = 1; i < inputs.size(); i++) {
    args.emplace_back(Ref(inputs[i]));
  }
  AddInst(Instruction::kPrim, args);
}

int CompileGraph::AddCall(const FuncGraphPtr &graph, const CNodePtr &node) {
  auto inputs = node->inputs();
  AnfNodePtr fn = inputs[0];
  (void)Ref(fn);
  size_t size = inputs.size();
  for (size_t i = size - 1; i > 0; i--) {
    AddInput(inputs[i]);
  }
  if (node == graph->output()) {
    AddTailCall(fn, size);
    return RET_BREAK;
  }
  MS_LOG(DEBUG) << "Call:" << Ref(fn) << ", " << height_ << ", " << size - 1;
  AddInst(Instruction::kCall, Ref(fn));
  Ret(static_cast<int>(size - 1));
  return RET_SUCCESS;
}

void CompileGraph::AddExternal(const LinConvertResult &result) {
  VectorRef args;
  args.push_back(result.run);
  args.push_back(result.simu_run);
  size_t size = result.inputs.size();
  for (size_t i = 0; i < size; i++) {
    args.emplace_back(Ref(result.inputs[i]));
  }
  AddInst(Instruction::kExternal, args);
}

void TraverseGraphMap(
  const FuncGraphManagerPtr &manager_ptr, FuncGraphTransaction *const tr, const FuncGraphSet &fgs,
  const std::function<std::shared_ptr<FuncGraph>(const PrimitivePtr, const AbstractFunctionPtr)> &get_prim_graph) {
  MS_EXCEPTION_IF_NULL(manager_ptr);
  MS_EXCEPTION_IF_NULL(tr);
  for (const auto &fg : fgs) {
    for (const auto &ct_any : fg->value_nodes()) {
      AnfNodePtr const_primitive_node = ct_any.first;
      if (const_primitive_node != nullptr && IsValueNode<Primitive>(const_primitive_node)) {
        auto users = manager_ptr->node_users()[const_primitive_node];
        for (auto &use : users) {
          CNodePtr node = use.first->cast<CNodePtr>();
          MS_EXCEPTION_IF_NULL(node);
          if (node->func_graph() != fg) {
            continue;
          }
          int key = use.second;
          if (key != 0) {
            MS_EXCEPTION_IF_NULL(node->input(0));
            bool key_is_const = node->input(0)->isa<ValueNode>();
            PrimitivePtr value = GetValueNode<PrimitivePtr>(node->input(0));
            if (value != nullptr) {
              bool is_prim_array_map = !(prim::kPrimArrayMap->name().compare(value->name()));
              bool is_prim_array_reduce = !(prim::kPrimArrayReduce->name().compare(value->name()));
              if (key == 1 && key_is_const && (is_prim_array_map || is_prim_array_reduce)) {
                continue;
              }
            }
            FuncGraphPtr g = get_prim_graph(GetValueNode<PrimitivePtr>(const_primitive_node),
                                            dyn_cast<AbstractFunction>(const_primitive_node->abstract()));
            tr->SetEdge(node, key, NewValueNode(g));
          }
        }
      }
    }
  }
}

FuncGraphPtr WrapPrimitives(const FuncGraphPtr &graph) {
  MS_EXCEPTION_IF_NULL(graph);
  FuncGraphManagerPtr manager_ptr = graph->manager();
  MS_EXCEPTION_IF_NULL(manager_ptr);
  MapPrimTypeFuncGraph prim_graphs;
  auto get_prim_graph = [&](const PrimitivePtr &prim, const AbstractFunctionPtr &type) {
    PrimTypePair prim_type = std::make_pair(prim, type);
    if (prim_graphs.end() == prim_graphs.find(prim_type)) {
      FuncGraphPtr g = std::make_shared<FuncGraph>();
      std::vector<AnfNodePtr> args;
      ValueNodePtr prim_ct = NewValueNode(prim);
      MS_EXCEPTION_IF_NULL(prim_ct);
      prim_ct->set_abstract(type);
      args.push_back(prim_ct);
      MS_EXCEPTION_IF_NULL(type);
      TypedPrimitiveAbstractClosurePtr tp = dyn_cast<abstract::TypedPrimitiveAbstractClosure>(type->GetUnique());
      MS_EXCEPTION_IF_NULL(tp);
      MS_EXCEPTION_IF_NULL(g);
      for (auto t : tp->args_spec_list()) {
        ParameterPtr p = g->add_parameter();
        p->set_abstract(t);
        args.push_back(p);
      }
      AnfNodePtr out = g->NewCNode(args);
      out->set_abstract(tp->output());
      g->set_output(out);
      prim_graphs[prim_type] = g;
    }

    return prim_graphs[prim_type];
  };

  FuncGraphTransaction tr = manager_ptr->Transact();
  auto &fgs = manager_ptr->func_graphs();
  TraverseGraphMap(manager_ptr, &tr, fgs, get_prim_graph);
  tr.Commit();

  return graph;
}

CompileGraphs::CompileGraphs(const BackendPtr &backend, const std::vector<PrimitivePtr> &cut_list) : backend_(backend) {
  MS_EXCEPTION_IF_NULL(backend);
  MS_LOG(DEBUG) << "Start vm: " << backend->name();
  transform_ = std::make_shared<CompileGraph>(backend, cut_list);
  Reset();
}

// Convert graphs to unlinked instructions.
void CompileGraphs::Compile(const FuncGraphPtr &graph) {
  MS_LOG(DEBUG) << "Start";
  mapping_[graph] = static_cast<int>(insts_.size());
  if (transform_ != nullptr) {
    InstSet insts = transform_->Run(graph);
    if (!insts.empty()) {
      (void)insts_.insert(insts_.end(), insts.begin(), insts.end());
    }
  }
  MS_LOG(DEBUG) << "End";
}

// Link instructions from multiple function graphs together.
FinalVMPtr CompileGraphs::Link(const FuncGraphPtr &graph) {
  MS_LOG(DEBUG) << "Start";
  for (std::size_t i = 0; i < insts_.size(); i++) {
    InstType inst = insts_[i];
    MS_LOG(DEBUG) << "Link point:" << inst_str[inst.first];
    if (Instruction::kGraph == inst.first) {
      if (inst.second.empty()) {
        MS_LOG(EXCEPTION) << "The second element of inst is empty";
      }
      FuncGraphPtr func_graph = utils::cast<ValuePtr>(inst.second[0])->cast<FuncGraphPtr>();
      MS_LOG(DEBUG) << "Link graph:" << func_graph->ToString();
      insts_[i] = std::make_pair(Instruction::kPush, VectorRef(std::vector<BaseRef>{mapping_[func_graph]}));
    }
  }

  FinalVMPtr rt = std::make_shared<FinalVM>(insts_, backend_);
  MS_LOG(DEBUG) << "End";
  return rt;
}

// Convert all graphs to unlinked instructions and link them.
FinalVMPtr CompileGraphs::CompileAndLink(const FuncGraphPtr &graph) {
  MS_EXCEPTION_IF_NULL(graph);
  MS_LOG(DEBUG) << "Start";
  Reset();
  MS_LOG(DEBUG) << "Begin parameter:" << graph->parameters().size();

  FuncGraphPtr prim_graph = WrapPrimitives(graph);
  Compile(prim_graph);
  MS_EXCEPTION_IF_NULL(prim_graph);
  FuncGraphSet graphs = prim_graph->manager()->func_graphs();
  for (auto g : graphs) {
    if (g != graph && g != nullptr && !(g->has_attr(FUNC_GRAPH_ATTR_GRAPH_KERNEL))) {
      Compile(g);
    }
  }

  FinalVMPtr rt = Link(graph);
  Reset();
  MS_LOG(DEBUG) << "End";
  return rt;
}

bool CompileGraphs::ContainMixedTarget(const FuncGraphPtr &graph) {
  MS_EXCEPTION_IF_NULL(graph);
  auto graph_manager = graph->manager();
  MS_EXCEPTION_IF_NULL(graph_manager);
  FuncGraphSet graphs = graph_manager->func_graphs();
  for (auto &g : graphs) {
    auto nodes = TopoSort(g->get_return());
    if (ContainMultiTarget(nodes)) {
      return true;
    }
  }
  return false;
}

BackendPtr CreateBackend() {
  auto context_ptr = MsContext::GetInstance();
  MS_EXCEPTION_IF_NULL(context_ptr);
  std::string name = context_ptr->backend_policy();
  MS_LOG(INFO) << "CreateBackend is: " << name;
  if (backend_list.count(name) == 0) {
    MS_LOG(EXCEPTION) << "Backend is error: " << name;
  }

  if (name == kMsConvert) {
    std::string target = context_ptr->device_target();
    uint32_t device_id = context_ptr->device_id();
    auto backend = std::make_shared<MsBackend>(name, target, device_id);
    std::string device_target = MsContext::GetInstance()->device_target();
    if (device_target == kAscendDevice) {
      if (MsContext::GetInstance()->execution_mode() == kPynativeMode) {
        backend->set_is_multi_graph_sink(false);
        context_ptr->set_is_multi_graph_sink(false);
      } else {
        backend->set_is_multi_graph_sink(true);
        context_ptr->set_is_multi_graph_sink(true);
      }
    }
    return backend;
  }

  return std::make_shared<Backend>(name);
}
}  // namespace compile
}  // namespace mindspore
