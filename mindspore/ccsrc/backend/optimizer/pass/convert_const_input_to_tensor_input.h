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
#ifndef MINDSPORE_CCSRC_BACKEND_OPTIMIZER_PASS_CONVERT_CONST_INPUT_TO_TENSOR_INPUT_H_
#define MINDSPORE_CCSRC_BACKEND_OPTIMIZER_PASS_CONVERT_CONST_INPUT_TO_TENSOR_INPUT_H_
#include <string>

#include "ir/anf.h"
#include "utils/convert_utils.h"
#include "backend/optimizer/common/optimizer.h"

namespace mindspore {
namespace opt {
class ConvertConstInputToTensorInput : public PatternProcessPass {
 public:
  explicit ConvertConstInputToTensorInput(bool multigraph = true)
      : PatternProcessPass("convert_const_input_to_tensor_input", multigraph) {}
  ~ConvertConstInputToTensorInput() override = default;
  const AnfNodePtr Process(const FuncGraphPtr &, const AnfNodePtr &, const EquivPtr &) const override;
};
}  // namespace opt
}  // namespace mindspore

#endif  // MINDSPORE_CCSRC_BACKEND_OPTIMIZER_PASS_CONVERT_CONST_INPUT_TO_TENSOR_INPUT_H_
