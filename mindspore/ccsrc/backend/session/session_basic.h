/**
 * Copyright 2019-2020 Huawei Technologies Co., Ltd
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
#ifndef MINDSPORE_CCSRC_BACKEND_SESSION_SESSION_BASIC_H
#define MINDSPORE_CCSRC_BACKEND_SESSION_SESSION_BASIC_H

#include <vector>
#include <string>
#include <unordered_map>
#include <utility>
#include <memory>
#include <map>

#include "utils/base_ref_extends.h"
#include "backend/session/session_context.h"
#include "backend/session/kernel_graph.h"
#include "ir/anf.h"
#include "ir/tensor.h"
#include "utils/any.h"
#include "utils/contract.h"
#include "pipeline/pynative/pynative_execute.h"
#include "runtime/device/kernel_info.h"
#include "utils/ms_context.h"
#ifdef ENABLE_DEBUGGER
#include "debug/debugger/debugger.h"
#endif

namespace mindspore {
using GraphId = uint32_t;
using GraphInfo = std::string;
namespace session {
void ClearPythonParasMap();
using CallBackFunc = uint32_t (*)(uint32_t graph_id,
                                  const std::map<std::string, mindspore::tensor::TensorPtr> &params_list);
using AnyList = std::vector<Any>;
using AnyListPtr = std::shared_ptr<AnyList>;

using OpRunInfo = pynative::OpExecInfo;
using OpRunInfoPtr = std::shared_ptr<OpRunInfo>;

class SessionBasic {
 public:
  SessionBasic() : context_(nullptr), summary_callback_(nullptr), device_id_(0) {
#ifdef ENABLE_DEBUGGER
    debugger_ = nullptr;
#endif
  }

  virtual void Init(uint32_t device_id) { device_id_ = device_id; }

  virtual ~SessionBasic() { summary_callback_ = nullptr; }

  virtual GraphId CompileGraph(const AnfNodePtrList &lst, const AnfNodePtrList &outputs) = 0;
  virtual GraphId CompileGraph(NotNull<FuncGraphPtr> func_graph) { return kInvalidGraphId; }
  // build graph, used to handle multiple child graphs
  virtual void BuildGraph(GraphId) {}

  virtual void RunGraph(const GraphId &graph_id, const std::vector<tensor::TensorPtr> &inputs, VectorRef *outputs) = 0;

  virtual void BuildOp(const OpRunInfo &, const GraphInfo &, const std::vector<tensor::TensorPtr> &input_tensors,
                       const std::vector<int> &tensors_mask) {}

  virtual py::tuple RunOp(const OpRunInfo &, const GraphInfo &, const std::vector<tensor::TensorPtr> &input_tensors) {
    return py::tuple();
  }

  virtual void RegisterSummaryCallBackFunc(const CallBackFunc &callback);

  void CreateCNodeKernelGraph(const AnfNodePtr node, KernelGraphPtr graph);

  std::shared_ptr<KernelGraph> ConstructKernelGraph(const AnfNodePtrList &lst, const AnfNodePtrList &outputs);
  std::shared_ptr<KernelGraph> ConstructKernelGraph(const FuncGraphPtr &func_graph,
                                                    std::vector<KernelGraphPtr> *all_out_graph);

  CNodePtr CreateNewCNode(const CNodePtr &cnode, bool valid_input, KernelGraph *graph, bool *from_other_graph,
                          std::unordered_map<AnfNodePtr, AnfNodePtr> *other_graph_cnode);
  CNodePtr CreateNewCNode(CNodePtr cnode, KernelGraph *graph);

  // get graph id in child graphs by ME front anf node pointer
  virtual GraphId GetGraphIdByNode(const AnfNodePtr &) const { return kInvalidGraphId; }
  virtual GraphId GetFinalRunGraph() const { return kInvalidGraphId; }
  void AssignParamKey(const KernelGraphPtr &kernel_graph);
  void InitPSParamAndOptim(const KernelGraphPtr &kernel_graph, const std::vector<tensor::TensorPtr> &inputs_const);
  virtual bool CheckModelInputs(uint32_t graph_id, const std::vector<tensor::TensorPtr> &inputs,
                                std::string *error_msg) const {
    return true;
  }

#ifdef ENABLE_DEBUGGER
  // set debugger
  void SetDebugger() {
    debugger_ = Debugger::GetInstance();
    auto ms_context = MsContext::GetInstance();
    MS_EXCEPTION_IF_NULL(ms_context);
    debugger_->Init(device_id_, ms_context->device_target());
  }
#endif

 private:
  CNodePtr CreateSwitchInput(const AnfNodePtr &node_input, KernelGraph *graph);
  std::vector<AnfNodePtr> CreateSwitchOrPartialNode(const CNodePtr &cnode, KernelGraph *graph);

 protected:
  virtual void SetSummaryNodes(KernelGraph *graph);
  // Get graph by graph id ,if not exist return null ptr
  KernelGraphPtr GetGraph(GraphId graph_id) const;
  virtual void LoadInputData(const std::shared_ptr<KernelGraph> &kernel_graph,
                             const std::vector<tensor::TensorPtr> &inputs_const) const;
  void UpdateOutputs(const std::shared_ptr<KernelGraph> &kernel_graph, VectorRef *const outputs,
                     const std::vector<tensor::TensorPtr> &input_tensors) const;
  void Reorder(std::vector<CNodePtr> *node_list);
  void Summary(KernelGraph *graph);
  // create graph output for RunOp
  void CreateOutputNode(const CNodePtr &cnode, const std::shared_ptr<KernelGraph> &graph);
  CNodePtr ConstructOutput(const AnfNodePtrList &outputs, const std::shared_ptr<KernelGraph> &graph);
  // create a single run op graph
  std::shared_ptr<KernelGraph> ConstructSingleOpGraph(const OpRunInfo &op_run_info,
                                                      const std::vector<tensor::TensorPtr> &input_tensors,
                                                      const std::vector<int> &tensors_mask);
  // trans BaseRef list to py::tuple
  BaseRef TransformBaseRefListToTuple(const BaseRef &base_ref);
  // create a new kernel graph and update the graph sum
  KernelGraphPtr NewKernelGraph();
  std::vector<AnfNodePtr> CreateParameterFromTuple(const AnfNodePtr &node, bool valid_input, KernelGraph *graph);
  virtual ParameterPtr CreateNewParameterFromParameter(const AnfNodePtr &anf, bool valid_input, KernelGraph *graph);
  ValueNodePtr CreateValueNodeKernelGraph(const AnfNodePtr &anf, KernelGraph *graph);
  ParameterPtr CreateNewParameter(const AnfNodePtr &anf, KernelGraph *graph);
  AnfNodePtr CreateNewParameterFromCNode(const AnfNodePtr &anf, bool valid_input, KernelGraph *graph);
  void AddParameterToGraphInputs(const std::vector<AnfNodePtr> &parameters, KernelGraph *graph);
  void InitInternalOutputParameter(const AnfNodePtr &out_node, const AnfNodePtr &parameter);
  AnfNodePtr FindPullNode(const AnfNodePtr &push_node, const std::vector<AnfNodePtr> &node_list);

  std::unordered_map<GraphId, std::shared_ptr<KernelGraph>> graphs_;
  std::unordered_map<GraphInfo, std::shared_ptr<KernelGraph>> run_op_graphs_;
  std::unordered_map<FuncGraphPtr, KernelGraphPtr> front_backend_graph_map_;
  std::shared_ptr<Context> context_;
  CallBackFunc summary_callback_;
  static GraphId graph_sum_;
  uint32_t device_id_;
#ifdef ENABLE_DEBUGGER
  std::shared_ptr<Debugger> debugger_;
#endif
};

using SessionPtr = std::shared_ptr<session::SessionBasic>;
using NamedSummaryOutputs = std::map<std::string, std::pair<AnfNodePtr, int>>;
}  // namespace session
}  // namespace mindspore
#endif  // MINDSPORE_CCSRC_BACKEND_SESSION_SESSION_BASIC_H
