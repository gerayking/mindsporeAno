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

#ifndef MINDSPORE_CCSRC_RUNTIME_DEVICE_KERNEL_RUNTIME_H_
#define MINDSPORE_CCSRC_RUNTIME_DEVICE_KERNEL_RUNTIME_H_
#include <vector>
#include <memory>
#include <string>
#include <map>

#include "runtime/device/device_address.h"
#include "ir/tensor.h"
#include "utils/convert_utils.h"
#ifdef ENABLE_DUMP_E2E
#include "debug/e2e_dump.h"
#endif
#ifdef ENABLE_DEBUGGER
#include "debug/debugger/debugger.h"
#endif
#include "backend/session/kernel_graph.h"
#include "backend/session/anf_runtime_algorithm.h"
#include "backend/kernel_compiler/kernel.h"
#include "utils/ms_context.h"
#include "runtime/device/memory_manager.h"

using mindspore::tensor::Tensor;
using std::vector;
using TensorPtr = std::shared_ptr<Tensor>;
using mindspore::kernel::AddressPtr;
using AddressPtrList = std::vector<mindspore::kernel::AddressPtr>;

namespace mindspore {
#ifndef ENABLE_DEBUGGER
class Debugger;
#endif
namespace device {
class KernelRuntime {
 public:
  KernelRuntime() = default;
  virtual ~KernelRuntime();
  virtual bool Init() = 0;
  virtual void AssignMemory(session::KernelGraph *graph);
  void RunOpAssignMemory(const ValuePtr &pre_output_value, const std::vector<tensor::TensorPtr> &input_tensors,
                         session::KernelGraph *graph);
  void RunOpClearMemory(const session::KernelGraph *graph);
  bool DumpDataEnabled();
  bool DumpDataEnabledIteration();
  virtual bool Run(session::KernelGraph *graph, Debugger *debugger = nullptr);
  virtual bool DumpData(session::KernelGraph *graph, Debugger *debugger = nullptr);
  virtual bool LoadData(session::KernelGraph *graph, Debugger *debugger);
  virtual bool RunTask(const session::KernelGraph *graph);
  virtual bool GenTask(const session::KernelGraph *graph);
  bool LaunchKernel(const session::KernelGraph *graph);
  bool LaunchTaskBasedOnSingleKernel(kernel::KernelModPtr kernel_mod_ptr, const AddressPtrList &kernel_inputs,
                                     const AddressPtrList &kernel_outputs,
                                     const AddressPtrList &kernel_workspaces) const;
  virtual void AssignStaticMemoryInput(const session::KernelGraph *graph);
  virtual void AssignStaticMemoryValueNode(session::KernelGraph *graph);
  virtual void ClearGraphRuntimeResource(uint32_t graph_id);
  virtual bool SyncStream() = 0;

#ifdef ENABLE_DUMP_E2E
  DumpConfPtr GetDumpConf();
#endif
  virtual bool LoadTask(const session::KernelGraph *graph);
  // for GPU and D to impl
  virtual void ReleaseDeviceRes() {}
  void set_device_id(uint32_t device_id) { device_id_ = device_id; }
  DeviceAddressPtr AssignSingleOpLaunchMemory(size_t size, const std::string &format, TypeId type);

 protected:
  virtual DeviceAddressPtr CreateDeviceAddress(void *device_ptr, size_t device_size, const string &format,
                                               TypeId type_id) = 0;
  virtual bool NodeOutputDeviceAddressExist(const AnfNodePtr &node, size_t index);
  void AssignStaticMemory(session::KernelGraph *graph);
  void AssignDynamicMemory(session::KernelGraph *graph);
  void ReuseAssignDynamicMemory(session::KernelGraph *graph);
  void AssignNodeOutputMem(MemType type, const AnfNodePtr &node, int index);
  void AssignWorkSpaceMem(MemType type, const AnfNodePtr &node);
  void AssignReuseWorkSpaceMem(const AnfNodePtr &node);

  void UpdateRefNodeOutputMem(const session::KernelGraph *graph);

  void AssignCommunicationNodeOutputMem(MemType type, const AnfNodePtr &node);
  void AssignCommunicationNodeInputMem(MemType type, const AnfNodePtr &node);
  void AssignCommunicationNodeMem(MemType type, const AnfNodePtr &node);
#ifdef ENABLE_DUMP_E2E
  bool SetDumpConf();
#endif

 private:
  void AssignStaticMemoryOutput(session::KernelGraph *graph);
  void GenLaunchArgs(const mindspore::kernel::KernelMod &kernel_mod, const AnfNodePtr &kernel,
                     AddressPtrList *kernel_inputs, AddressPtrList *kernel_workspaces, AddressPtrList *kernel_outputs);
  bool LaunchKernelMod(const session::KernelGraph &graph);
  void GenAddrCleanLaunchArgs(const CNodePtr &cnode, AddressPtrList *kernel_inputs);
  size_t CountNodeDeviceMemorySize(const AnfNodePtr &node, size_t output_index);
  void RunOpAssignInputMemory(const std::vector<tensor::TensorPtr> &input_tensors, const session::KernelGraph *graph);
  void RunOpAssignOutputMemory(const AnfNodePtr &kernel);
  void RunOpAssignWorkSpaceMemory(const AnfNodePtr &kernel);
  void RunOpAssignOutputNodeMemory(const ValuePtr &pre_output_value, session::KernelGraph *graph);
  void AssignValueNodeTensor(const ValueNodePtr &value_node, const ValuePtr &node_value, size_t output_idx);
  DeviceAddressPtr PreAssignCNodeMemory(const AnfNodePtr &anf_node, size_t index);

 protected:
  uint32_t device_id_{0};
#ifdef ENABLE_DUMP_E2E
  DumpConfPtr dump_conf_ptr_;
#endif
  void *stream_ = nullptr;
  std::shared_ptr<MemoryManager> mem_manager_{nullptr};
};
using KernelRuntimePtr = std::shared_ptr<KernelRuntime>;
}  // namespace device
}  // namespace mindspore

#endif  // MINDSPORE_CCSRC_RUNTIME_DEVICE_KERNEL_RUNTIME_H_
