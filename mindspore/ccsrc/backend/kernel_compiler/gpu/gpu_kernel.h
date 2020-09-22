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

#ifndef MINDSPORE_CCSRC_BACKEND_KERNEL_COMPILER_GPU_GPUKERNEL_H_
#define MINDSPORE_CCSRC_BACKEND_KERNEL_COMPILER_GPU_GPUKERNEL_H_

#include <cuda.h>
#include <cudnn.h>
#include <string>
#include <vector>
#include "backend/kernel_compiler/kernel.h"
#include "backend/kernel_compiler/gpu/kernel_constants.h"
#include "runtime/device/gpu/gpu_device_manager.h"
#include "runtime/device/gpu/gpu_common.h"
#include "backend/session/anf_runtime_algorithm.h"
using AnfAlgo = mindspore::session::AnfRuntimeAlgorithm;

namespace mindspore {
namespace kernel {
class GpuKernel : public KernelMod {
 public:
  virtual ~GpuKernel() = default;
  virtual bool Init(const CNodePtr &kernel_node) = 0;

 protected:
  virtual void InitResource() {}
  virtual void InitSizeLists() = 0;

  template <typename T>
  inline T *GetDeviceAddress(const std::vector<AddressPtr> &addr_list, size_t index) {
    if (index >= addr_list.size()) {
      MS_LOG(EXCEPTION) << "Address index(" << index << ") out of range(" << addr_list.size() << ")";
    }
    // Kernels may run normally without workspace, the addr_list[index] maybe nullptr.
    if ((addr_list[index] == nullptr) || (addr_list[index]->size == 0)) {
      return nullptr;
    }
    MS_EXCEPTION_IF_NULL(addr_list[index]->addr);
    return reinterpret_cast<T *>(addr_list[index]->addr);
  }

  template <typename T>
  inline T GetAttr(const CNodePtr &kernel_node, const std::string &key) const {
    const PrimitivePtr &prim = AnfAlgo::GetCNodePrimitive(kernel_node);
    const ValuePtr &attr = prim->GetAttr(key);
    if (attr == nullptr) {
      const std::string &prim_name = AnfAlgo::GetCNodeName(kernel_node);
      MS_LOG(EXCEPTION) << "The attr(" << key << ") of kernel(" << prim_name << ") not exist";
    }
    return GetValue<T>(attr);
  }
  // expand Nd Shape to 4d (N in [0,4])
  void ShapeNdTo4d(const std::vector<size_t> &src, std::vector<int> *dst) {
    if (src.size() > 4) {
      MS_EXCEPTION(ValueError) << src.size() << "-D data is not supported!";
    }
    dst->push_back(src.size() < 4 ? 1 : SizeToInt(src[src.size() - 4]));
    dst->push_back(src.size() < 3 ? 1 : SizeToInt(src[src.size() - 3]));
    dst->push_back(src.size() < 2 ? 1 : SizeToInt(src[src.size() - 2]));
    dst->push_back(src.size() == 0 ? 1 : SizeToInt(src[src.size() - 1]));
  }

  inline void CheckBroadcast4TensorOp(const std::vector<int> &A, const std::vector<int> &B,
                                      const std::vector<int> &Out) {
    if (A != Out && B != Out) {
      MS_EXCEPTION(ValueError)
        << "Double-sided broadcast was not supported in cudnn of cudnnOpTensor:\n"
           "InputA must match the corresponding dimension of the destination tensor outC, and each "
           "dimension of the inputB "
           "must match the corresponding dimension of outC or must be equal to 1.";
    }
  }

  // set the tensor descriptor for cudnn/cublas
  void CudnnSetTensorNdDescriptor(const std::vector<size_t> &shape, cudnnTensorDescriptor_t descriptor,
                                  cudnnDataType_t data_type) {
    if (shape.size() < 3) {
      MS_EXCEPTION(ValueError) << "cudnnSetTensorNdDescriptor don't support" << shape.size() << "D.";
    }
    const int nbDims = shape.size();
    int *dim = new (std::nothrow) int[nbDims];
    if (dim == nullptr) {
      MS_LOG(EXCEPTION) << "malloc dim failed.";
    }
    int *stride = new (std::nothrow) int[nbDims];
    if (stride == nullptr) {
      MS_LOG(EXCEPTION) << "malloc stride failed.";
    }

    for (int i = 0; i < nbDims; i++) {
      dim[i] = SizeToInt(shape[i]);
      stride[i] = 1;
    }

    for (int i = nbDims - 2; i >= 0; i--) {
      stride[i] = stride[i + 1] * SizeToInt(shape[i + 1]);
    }

    CHECK_CUDNN_RET_WITH_EXCEPT(cudnnSetTensorNdDescriptor(descriptor, data_type, nbDims, dim, stride),
                                "cudnnSetTensorNdDescriptor failed");

    delete[] dim;
    dim = nullptr;
    delete[] stride;
    stride = nullptr;
  }

  // choose the suitable datatype for cudnn/cublas
  inline cudnnDataType_t GetCudnnDataType(const std::string &Type) {
    auto type = kCudnnDtypeMap.find(Type);
    if (type == kCudnnDtypeMap.end()) {
      MS_EXCEPTION(TypeError) << Type << " is not supported.";
    }
    return type->second;
  }
  inline cudaDataType_t GetCudaDataType(const std::string &Type) {
    auto type = kCudaDtypeMap.find(Type);
    if (type == kCudaDtypeMap.end()) {
      MS_EXCEPTION(TypeError) << Type << " is not supported.";
    }
    return type->second;
  }
};
}  // namespace kernel
}  // namespace mindspore

#endif  // MINDSPORE_CCSRC_BACKEND_KERNEL_COMPILER_GPU_GPUKERNEL_H_
