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
#ifndef MINDSPORE_CCSRC_MINDDATA_DATASET_KERNELS_DATA_SLICE_OP_H_
#define MINDSPORE_CCSRC_MINDDATA_DATASET_KERNELS_DATA_SLICE_OP_H_

#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "minddata/dataset/core/tensor.h"
#include "minddata/dataset/kernels/tensor_op.h"

namespace mindspore {
namespace dataset {
class Slice {
 public:
  Slice() : start_(0), stop_(0), step_(0) {}
  Slice(dsize_t start, dsize_t stop, dsize_t step) : start_(start), stop_(stop), step_(step) {}
  Slice(dsize_t start, dsize_t stop) : start_(start), stop_(stop), step_(1) {}
  explicit Slice(dsize_t stop) : start_(0), stop_(stop), step_(1) {}

  ~Slice() = default;

  std::vector<dsize_t> Indices(dsize_t length) {
    std::vector<dsize_t> indices;
    dsize_t index = std::min(Tensor::HandleNeg(start_, length), length);
    dsize_t end_index = std::min(Tensor::HandleNeg(stop_, length), length);
    if (step_ > 0) {
      for (; index < end_index; index += step_) {
        indices.push_back(index);
      }
    } else {
      for (; index > end_index; index += step_) {
        indices.push_back(index);
      }
    }
    return indices;
  }

  bool valid() { return !(start_ == 0 && stop_ == 0 && step_ == 0); }

  dsize_t start_;
  dsize_t stop_;
  dsize_t step_;
};

class SliceOp : public TensorOp {
 public:
  explicit SliceOp(std::vector<dsize_t> indices) : indices_(std::move(indices)) {}
  explicit SliceOp(Slice slice) : slice_(slice) {}
  explicit SliceOp(bool all) : all_(all) {}

  ~SliceOp() override = default;

  Status Compute(const std::shared_ptr<Tensor> &input, std::shared_ptr<Tensor> *output) override;

  std::string Name() const override { return kSliceOp; }

 private:
  // only on of the following will be valid
  // given indices to slice the Tensor. Empty vector if invalid.
  std::vector<dsize_t> indices_;
  // Slice object. All start, stop and step are 0 if invalid.
  Slice slice_;
  // Flag to read all indcies in the dim.
  bool all_ = false;
};
}  // namespace dataset
}  // namespace mindspore
#endif  // MINDSPORE_CCSRC_MINDDATA_DATASET_KERNELS_DATA_SLICE_OP_H_
