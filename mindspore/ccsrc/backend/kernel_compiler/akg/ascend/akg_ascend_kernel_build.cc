/**
 * Copyright 2020 Huawei Technologies Co., Ltd
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

#include "backend/kernel_compiler/akg/ascend/akg_ascend_kernel_build.h"

#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>
#include "ir/dtype.h"
#include "ir/func_graph.h"
#include "backend/kernel_compiler/kernel.h"
#include "backend/kernel_compiler/common_utils.h"
#include "backend/kernel_compiler/tbe/tbe_utils.h"
#include "backend/kernel_compiler/akg/ascend/akg_ascend_kernel_mod.h"
#include "backend/kernel_compiler/akg/akg_kernel_attrs_process.h"
#include "backend/session/anf_runtime_algorithm.h"
#include "backend/session/kernel_build_client.h"

namespace mindspore {
namespace kernel {
constexpr int32_t PROCESS_NUM = 16;
constexpr int32_t TIME_OUT = 300;

constexpr auto kOpDesc = "op_desc";
constexpr auto kShape = "shape";
constexpr auto kDataType = "data_type";
constexpr auto kInputDesc = "input_desc";
constexpr auto kOutputDesc = "output_desc";
constexpr auto kTensorName = "tensor_name";

namespace {
void UpdateTensorNameInJson(const std::vector<AnfNodePtr> &anf_nodes,
                            std::map<AnfNodePtr, nlohmann::json> *node_json_map) {
  for (auto const &anf_node : anf_nodes) {
    std::vector<int> dyn_input_sizes;
    auto primitive = AnfAlgo::GetCNodePrimitive(anf_node);
    MS_EXCEPTION_IF_NULL(primitive);

    if (primitive->GetAttr(kAttrDynInputSizes) != nullptr) {
      dyn_input_sizes = GetValue<const std::vector<int>>(primitive->GetAttr(kAttrDynInputSizes));
    }

    bool is_dynamic_input = !dyn_input_sizes.empty();
    size_t input_num = is_dynamic_input ? dyn_input_sizes.size() : AnfAlgo::GetInputTensorNum(anf_node);
    size_t real_input_index = 0;
    for (size_t i = 0; i < input_num; ++i) {
      size_t input_tensor_num = is_dynamic_input ? IntToSize(dyn_input_sizes[i]) : 1;
      for (size_t j = 0; j < input_tensor_num; ++j) {
        auto tmp_input = GetKernelInput(anf_node, real_input_index);
        std::string tensor_name = GetTensorName((*node_json_map)[anf_node], kInputDesc, std::make_pair(i, j));
        if (node_json_map->find(tmp_input.first) != node_json_map->end()) {
          std::string new_tensor_name =
            GetTensorName((*node_json_map)[tmp_input.first], kOutputDesc, std::make_pair(0, tmp_input.second));
          SetTensorName(kInputDesc, new_tensor_name, std::make_pair(i, j), &((*node_json_map)[anf_node]));
          MS_LOG(DEBUG) << "Update [" << real_input_index << "] input [" << tensor_name << "] of ["
                        << anf_node->fullname_with_scope() << "] to [" << tmp_input.second << "] output ["
                        << new_tensor_name << "] of [" << tmp_input.first->fullname_with_scope() << "].";
        } else {
          MS_LOG(DEBUG) << "[" << real_input_index << "] input " << tensor_name << "] of ["
                        << anf_node->fullname_with_scope() << "] is out input.";
        }
        real_input_index++;
      }
    }
  }
}

nlohmann::json GetInputsJson(const std::vector<AnfNodePtr> &anf_nodes, const std::vector<AnfNodePtr> &input_list,
                             std::map<AnfNodePtr, nlohmann::json> *node_json_map) {
  nlohmann::json inputs_json;
  auto input_index = GetInputIndex(anf_nodes, input_list);
  for (size_t i = 0; i < input_index.size(); ++i) {
    auto tmp_input = input_index[i];
    auto type_id = AnfAlgo::GetInputDeviceDataType(tmp_input.first, tmp_input.second.first);
    std::string dtype = TypeId2String(type_id);
    nlohmann::json input_desc_json;
    input_desc_json[kTensorName] = GetTensorName((*node_json_map)[tmp_input.first], kInputDesc, tmp_input.second);
    input_desc_json[kDataType] = dtype;
    input_desc_json[kShape] = AnfAlgo::GetInputDeviceShape(tmp_input.first, tmp_input.second.first);
    inputs_json.emplace_back(std::vector<nlohmann::json>{input_desc_json});
  }

  return inputs_json;
}

nlohmann::json GetOutputsJson(const std::vector<AnfNodePtr> &anf_nodes, const std::vector<AnfNodePtr> &input_list,
                              const std::vector<AnfNodePtr> &output_list, const nlohmann::json &inputs_json,
                              std::map<AnfNodePtr, nlohmann::json> *node_json_map) {
  nlohmann::json outputs_json;
  auto output_index = GetOutputIndex(anf_nodes, input_list, output_list);
  for (size_t i = 0; i < output_index.size(); ++i) {
    auto tmp_output = output_index[i];
    bool found = false;
    nlohmann::json output_desc_json;
    for (size_t input_i = 0; input_i < input_list.size(); ++input_i) {
      if (tmp_output.first == input_list[input_i]) {
        output_desc_json = inputs_json[input_i][0];
        found = true;
        break;
      }
    }
    if (!found) {
      auto type_id = AnfAlgo::GetOutputDeviceDataType(tmp_output.first, tmp_output.second);
      std::string dtype = TypeId2String(type_id);
      output_desc_json[kTensorName] =
        GetTensorName((*node_json_map)[tmp_output.first], kOutputDesc, std::make_pair(0, tmp_output.second));
      output_desc_json[kDataType] = dtype;
      auto output_shape = AnfAlgo::GetOutputDeviceShape(tmp_output.first, tmp_output.second);
      if (output_shape.empty()) {
        output_shape.push_back(1);
      }
      output_desc_json[kShape] = output_shape;
    }
    outputs_json.emplace_back(output_desc_json);
  }

  return outputs_json;
}

std::pair<std::vector<std::string>, std::vector<std::pair<AkgAscendKernelBuilder, AnfNodePtr>>> PreProcessJsonForBuild(
  const std::vector<std::pair<AkgAscendKernelBuilder, AnfNodePtr>> &build_args) {
  // Remove cached nodes, gether unique nodes, and collect repeated nodes which need postprecess.
  std::vector<std::string> jsons;
  std::vector<std::pair<AkgAscendKernelBuilder, AnfNodePtr>> repeat_nodes;
  std::unordered_set<std::string> json_name_set;
  for (const auto &[builder, anf_node] : build_args) {
    MS_EXCEPTION_IF_NULL(anf_node);
    auto json_name = builder.json_name();
    MS_LOG(DEBUG) << "Akg start compile op: " << json_name;
    auto cached_kernel_pack = tbe::TbeUtils::SearchCache(json_name, AkgKernelBuild::GetProcessor(anf_node));
    if (cached_kernel_pack != nullptr) {
      MS_LOG(DEBUG) << "Use cached kernel, json_name_[" << json_name << "], fullname_with_scope["
                    << anf_node->fullname_with_scope() << "].";
      auto kernel_mod_ptr = std::make_shared<AkgKernelMod>(cached_kernel_pack);
      kernel_mod_ptr->SetInputSizeList(builder.input_size_list());
      kernel_mod_ptr->SetOutputSizeList(builder.output_size_list());
      AnfAlgo::SetKernelMod(kernel_mod_ptr, anf_node.get());
      continue;
    }

    if (json_name_set.count(json_name) != 0) {
      repeat_nodes.push_back({builder, anf_node});
      continue;
    }
    json_name_set.insert(json_name);
    auto node_json = builder.kernel_json();
    kernel::SaveJsonInfo(json_name, node_json);
    jsons.push_back(node_json);
  }

  return std::make_pair(jsons, repeat_nodes);
}

bool PostProcessAfterCompile(const std::vector<std::pair<AkgAscendKernelBuilder, AnfNodePtr>> &build_args,
                             const std::vector<std::pair<AkgAscendKernelBuilder, AnfNodePtr>> &repeat_nodes) {
  for (const auto &[builder, anf_node] : build_args) {
    auto json_name = builder.json_name();
    auto new_kernel_pack = tbe::TbeUtils::InsertCache(json_name, AkgKernelBuild::GetProcessor(anf_node));
    if (new_kernel_pack == nullptr) {
      MS_LOG(ERROR) << "Insert to cache failed, json_name_[" << json_name << "], fullname_with_scope["
                    << anf_node->fullname_with_scope() << "].";
      return false;
    }
    auto kernel_mod_ptr = std::make_shared<AkgKernelMod>(new_kernel_pack);
    kernel_mod_ptr->SetInputSizeList(builder.input_size_list());
    kernel_mod_ptr->SetOutputSizeList(builder.output_size_list());
    AnfAlgo::SetKernelMod(kernel_mod_ptr, anf_node.get());
    MS_LOG(DEBUG) << "Akg compile " << json_name << " kernel and insert cache successfully!";
  }

  for (const auto &[builder, anf_node] : repeat_nodes) {
    auto node_json = builder.kernel_json();
    auto json_name = builder.json_name();
    auto cached_kernel_pack = tbe::TbeUtils::SearchCache(json_name, AkgKernelBuild::GetProcessor(anf_node));
    if (cached_kernel_pack == nullptr) {
      return false;
    }
    MS_LOG(INFO) << "Use just compiled kernel, json_name_[" << json_name << "], fullname_with_scope["
                 << anf_node->fullname_with_scope() << "].";
    auto kernel_mod_ptr = std::make_shared<AkgKernelMod>(cached_kernel_pack);
    kernel_mod_ptr->SetInputSizeList(builder.input_size_list());
    kernel_mod_ptr->SetOutputSizeList(builder.output_size_list());
    AnfAlgo::SetKernelMod(kernel_mod_ptr, anf_node.get());
  }

  return true;
}
}  // namespace

bool AkgAscendKernelBuilder::CollectJson(const AnfNodePtr &anf_node) {
  MS_EXCEPTION_IF_NULL(anf_node);
  std::string op_name = AnfAlgo::GetCNodeName(anf_node);
  MS_LOG(INFO) << "AKG start compile, op[" << op_name << "], device[" << AkgKernelBuild::GetProcessor(anf_node) << "]";
  auto it = kAkgKernelAttrsProcessMap.find(op_name);
  if (it != kAkgKernelAttrsProcessMap.end()) {
    it->second(anf_node);
  }
  MS_LOG(INFO) << "Akg start compile, op[" << op_name << "], device[" << AkgKernelBuild::GetProcessor(anf_node) << "]";
  nlohmann::json node_json;
  if (!GenerateSingleKernelJson(anf_node, op_name, &node_json)) {
    MS_LOG(ERROR) << "Op[" << op_name << "] create single kernel json failed.";
  }

  kernel_json_ = node_json.dump();

  if (!GetIOSize(node_json, &input_size_list_, &output_size_list_)) {
    MS_LOG(ERROR) << "Cal mem size failed.";
    return false;
  }

  return true;
}

bool AkgAscendKernelBuilder::GenJsonAndPreprocess4Fused(const std::vector<AnfNodePtr> &anf_nodes,
                                                        std::map<AnfNodePtr, nlohmann::json> *node_json_map) {
  for (auto const &anf_node : anf_nodes) {
    MS_EXCEPTION_IF_NULL(anf_node);
    std::string op_name = AnfAlgo::GetCNodeName(anf_node);
    if (!AnfAlgo::IsRealKernel(anf_node)) {
      MS_LOG(ERROR) << "Invalid anf node to build [" << anf_node->fullname_with_scope() << "].";
      return false;
    }
    auto it = kAkgKernelAttrsProcessMap.find(op_name);
    if (it != kAkgKernelAttrsProcessMap.end()) {
      it->second(anf_node);
    }

    nlohmann::json node_json;
    if (!GenerateSingleKernelJson(anf_node, op_name, &node_json)) {
      MS_LOG(ERROR) << "Op [" << op_name << "] create single kernel json failed.";
      return false;
    }
    // No need for composite op.
    node_json.erase("id");
    node_json.erase("op");
    node_json.erase("composite");

    auto primitive = AnfAlgo::GetCNodePrimitive(anf_node);
    MS_EXCEPTION_IF_NULL(primitive);

    if (primitive->GetAttr("fusion") != nullptr) {
      node_json["fusion"] = primitive->GetAttr("fusion")->ToString();
    }

    (*node_json_map)[anf_node] = node_json;
  }
  return true;
}

bool AkgAscendKernelBuilder::CollectFusedJson(const std::vector<AnfNodePtr> &anf_nodes,
                                              const std::vector<AnfNodePtr> &input_list,
                                              const std::vector<AnfNodePtr> &output_list) {
  if (anf_nodes.empty() || input_list.empty()) {
    MS_LOG(ERROR) << "Invalid input size, anf_nodes [" << anf_nodes.size() << "], input_list [" << input_list.size()
                  << "].";
    return false;
  }
  MS_LOG(INFO) << "anf_nodes [" << output_list.size() << "], input_list [" << anf_nodes.size() << "], output_list ["
               << input_list.size() << "].";

  std::map<AnfNodePtr, nlohmann::json> node_json_map;
  if (!GenJsonAndPreprocess4Fused(anf_nodes, &node_json_map)) {
    return false;
  }

  UpdateTensorNameInJson(anf_nodes, &node_json_map);

  nlohmann::json fused_node_json;
  std::vector<nlohmann::json> node_json_desc;
  std::transform(anf_nodes.begin(), anf_nodes.end(), std::back_inserter(node_json_desc),
                 [&node_json_map](const AnfNodePtr &anf_node) { return node_json_map[anf_node]; });
  fused_node_json[kOpDesc] = node_json_desc;
  fused_node_json[kInputDesc] = GetInputsJson(anf_nodes, input_list, &node_json_map);
  fused_node_json[kOutputDesc] =
    GetOutputsJson(anf_nodes, input_list, output_list, fused_node_json[kInputDesc], &node_json_map);

  size_t hash_id = std::hash<std::string>()(fused_node_json.dump());
  json_name_ = "Fused_";
  auto fg = anf_nodes[0]->func_graph();
  MS_EXCEPTION_IF_NULL(fg);
  auto attr_val = fg->get_attr(FUNC_GRAPH_ATTR_GRAPH_KERNEL);
  if (attr_val != nullptr) {
    auto fg_attr = GetValue<std::string>(attr_val);
    (void)json_name_.append(fg_attr).append("_");
  }
  (void)json_name_.append(std::to_string(hash_id));
  fused_node_json["composite_graph"] = fg->ToString();
  fused_node_json["op"] = json_name_;
  fused_node_json["platform"] = "AKG";
  fused_node_json["process"] = "aicore";
  fused_node_json["composite"] = true;

  kernel_json_ = fused_node_json.dump();

  if (!GetIOSize(fused_node_json, &input_size_list_, &output_size_list_)) {
    MS_LOG(ERROR) << "Cal mem size failed.";
    return false;
  }

  return true;
}

bool AkgOpParallelBuild(const std::vector<std::pair<AkgAscendKernelBuilder, AnfNodePtr>> &build_args) {
  auto [jsons, repeat_nodes] = PreProcessJsonForBuild(build_args);
  if (jsons.empty()) {
    return true;
  }

  // Start building in AKG
  if (!AscendKernelBuildClient::Instance().AkgStart(PROCESS_NUM, TIME_OUT)) {
    MS_LOG(ERROR) << "Akg start failed.";
    return false;
  }
  if (!AscendKernelBuildClient::Instance().AkgSendData(jsons)) {
    MS_LOG(ERROR) << "Akg send data failed.";
    return false;
  }
  if (!AscendKernelBuildClient::Instance().AkgWait()) {
    MS_LOG(ERROR) << "Akg compile failed.";
    return false;
  }

  if (!PostProcessAfterCompile(build_args, repeat_nodes)) {
    return false;
  }

  return true;
}

bool AkgAscendKernelParallelBuild(const std::vector<AnfNodePtr> &anf_nodes) {
  std::vector<std::pair<AkgAscendKernelBuilder, AnfNodePtr>> json_and_node;
  for (const auto &anf_node : anf_nodes) {
    MS_EXCEPTION_IF_NULL(anf_node);
    AkgAscendKernelBuilder akg_cce_kernel_builder;
    KernelPackPtr kernel_pack = nullptr;
    auto cnode = anf_node->cast<CNodePtr>();
    MS_EXCEPTION_IF_NULL(cnode);
    if (AnfAlgo::IsGraphKernel(cnode)) {
      auto func_graph = AnfAlgo::GetCNodeFuncGraphPtr(cnode);
      auto mng = func_graph->manager();
      if (mng == nullptr) {
        mng = Manage(func_graph, true);
        func_graph->set_manager(mng);
      }
      MS_EXCEPTION_IF_NULL(func_graph);
      std::vector<AnfNodePtr> node_list;
      std::vector<AnfNodePtr> input_list;
      std::vector<AnfNodePtr> output_list;
      std::string op_name = AnfAlgo::GetCNodeName(anf_node);
      MS_LOG(INFO) << "Akg start compile composite op[" << op_name << "]";
      GetValidKernelNodes(func_graph, &node_list, &input_list, &output_list);
      if (!akg_cce_kernel_builder.CollectFusedJson(node_list, input_list, output_list)) {
        MS_EXCEPTION(UnknownError) << "Akg build failed composite op[" << op_name << "].";
      }
    } else {
      if (!akg_cce_kernel_builder.CollectJson(anf_node)) {
        MS_EXCEPTION(UnknownError) << "Akg build failed op[" << AnfAlgo::GetCNodeName(anf_node) << "].";
      }
    }
    json_and_node.push_back({akg_cce_kernel_builder, anf_node});
  }

  if (json_and_node.empty()) {
    MS_LOG(DEBUG) << "There is no kernel needed to be compiled.";
    return true;
  }

  return AkgOpParallelBuild(json_and_node);
}
}  // namespace kernel
}  // namespace mindspore
