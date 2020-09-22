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

#ifndef MINDSPORE_CCSRC_MINDDATA_DATASET_CORE_TENSOR_ROW_H_
#define MINDSPORE_CCSRC_MINDDATA_DATASET_CORE_TENSOR_ROW_H_

#include <deque>
#include <memory>
#include <vector>

#include "minddata/dataset/core/tensor.h"

namespace mindspore {
namespace dataset {

class TensorRow;                             // A set of Tensor pointers with an id
using TensorTable = std::vector<TensorRow>;  // The table of tensors is a vector of rows
using TensorQTable = std::deque<TensorRow>;  // A different flavour of tensor table, this one has queue functionality

class TensorRow {
 public:
  static constexpr row_id_type kDefaultRowId = -1;  // Default row id

  // Type definitions
  using size_type = dsize_t;
  using value_type = std::shared_ptr<Tensor>;
  using reference = std::shared_ptr<Tensor> &;
  using const_reference = const std::shared_ptr<Tensor> &;
  using vector_type = std::vector<std::shared_ptr<Tensor>>;
  using iterator = std::vector<std::shared_ptr<Tensor>>::iterator;
  using const_iterator = std::vector<std::shared_ptr<Tensor>>::const_iterator;

  TensorRow() noexcept;

  TensorRow(size_type n, value_type t) noexcept;

  // Copy Constructors
  explicit TensorRow(const vector_type &v);

  TensorRow(row_id_type id, const std::initializer_list<value_type> &lst);

  TensorRow(const TensorRow &tr);

  TensorRow &operator=(const TensorRow &tr);

  TensorRow &operator=(const std::initializer_list<value_type> &lst);

  // Move Constructors
  explicit TensorRow(vector_type &&v) noexcept;

  TensorRow(row_id_type id, std::initializer_list<value_type> &&lst) noexcept;

  TensorRow(TensorRow &&tr) noexcept;

  TensorRow &operator=(TensorRow &&tr) noexcept;

  TensorRow &operator=(std::initializer_list<value_type> &&lst) noexcept;

  // Destructor
  ~TensorRow() = default;

  // Functions to fetch/set id/vector
  row_id_type getId() const { return id_; }

  void setId(row_id_type id) { id_ = id; }

  const vector_type &getRow() const { return row_; }

  // Wrapper functions to support vector operations
  void emplace_back(value_type t) { row_.emplace_back(t); }

  void push_back(value_type t) { row_.push_back(t); }

  void clear() noexcept { row_.clear(); }

  size_type size() const noexcept { return row_.size(); }

  void reserve(size_type size) { row_.reserve(size); }

  void resize(size_type size) { row_.resize(size); }

  bool empty() { return row_.empty(); }

  void insert(iterator position, iterator first, iterator last) { row_.insert(position, first, last); }

  // Wrapper functions to support vector element access
  reference at(size_type index) { return row_.at(index); }

  const_reference at(size_type index) const { return row_.at(index); }

  reference front() { return row_.front(); }

  const_reference front() const { return row_.front(); }

  reference back() { return row_.back(); }

  const_reference back() const { return row_.back(); }

  reference operator[](size_type index) { return row_[index]; }

  const_reference operator[](size_type index) const { return row_[index]; }

  // Wrapper functions to support vector iteration
  iterator begin() { return row_.begin(); }

  const_iterator begin() const { return row_.begin(); }

  iterator end() { return row_.end(); }

  const_iterator end() const { return row_.end(); }

 protected:
  row_id_type id_;
  std::vector<std::shared_ptr<Tensor>> row_;
};
}  // namespace dataset
}  // namespace mindspore
#endif  // MINDSPORE_CCSRC_MINDDATA_DATASET_CORE_TENSOR_ROW_H_
