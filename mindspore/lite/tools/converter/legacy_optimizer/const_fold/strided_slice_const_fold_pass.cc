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

#include "tools/converter/legacy_optimizer/const_fold/strided_slice_const_fold_pass.h"
#include "src/operator/cpu/creator/strided_slice.h"

namespace mindspore {
namespace lite {
STATUS StridedSliceConstFoldPass::Run(GraphNode *graphNode) { return ConstFoldPass::Run(graphNode); }

STATUS StridedSliceConstFoldPass::CreateOp(SubGraphDefT *subGraph, OpDefT *node) {
  InnerContext ctx;
  OpDesc desc{};
  desc.type = OpT_Slice;
  desc.arch = kCPU;
  op = new (std::nothrow) OpStridedSlice(inputs, outputs, *PackOpDefT(node), &ctx, desc);
  if (op == nullptr) {
    MS_LOGE("new OpStridedSlice return nullptr");
    return RET_ERROR;
  }
  auto ret = op->InferShape(inputs, outputs);
  if (ret != RET_OK) {
    MS_LOGE("OpStridedSlice InferShape Failed");
    return RET_ERROR;
  }
  ret = op->Init(inputs, outputs);
  if (ret != RET_OK) {
    MS_LOGE("OpStridedSlice Init Failed");
    return RET_ERROR;
  }
  return RET_OK;
}

STATUS StridedSliceConstFoldPass::DoFold(SubGraphDefT *subGraph, OpDefT *node) {
  MS_ASSERT(op != nullptr);
  auto ret = op->Execute(inputs, outputs);
  if (ret != RET_OK) {
    MS_LOGE("OpStridedSlice Execute Failed");
    return RET_ERROR;
  }

  if (node->outputIndex.size() != kStridedSliceOutputNum) {
    MS_LOGE("The number of output for slice must be %u, nodeName: %s", kStridedSliceOutputNum, node->name.c_str());
    return RET_ERROR;
  }
  this->outputTensor = subGraph->allTensors.at(node->outputIndex.front()).get();
  CopyTensor2TensorDefT(outputs.front(), this->outputTensor);
  return RET_OK;
}
}  // namespace lite
}  // namespace mindspore

