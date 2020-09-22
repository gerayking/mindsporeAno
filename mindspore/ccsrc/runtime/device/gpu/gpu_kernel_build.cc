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
#include "runtime/device/gpu/gpu_kernel_build.h"
#include <string>
#include "backend/kernel_compiler/kernel.h"
#include "backend/kernel_compiler/akg/akg_kernel_build.h"
#include "backend/kernel_compiler/akg/gpu/akg_gpu_kernel_build.h"
#include "backend/kernel_compiler/gpu/gpu_kernel_factory.h"
#include "frontend/operator/ops.h"
#include "backend/session/anf_runtime_algorithm.h"
#include "backend/session/kernel_build_client.h"

namespace mindspore {
namespace device {
namespace gpu {
void GpuBuild(const KernelGraphPtr &kernel_graph) {
  kernel::KernelMeta *bin_map = kernel::KernelMeta::GetInstance();
  MS_EXCEPTION_IF_NULL(bin_map);
  auto pid = mindspore::kernel::GpuKernelBuildClient::Instance().AkgGetPid();
  bin_map->Initialize(pid);
  MS_EXCEPTION_IF_NULL(kernel_graph);
  auto kernels = kernel_graph->execution_order();
  for (const auto &kernel : kernels) {
    std::string kernel_name = session::AnfRuntimeAlgorithm::GetCNodeName(kernel);
    if (kernel_name == prim::kPrimTupleGetItem->name() || kernel_name == prim::kPrimMakeTuple->name() ||
        kernel_name == prim::kPrimDepend->name() || kernel_name == prim::kPrimStateSetItem->name()) {
      continue;
    }

    if (session::AnfRuntimeAlgorithm::GetKernelType(kernel) == KernelType::AKG_KERNEL) {
      auto gpu_kernel_ptr = kernel::AkgGpuKernelBuild(kernel);
      if (!gpu_kernel_ptr) {
        MS_LOG(EXCEPTION) << "Build akg kernel op[" << kernel_name << "] failed";
      }
      session::AnfRuntimeAlgorithm::SetKernelMod(gpu_kernel_ptr, kernel.get());
    } else {
      auto gpu_kernel_ptr = kernel::GpuKernelFactory::GetInstance().Create(kernel_name, kernel);
      if (!gpu_kernel_ptr) {
        MS_LOG(EXCEPTION) << "Build gpu kernel op[" << kernel_name << "] failed";
      }
      if (!gpu_kernel_ptr->Init(kernel)) {
        MS_LOG(EXCEPTION) << "Initialize gpu kernel op[" << kernel_name << "] failed.";
      }
      session::AnfRuntimeAlgorithm::SetKernelMod((kernel::KernelModPtr)gpu_kernel_ptr, kernel.get());
    }
  }
}
}  // namespace gpu
}  // namespace device
}  // namespace mindspore
