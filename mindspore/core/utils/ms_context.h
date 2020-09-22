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

#ifndef MINDSPORE_CORE_UTILS_MS_CONTEXT_H_
#define MINDSPORE_CORE_UTILS_MS_CONTEXT_H_
#include <thread>
#include <memory>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <utility>
#include "utils/log_adapter.h"

namespace mindspore {
enum MsBackendPolicy {
  kMsBackendGeOnly = 0,
  kMsBackendVmOnly = 1,
  kMsBackendGePrior = 2,
  kMsBackendVmPrior = 3,
  kMsBackendMsPrior = 4,
  kMsBackendUnknown = 5,
};

const int kGraphMode = 0;
const int kPynativeMode = 1;
const char kCPUDevice[] = "CPU";
const char kGPUDevice[] = "GPU";
const char kAscendDevice[] = "Ascend";
const char kDavinciInferenceDevice[] = "AscendInference";
const char kDavinciDevice[] = "Davinci";
const char KNpuLog[] = "_npu_log";
const std::set<std::string> kTargetSet = {kCPUDevice, kGPUDevice, kAscendDevice, kDavinciDevice};
// The default max available device memory is 1024GB.
const float kDefaultMaxDeviceMemory = 1024;

class MsContext {
 public:
  MsContext(const std::string &backend_policy, const std::string &target);
  ~MsContext() = default;
  MsContext(const MsContext &) = delete;
  MsContext &operator=(const MsContext &) = delete;
  using DeviceSeter = std::function<void(const std::string &device_target)>;
  using DeviceTypeSeter = std::function<void(std::shared_ptr<MsContext> &)>;
  static std::shared_ptr<MsContext> GetInstance();

  std::string backend_policy() const;
  bool set_backend_policy(const std::string &policy);

  int execution_mode() const { return execution_mode_; }
  void set_execution_mode(int execution_mode);

  bool enable_pynative_infer() const { return enable_pynative_infer_; }
  void set_enable_pynative_infer(bool enable_pynative_infer) { enable_pynative_infer_ = enable_pynative_infer; }

  bool enable_pynative_hook() const { return enable_pynative_hook_; }
  void set_enable_pynative_hook(bool enable_pynative_hook) { enable_pynative_hook_ = enable_pynative_hook; }

  bool enable_task_sink() const { return enable_task_sink_; }

  void set_precompile_only(bool precompile_only) { precompile_only_ = precompile_only; }
  bool precompile_only() const { return precompile_only_; }

  std::string device_target() const { return device_target_; }
  bool set_device_target(const std::string &target);

  uint32_t device_id() const { return device_id_; }
  bool set_device_id(uint32_t device_id);

  bool save_graphs_flag() const { return save_graphs_flag_; }
  void set_save_graphs_flag(bool save_graphs_flag) { save_graphs_flag_ = save_graphs_flag; }

  std::string save_graphs_path() const { return save_graphs_path_; }
  void set_save_graphs_path(const std::string &save_paths) { save_graphs_path_ = save_paths; }

  bool IsGeInited() { return ge_ref_ > 0; }
  void set_enable_hccl(bool enable_hccl) { enable_hccl_ = enable_hccl; }
  bool enable_hccl() const { return enable_hccl_; }
  bool ir_fusion_flag() const { return ir_fusion_flag_; }
  bool loop_sink_flag() const { return enable_loop_sink_; }
  void set_loop_sink_flag(bool enable_loop_sink) { enable_loop_sink_ = enable_loop_sink; }
  void set_enable_mem_reuse(bool enable_mem_reuse) { enable_mem_reuse_ = enable_mem_reuse; }
  bool enable_mem_reuse() const { return enable_mem_reuse_; }

  void set_enable_gpu_summary(bool enable_gpu_summary) { enable_gpu_summary_ = enable_gpu_summary; }
  bool enable_gpu_summary() const { return enable_gpu_summary_; }

  void set_auto_mixed_precision_flag(bool auto_mixed_precision_flag) {
    auto_mixed_precision_flag_ = auto_mixed_precision_flag;
  }
  bool auto_mixed_precision_flag() const { return auto_mixed_precision_flag_; }

  void set_enable_reduce_precision(bool flag) { enable_reduce_precision_ = flag; }
  bool enable_reduce_precision() const { return enable_reduce_precision_; }

  void set_enable_dump(bool flag) { enable_dump_ = flag; }
  bool enable_dump() const { return enable_dump_; }

  void set_save_dump_path(const std::string &path) { save_dump_path_ = path; }
  std::string save_dump_path() const { return save_dump_path_; }

  bool IsTsdOpened() const { return tsd_ref_ > 0; }
  void set_tsd_ref(const std::string &op);
  uint32_t tsd_ref() const { return tsd_ref_; }

  void set_ge_ref(const std::string &op);
  uint32_t ge_ref() const { return ge_ref_; }

  bool is_pynative_ge_init() { return is_pynative_ge_init_; }
  void set_pynative_ge_init(bool flag) { is_pynative_ge_init_ = flag; }

  bool is_multi_graph_sink() const { return is_multi_graph_sink_; }
  void set_is_multi_graph_sink(bool flag) { is_multi_graph_sink_ = flag; }

  void set_enable_dynamic_mem_pool(bool enable_dynamic_mem_pool) { enable_dynamic_mem_pool_ = enable_dynamic_mem_pool; }
  bool enable_dynamic_mem_pool() const { return enable_dynamic_mem_pool_; }

  void set_graph_memory_max_size(const std::string &graph_memory_max_size) {
    graph_memory_max_size_ = graph_memory_max_size;
  }

  void set_variable_memory_max_size(const std::string &variable_memory_max_size) {
    variable_memory_max_size_ = variable_memory_max_size;
  }

  const std::string &variable_memory_max_size() const { return variable_memory_max_size_; }

  const std::string &graph_memory_max_size() const { return graph_memory_max_size_; }

  void set_enable_profiling(bool flag) { profiling_mode_ = flag; }
  bool enable_profiling() const { return profiling_mode_; }

  void set_profiling_options(const std::string &options) { profiling_options_ = options; }
  std::string profiling_options() const { return profiling_options_; }
  bool check_bprop_flag() const { return check_bprop_flag_; }
  void set_check_bprop_flag(bool check_bprop_flag) { check_bprop_flag_ = check_bprop_flag; }
  void set_print_file_path(const std::string &file) { print_file_path_ = file; }
  const std::string &print_file_path() const { return print_file_path_; }

  float max_device_memory() const { return max_device_memory_; }
  void set_max_device_memory(float max_device_memory) { max_device_memory_ = max_device_memory; }

  void set_enable_graph_kernel(bool enable_graph_kernel) { enable_graph_kernel_ = enable_graph_kernel; }
  bool enable_graph_kernel() const { return enable_graph_kernel_; }

  bool enable_sparse() const { return enable_sparse_; }
  void set_enable_sparse(bool enable_sparse) { enable_sparse_ = enable_sparse; }
  static void device_seter(DeviceSeter device) { seter_ = device; }
  static void device_type_seter(DeviceTypeSeter device_type) { device_type_seter_ = device_type; }

  std::thread tdt_print_;

 private:
  inline static DeviceSeter seter_ = nullptr;
  inline static DeviceTypeSeter device_type_seter_ = nullptr;
  static std::shared_ptr<MsContext> inst_context_;
  static std::map<std::string, MsBackendPolicy> policy_map_;
  MsBackendPolicy backend_policy_;
  std::string device_target_;
  uint32_t device_id_;
  int execution_mode_;
  bool enable_pynative_infer_;
  bool enable_pynative_hook_;
  bool save_graphs_flag_;
  std::string save_graphs_path_;
  uint32_t tsd_ref_;
  uint32_t ge_ref_;
  bool enable_task_sink_;
  bool enable_hccl_;
  bool precompile_only_;
  bool ir_fusion_flag_;
  bool auto_mixed_precision_flag_;
  bool enable_reduce_precision_;
  bool enable_loop_sink_;
  bool enable_mem_reuse_;
  bool enable_gpu_summary_;
  bool enable_dump_;
  std::string save_dump_path_;
  bool is_multi_graph_sink_;
  bool is_pynative_ge_init_;
  bool enable_dynamic_mem_pool_;
  std::string graph_memory_max_size_;
  std::string variable_memory_max_size_;
  bool profiling_mode_;
  std::string profiling_options_;
  bool check_bprop_flag_;
  float max_device_memory_;
  std::string print_file_path_;
  bool enable_graph_kernel_;
  bool enable_sparse_;
};
}  // namespace mindspore

#endif  // MINDSPORE_CORE_UTILS_MS_CONTEXT_H_
