/**
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

#ifndef MINDSPORE_CCSRC_BACKEND_KERNEL_COMPILER_COMMON_UTILS_H_
#define MINDSPORE_CCSRC_BACKEND_KERNEL_COMPILER_COMMON_UTILS_H_

#include <dirent.h>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <string>
#include <vector>
#include <utility>
#include <nlohmann/json.hpp>
#include "backend/kernel_compiler/kernel.h"
#include "backend/kernel_compiler/oplib/opinfo.h"
#include "backend/kernel_compiler/kernel_build_info.h"

namespace mindspore {
namespace kernel {
constexpr auto kCceKernelMeta = "./kernel_meta/";
constexpr auto kGpuKernelMeta = "./cuda_meta";
constexpr auto kProcessorAiCore = "aicore";
constexpr auto kProcessorAiCpu = "aicpu";
constexpr auto kProcessorCuda = "cuda";
constexpr auto kJsonSuffix = ".json";
constexpr auto kInfoSuffix = ".info";
constexpr unsigned int AUTODIFF_COMPILE_OVERTIME = 600;
constexpr auto kArgDataformat = "data_format";

const std::vector<std::string> support_devices = {"aicore", "aicpu", "cuda"};

struct KernelMetaInfo {
  uintptr_t func_stub_;
  uint32_t block_dim_;
};
using KernelMetaPtr = std::shared_ptr<KernelMetaInfo>;

class KernelMeta {
 public:
  KernelMeta() = default;
  void Initialize(int pid);
  void RemoveKernelCache();
  std::string Search(const std::string &kernel_name) const;
  bool Insert(const std::string &kernel_name, const std::string &kernel_json);
  std::string GetKernelMetaPath() { return kernel_meta_path_; }

  static KernelMeta *GetInstance() {
    static KernelMeta kernel_meta;
    return &kernel_meta;
  }
  ~KernelMeta() = default;

 private:
  bool initialized_ = false;
  std::string kernel_meta_path_;
  std::unordered_map<std::string, std::string> kernel_meta_map_;
};

struct SparseGradient {
  float *value_{nullptr};
  int *indices_{nullptr};
  size_t indices_size_{0};
};

struct ReduceSparseGradientParam {
  SparseGradient *input_grad_{nullptr};
  SparseGradient *workspace_grad_{nullptr};
  SparseGradient *output_grad_{nullptr};
  size_t max_index_{0};
  size_t value_stride_{0};
  bool use_sort_reduce_{false};
};

struct MultiThreadComputeParams {
  float *var_;
  float *accum_;
  float *linear_;
  float *m_;
  float *m_t_;
  float *v_;
  float lr_;
  float l1_;
  float l2_;
  float lr_power_;
  float beta1_;
  float beta2_;
  float epsilon_;
  SparseGradient sparse_grad_;
  size_t var_first_dim_size_;
  size_t var_outer_dim_size_;
  bool use_nesterov_;
};
using MultiThreadComputeFunc = std::function<void(MultiThreadComputeParams *param, size_t start, size_t end)>;

bool CheckCache(const std::string &kernel_name);
KernelPackPtr SearchCache(const std::string &kernel_name, const std::string &processor);
KernelPackPtr InsertCache(const std::string &kernel_name, const std::string &processor);
TypeId DtypeToTypeId(const std::string &dtypes);
std::string Dtype2ShortType(const std::string &dtypes);
std::string TypeId2String(TypeId type_id);
size_t GetDtypeNbyte(const std::string &dtypes);
bool ParseMetadata(const CNodePtr &kernel_node, const std::shared_ptr<const OpInfo> &op_info_ptr, Processor processor,
                   std::vector<std::shared_ptr<KernelBuildInfo>> *const kernel_info_list);
void SaveJsonInfo(const std::string &json_name, const std::string &info);
std::string GetProcessor(const AnfNodePtr &anf_node);
bool IsSameShape(const std::vector<size_t> &shape_a, const std::vector<size_t> &shape_b);
int Sign(float x);
std::pair<AnfNodePtr, size_t> GetKernelInput(const AnfNodePtr &anf_node, size_t index);
std::vector<std::pair<AnfNodePtr, std::pair<size_t, size_t>>> GetInputIndex(const std::vector<AnfNodePtr> &node_list,
                                                                            const std::vector<AnfNodePtr> &input_list);
std::vector<std::pair<AnfNodePtr, size_t>> GetOutputIndex(const std::vector<AnfNodePtr> &node_list,
                                                          const std::vector<AnfNodePtr> &input_list,
                                                          const std::vector<AnfNodePtr> &output_list);
void GetValidKernelNodes(const FuncGraphPtr &func_graph, std::vector<AnfNodePtr> *node_list,
                         std::vector<AnfNodePtr> *input_list, std::vector<AnfNodePtr> *output_list);
void GetValidKernelNodes(const FuncGraphPtr &func_graph, std::vector<AnfNodePtr> *node_list);
bool GetInputTensorValue(const AnfNodePtr &anf_node, size_t input_idx, nlohmann::json *const node_json);
void GetGraphRealOutput(const FuncGraphPtr &func_graph, std::vector<std::pair<AnfNodePtr, size_t>> *node_list);
bool IsWeightBoundary(const AnfNodePtr &node);
void MultiThreadCompute(const MultiThreadComputeFunc &func, MultiThreadComputeParams *params,
                        size_t total_compute_size);
void BucketReduceSparseGradient(const ReduceSparseGradientParam &param);
std::vector<int> GetReduceAttrAxis(const CNodePtr &cnode);
}  // namespace kernel
}  // namespace mindspore

#endif  // MINDSPORE_CCSRC_BACKEND_KERNEL_COMPILER_COMMON_UTILS_H_
