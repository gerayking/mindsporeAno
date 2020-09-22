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

#ifndef MINDSPORE_CCSRC_MINDDATA_DATASET_ENGINE_OPT_PASS_H_
#define MINDSPORE_CCSRC_MINDDATA_DATASET_ENGINE_OPT_PASS_H_

#include <memory>
#include <queue>

#include "minddata/dataset/engine/execution_tree.h"
#include "minddata/dataset/util/status.h"

namespace mindspore {
namespace dataset {
class BatchOp;

class MapOp;

class ProjectOp;

class RenameOp;

class SkipOp;

class ShuffleOp;

#ifndef ENABLE_ANDROID
class MindRecordOp;

class TFReaderOp;
#endif

#ifdef ENABLE_PYTHON
class FilterOp;

class GeneratorOp;
#endif

class RandomDataOp;

class RepeatOp;

class TakeOp;

class ZipOp;

class DeviceQueueOp;

class ImageFolderOp;

class CacheOp;

class MnistOp;

class ManifestOp;

class CifarOp;

class VOCOp;

class CocoOp;

class CelebAOp;

class CacheMergeOp;

class CacheLookupOp;

class EpochCtrlOp;

class BuildVocabOp;

class BuildSentencePieceVocabOp;

// The base class Pass is the basic unit of tree transformation.
// The actual implementation of the passes will be derived from here.
class Pass : public std::enable_shared_from_this<Pass> {
 public:
  // Run the transformation pass against the execution tree.
  // @param tree - Pointer to the execution tree to be transformed.
  // @param modified - Pointer to the modified flag,
  virtual Status Run(ExecutionTree *tree, bool *modified) = 0;

  virtual ~Pass() = default;
};

// TreePass is a basic Pass class which performs transformation on ExecutionTree directly.
class TreePass : public Pass {
 public:
  /// \brief Run the transformation pass against the execution tree.
  /// \param[inout] tree Pointer to the execution tree to be transformed.
  /// \param[inout] modified Indicate if the tree was modified
  Status Run(ExecutionTree *tree, bool *modified) final;

  /// \brief Derived classes may implement the runOnTree function to implement tree transformation.
  ///     "modified" flag needs to be set to true if tree is modified during the pass execution.
  /// \param[inout] tree The tree to operate on.
  /// \param[inout] Indicate of the tree was modified.
  /// \return Status The error code return
  virtual Status RunOnTree(ExecutionTree *tree, bool *modified) { return Status::OK(); }
};

// NodePass is a basic Pass class which performs transformation on Node visiting.
// NodePass implements Visitor design pattern.
class NodePass : public Pass {
 public:
  // Tree traversal order
  enum Order { DFS, BFS };

  // Constructor
  // Default DFS traversal
  explicit NodePass(Order order = Order::DFS) { traversalOrder_ = order; }

  ~NodePass() = default;

  /// \brief Run the transformation pass against the execution tree
  /// \param[inout] tree Pointer to the execution tree to be transformed
  /// \param[inout] modified Indicator if the tree was changed
  Status Run(ExecutionTree *tree, bool *modified) final;

  /// \brief Derived classes may implement the PreRunOnNode function to implement any initial visit work on the way down
  ///     a tree traversal.  "modified" flag needs to be set to true if tree is modified during the pass execution
  /// \param[in] node The node being visited
  /// \param[out] modified Indicator if the node was changed at all
  /// \return Status The error code return
  virtual Status PreRunOnNode(std::shared_ptr<DatasetOp> node, bool *modified) { return Status::OK(); }

  /// \brief Derived classes may implement the RunOnNode function to implement node level tree transformation
  ///     "modified" flag needs to be set to true if tree is modified during the pass execution
  /// \param[in] node The node being visited
  /// \param[out] modified Indicator if the node was changed at all.
  /// \return Status The error code return
  virtual Status RunOnNode(std::shared_ptr<DatasetOp> node, bool *modified) { return Status::OK(); }

  // Visit methods to be overridden.
  // Note that member template can not be virtual, any op which wants to work with NodePass should declare RunOnNode
  // of its own type and override "Accept" from DatasetOp.
  virtual Status RunOnNode(std::shared_ptr<BatchOp> node, bool *modified);

  virtual Status RunOnNode(std::shared_ptr<MapOp> node, bool *modified);

  virtual Status RunOnNode(std::shared_ptr<ProjectOp> node, bool *modified);

  virtual Status RunOnNode(std::shared_ptr<RenameOp> node, bool *modified);

  virtual Status RunOnNode(std::shared_ptr<SkipOp> node, bool *modified);

  virtual Status RunOnNode(std::shared_ptr<ShuffleOp> node, bool *modified);

#ifndef ENABLE_ANDROID
  virtual Status RunOnNode(std::shared_ptr<MindRecordOp> node, bool *modified);

  virtual Status RunOnNode(std::shared_ptr<TFReaderOp> node, bool *modified);
#endif

#ifdef ENABLE_PYTHON
  virtual Status RunOnNode(std::shared_ptr<FilterOp> node, bool *modified);

  virtual Status RunOnNode(std::shared_ptr<ManifestOp> node, bool *modified);

  virtual Status RunOnNode(std::shared_ptr<GeneratorOp> node, bool *modified);

  virtual Status RunOnNode(std::shared_ptr<VOCOp> node, bool *modified);
#endif

  virtual Status RunOnNode(std::shared_ptr<RandomDataOp> node, bool *modified);

  virtual Status RunOnNode(std::shared_ptr<TakeOp> node, bool *modified);

  virtual Status RunOnNode(std::shared_ptr<ZipOp> node, bool *modified);

  virtual Status RunOnNode(std::shared_ptr<DeviceQueueOp> node, bool *modified);

  virtual Status RunOnNode(std::shared_ptr<CacheOp> node, bool *modified);

  virtual Status RunOnNode(std::shared_ptr<ImageFolderOp> node, bool *modified);

  virtual Status RunOnNode(std::shared_ptr<MnistOp> node, bool *modified);

  virtual Status RunOnNode(std::shared_ptr<CifarOp> node, bool *modified);

  virtual Status RunOnNode(std::shared_ptr<CocoOp> node, bool *modified);

  virtual Status RunOnNode(std::shared_ptr<CelebAOp> node, bool *modified);

  virtual Status RunOnNode(std::shared_ptr<RepeatOp> node, bool *modified);

  virtual Status RunOnNode(std::shared_ptr<CacheMergeOp> node, bool *modified);

  virtual Status RunOnNode(std::shared_ptr<CacheLookupOp> node, bool *modified);

  virtual Status RunOnNode(std::shared_ptr<EpochCtrlOp> node, bool *modified);

  virtual Status PreRunOnNode(std::shared_ptr<CacheOp> node, bool *modified);

  virtual Status PreRunOnNode(std::shared_ptr<RepeatOp> node, bool *modified);

  virtual Status PreRunOnNode(std::shared_ptr<CacheMergeOp> node, bool *modified);

  virtual Status PreRunOnNode(std::shared_ptr<EpochCtrlOp> node, bool *modified);

  virtual Status PreRunOnNode(std::shared_ptr<BuildVocabOp> node, bool *modified);

  virtual Status PreRunOnNode(std::shared_ptr<BuildSentencePieceVocabOp> node, bool *modified);

 private:
  // Helper function to perform DFS visit
  Status DFSNodeVisit(std::shared_ptr<DatasetOp> node, bool *modified);

  // Helper function to perform BFS visit
  Status BFSNodeVisit(std::shared_ptr<DatasetOp> root, bool *modified);

  // Tree traversal order of the NodePass
  Order traversalOrder_;
};

}  // namespace dataset
}  // namespace mindspore

#endif  // MINDSPORE_CCSRC_MINDDATA_DATASET_ENGINE_OPT_PASS_H_
