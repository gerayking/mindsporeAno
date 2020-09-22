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

#ifndef MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_NNACL_PRELU_PARAMETER_H_
#define MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_NNACL_PRELU_PARAMETER_H_

#include "nnacl/op_base.h"
#include "nnacl/quantization/quantize.h"

#define PRELU_OFFSET_MAX_SIZE 65535

typedef struct PreluParameter {
  OpParameter op_parameter_;
  PreluQuantArg quant_arg;
  double alpha_;
  int thread_count_;
  float slope_[PRELU_OFFSET_MAX_SIZE];
  int64_t in_offset_[PRELU_OFFSET_MAX_SIZE];
  int64_t axis_;
  const int *in_shape_;
  const int *out_shape_;
  int input_dim_;
  int element_num;
} PreluParameter;

#endif  // MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_NNACL_PRELU_PARAMETER_H_
