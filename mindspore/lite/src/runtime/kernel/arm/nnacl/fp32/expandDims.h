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

#ifndef MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_NNACL_EXPANDDIMS_H_
#define MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_NNACL_EXPANDDIMS_H_

#include "nnacl/op_base.h"

typedef struct ExpandDimsParameter {
  OpParameter op_parameter_;
  int dim_;
} ExpandDimsParameter;

#ifdef __cplusplus
extern "C" {
#endif
int ExpandDims(float *input_ptr, float *output_ptr, size_t data_size);
#ifdef __cplusplus
}
#endif

#endif  // MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_NNACL_EXPANDDIMS_H_
