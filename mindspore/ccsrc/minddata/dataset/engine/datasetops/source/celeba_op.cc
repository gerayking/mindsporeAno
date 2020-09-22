/**
 * Copyright 2019 Huawei Technologies Co., Ltd

 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at

 * http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/
#include "minddata/dataset/engine/datasetops/source/celeba_op.h"

#include <fstream>
#include <iomanip>
#include "minddata/dataset/core/config_manager.h"
#include "minddata/dataset/util/path.h"
#include "minddata/dataset/engine/datasetops/source/sampler/sequential_sampler.h"
#include "minddata/dataset/engine/data_schema.h"
#include "minddata/dataset/engine/execution_tree.h"
#include "minddata/dataset/engine/opt/pass.h"
#include "minddata/dataset/kernels/image/image_utils.h"

namespace mindspore {
namespace dataset {
CelebAOp::Builder::Builder() : builder_decode_(false), builder_sampler_(nullptr) {
  std::shared_ptr<ConfigManager> cfg = GlobalContext::config_manager();
  builder_num_workers_ = cfg->num_parallel_workers();
  builder_rows_per_buffer_ = cfg->rows_per_buffer();
  builder_op_connector_size_ = cfg->op_connector_size();
}

Status CelebAOp::Builder::Build(std::shared_ptr<CelebAOp> *op) {
  MS_LOG(DEBUG) << "Celeba dataset directory is " << builder_dir_.c_str() << ".";
  MS_LOG(DEBUG) << "Celeba dataset type is " << builder_dataset_type_.c_str() << ".";
  RETURN_IF_NOT_OK(SanityCheck());
  if (builder_sampler_ == nullptr) {
    const int64_t num_samples = 0;
    const int64_t start_index = 0;
    builder_sampler_ = std::make_shared<SequentialSampler>(start_index, num_samples);
  }

  builder_schema_ = std::make_unique<DataSchema>();
  RETURN_IF_NOT_OK(
    builder_schema_->AddColumn(ColDescriptor("image", DataType(DataType::DE_UINT8), TensorImpl::kFlexible, 1)));
  // label is like this:0 1 0 0 1......
  RETURN_IF_NOT_OK(
    builder_schema_->AddColumn(ColDescriptor("attr", DataType(DataType::DE_UINT32), TensorImpl::kFlexible, 1)));
  *op = std::make_shared<CelebAOp>(builder_num_workers_, builder_rows_per_buffer_, builder_dir_,
                                   builder_op_connector_size_, builder_decode_, builder_dataset_type_,
                                   builder_extensions_, std::move(builder_schema_), std::move(builder_sampler_));
  if (*op == nullptr) {
    return Status(StatusCode::kUnexpectedError, __LINE__, __FILE__, "CelebAOp is null");
  }

  return Status::OK();
}

Status CelebAOp::Builder::SanityCheck() {
  Path dir(builder_dir_);
  std::string err_msg;
  err_msg += dir.IsDirectory() ? "" : "CelebA path is invalid or not set\n";
  err_msg += builder_num_workers_ <= 0 ? "Num of parallel workers is smaller than 1\n" : "";
  return err_msg.empty() ? Status::OK() : Status(StatusCode::kUnexpectedError, __LINE__, __FILE__, err_msg);
}

CelebAOp::CelebAOp(int32_t num_workers, int32_t rows_per_buffer, const std::string &dir, int32_t queue_size,
                   bool decode, const std::string &dataset_type, const std::set<std::string> &exts,
                   std::unique_ptr<DataSchema> schema, std::shared_ptr<Sampler> sampler)
    : ParallelOp(num_workers, queue_size, std::move(sampler)),
      rows_per_buffer_(rows_per_buffer),
      folder_path_(dir),
      decode_(decode),
      extensions_(exts),
      data_schema_(std::move(schema)),
      num_rows_in_attr_file_(0),
      dataset_type_(dataset_type) {
  attr_info_queue_ = std::make_unique<Queue<std::vector<std::string>>>(queue_size);
  io_block_queues_.Init(num_workers_, queue_size);
}

Status CelebAOp::LaunchThreadsAndInitOp() {
  if (tree_ == nullptr) {
    return Status(StatusCode::kUnexpectedError, __LINE__, __FILE__, "tree_ not set");
  }

  RETURN_IF_NOT_OK(io_block_queues_.Register(tree_->AllTasks()));
  RETURN_IF_NOT_OK(attr_info_queue_->Register(tree_->AllTasks()));
  RETURN_IF_NOT_OK(wp_.Register(tree_->AllTasks()));

  RETURN_IF_NOT_OK(tree_->AllTasks()->CreateAsyncTask("Walking attr file", std::bind(&CelebAOp::ParseAttrFile, this)));
  RETURN_IF_NOT_OK(tree_->LaunchWorkers(num_workers_, std::bind(&CelebAOp::WorkerEntry, this, std::placeholders::_1)));
  TaskManager::FindMe()->Post();
  RETURN_IF_NOT_OK(ParseImageAttrInfo());
  RETURN_IF_NOT_OK(sampler_->HandshakeRandomAccessOp(this));

  return Status::OK();
}

Status CelebAOp::ParseAttrFile() {
  TaskManager::FindMe()->Post();
  Path folder_path(folder_path_);
  std::ifstream attr_file((folder_path / "list_attr_celeba.txt").toString());
  if (!attr_file.is_open()) {
    return Status(StatusCode::kFileNotExist, __LINE__, __FILE__, "Celeba attr file does not exist");
  }

  const auto PushBackToQueue = [this](std::vector<std::string> &vec, std::ifstream &attr_file,
                                      std::ifstream &partition_file) {
    Status s = attr_info_queue_->EmplaceBack(vec);
    if (s.IsError()) {
      CLOSE_FILE(attr_file, partition_file);
      return s;
    }
    return Status::OK();
  };

  std::string rows_num;
  std::string attr_name;
  (void)getline(attr_file, rows_num);
  try {
    num_rows_in_attr_file_ = static_cast<int64_t>(std::stoul(rows_num));  // First line is rows number in attr file
  } catch (std::invalid_argument &e) {
    RETURN_STATUS_UNEXPECTED("Conversion to ulong failed, invalid argument.");
  } catch (std::out_of_range &e) {
    RETURN_STATUS_UNEXPECTED("Conversion to ulong failed, out of range.");
  }

  (void)getline(attr_file, attr_name);  // Second line is attribute name,ignore it
  std::string image_info;
  std::vector<std::string> image_infos;
  image_infos.reserve(oc_queue_size_);
  while (getline(attr_file, image_info)) {
    if ((image_info.empty()) || (dataset_type_ != "all" && !CheckDatasetTypeValid())) {
      continue;
    }
    image_infos.push_back(image_info);
    if (image_info.size() % oc_queue_size_ == 0) {
      RETURN_IF_NOT_OK(PushBackToQueue(image_infos, attr_file, partition_file_));
      image_infos.clear();
    }
  }
  if (!image_infos.empty()) {
    RETURN_IF_NOT_OK(PushBackToQueue(image_infos, attr_file, partition_file_));
  }
  std::vector<std::string> end_indicator = std::vector<std::string>(0);
  RETURN_IF_NOT_OK(PushBackToQueue(end_indicator, attr_file, partition_file_));  // end indicator
  CLOSE_FILE(attr_file, partition_file_);
  return Status::OK();
}

bool CelebAOp::CheckDatasetTypeValid() {
  if (!partition_file_.is_open()) {
    Path folder_path(folder_path_);
    partition_file_.open((folder_path / "list_eval_partition.txt").toString());
    if (!partition_file_.is_open()) {
      MS_LOG(ERROR) << "Celeba partition file does not exist!";
      return false;
    }
  }
  std::string line;
  (void)getline(partition_file_, line);
  std::vector<std::string> vec = Split(line);
  if (vec.size() != 2) {
    return false;
  }
  int32_t type;
  try {
    type = std::stoi(vec[1]);
  } catch (std::invalid_argument &e) {
    MS_LOG(WARNING) << "Conversion to unsigned long failed, invalid argument, " << vec[0] << ".";
    return false;
  } catch (std::out_of_range &e) {
    MS_LOG(WARNING) << "Conversion to unsigned long failed, out of range, " << vec[0] << ".";
    return false;
  }
  // train:0, valid=1, test=2
  if (dataset_type_ == "train" && (type == 0)) {
    return true;
  } else if (dataset_type_ == "valid" && (type == 1)) {
    return true;
  } else if (dataset_type_ == "test" && (type == 2)) {
    return true;
  }

  return false;
}

Status CelebAOp::ParseImageAttrInfo() {
  std::vector<std::string> image_infos;
  bool needMoreData = true;
  RETURN_IF_NOT_OK(attr_info_queue_->PopFront(&image_infos));
  while (!image_infos.empty() && needMoreData) {
    for (uint32_t index = 0; index < image_infos.size(); index++) {
      std::string image_info = image_infos[index];
      std::vector<std::string> split = Split(image_info);
      std::pair<std::string, std::vector<int32_t>> image_labels;

      Path path(folder_path_);
      Path file_path = path / split[0];
      if (!extensions_.empty() && extensions_.find(file_path.Extension()) == extensions_.end()) {
        MS_LOG(WARNING) << "Unsupported file found at " << file_path.toString().c_str() << ", its extension is "
                        << file_path.Extension().c_str() << ".";
        continue;
      }
      image_labels.first = split[0];
      for (uint32_t label_index = 1; label_index < split.size(); label_index++) {
        int32_t value;
        try {
          value = std::stoi(split[label_index]);
        } catch (std::invalid_argument &e) {
          RETURN_STATUS_UNEXPECTED("Conversion to int failed, invalid argument.");
        } catch (std::out_of_range &e) {
          RETURN_STATUS_UNEXPECTED("Conversion to int failed, out of range.");
        }
        image_labels.second.push_back(value);
      }

      image_labels_vec_.push_back(image_labels);
    }

    RETURN_IF_NOT_OK(attr_info_queue_->PopFront(&image_infos));
  }

  num_rows_ = image_labels_vec_.size();
  if (num_rows_ == 0) {
    RETURN_STATUS_UNEXPECTED(
      "There is no valid data matching the dataset API CelebADataset.Please check file path or dataset API "
      "validation first.");
  }
  MS_LOG(DEBUG) << "Celeba dataset rows number is " << num_rows_ << ".";
  return Status::OK();
}

std::vector<std::string> CelebAOp::Split(const std::string &line) {
  std::string str = line;
  std::string::size_type pos;
  std::vector<std::string> split;
  str += " ";
  int size = str.size();
  for (uint32_t index = 0; index < size;) {
    pos = str.find(" ", index);
    if (pos != index) {  // skip space
      std::string s = str.substr(index, pos - index);
      split.push_back(s);
    }
    index = pos + 1;
  }

  return split;
}

// Main logic, Register Queue with TaskGroup, launch all threads and do the functor's work
Status CelebAOp::operator()() {
  RETURN_IF_NOT_OK(LaunchThreadsAndInitOp());
  std::unique_ptr<DataBuffer> data_buffer;
  RETURN_IF_NOT_OK(sampler_->GetNextSample(&data_buffer));
  RETURN_IF_NOT_OK(AddIOBlock(&data_buffer));
  return Status::OK();
}

Status CelebAOp::AddIOBlock(std::unique_ptr<DataBuffer> *data_buffer) {
  int64_t buff_count = 0;
  while (true) {
    std::vector<int64_t> keys;
    keys.reserve(rows_per_buffer_);
    int64_t row_count = 0;
    while (!(*data_buffer)->eoe()) {
      TensorRow sample_row;
      RETURN_IF_NOT_OK((*data_buffer)->PopRow(&sample_row));
      std::shared_ptr<Tensor> sample_ids = sample_row[0];
      for (auto itr = sample_ids->begin<int64_t>(); itr != sample_ids->end<int64_t>(); ++itr) {
        if ((*itr) >= num_rows_) {
          MS_LOG(WARNING) << "Sample Id (" << *itr << ") is out of bounds, skipping. Max id is " << num_rows_ << ".";
          continue;
        }
        keys.push_back(*itr);
        row_count++;
        if (row_count % rows_per_buffer_ == 0) {
          RETURN_IF_NOT_OK(io_block_queues_[buff_count++ % num_workers_]->Add(
            std::make_unique<IOBlock>(IOBlock(keys, IOBlock::kDeIoBlockNone))));
          keys.clear();
        }
      }
      RETURN_IF_NOT_OK(sampler_->GetNextSample(data_buffer));
    }

    if (!keys.empty()) {
      RETURN_IF_NOT_OK(io_block_queues_[(buff_count++) % num_workers_]->Add(
        std::make_unique<IOBlock>(IOBlock(keys, IOBlock::kDeIoBlockNone))));
    }
    if (IsLastIteration()) {
      RETURN_IF_NOT_OK(
        io_block_queues_[(buff_count++) % num_workers_]->Add(std::make_unique<IOBlock>(IOBlock::kDeIoBlockFlagEoe)));
      RETURN_IF_NOT_OK(
        io_block_queues_[(buff_count++) % num_workers_]->Add(std::make_unique<IOBlock>(IOBlock::kDeIoBlockFlagEof)));
      for (int32_t i = 0; i < num_workers_; i++) {
        RETURN_IF_NOT_OK(
          io_block_queues_[i]->Add(std::make_unique<IOBlock>(std::vector<int64_t>(), IOBlock::kDeIoBlockNone)));
      }
      return Status::OK();
    } else {  // not the last repeat. Acquire lock, sleeps master thread, wait for the wake-up from reset
      RETURN_IF_NOT_OK(
        io_block_queues_[(buff_count++) % num_workers_]->Add(std::make_unique<IOBlock>(IOBlock::kDeIoBlockFlagEoe)));
      RETURN_IF_NOT_OK(wp_.Wait());  // Master thread goes to sleep after it has made all the IOBlocks
      wp_.Clear();
      RETURN_IF_NOT_OK(sampler_->GetNextSample(data_buffer));
    }
    UpdateRepeatAndEpochCounter();
  }
}

Status CelebAOp::WorkerEntry(int32_t worker_id) {
  TaskManager::FindMe()->Post();
  int64_t buffer_id = worker_id;
  std::unique_ptr<IOBlock> io_block;
  RETURN_IF_NOT_OK(io_block_queues_[worker_id]->PopFront(&io_block));
  while (io_block != nullptr) {
    if (io_block->eoe() == true) {
      RETURN_IF_NOT_OK(out_connector_->Add(worker_id, std::make_unique<DataBuffer>(0, DataBuffer::kDeBFlagEOE)));
      buffer_id = worker_id;
    } else if (io_block->eof() == true) {
      RETURN_IF_NOT_OK(out_connector_->Add(worker_id, std::make_unique<DataBuffer>(0, DataBuffer::kDeBFlagEOF)));
    } else {
      std::vector<int64_t> keys;
      RETURN_IF_NOT_OK(io_block->GetKeys(&keys));
      if (keys.empty()) {
        return Status::OK();  // empty key is a quit signal for workers
      }
      std::unique_ptr<DataBuffer> db = std::make_unique<DataBuffer>(buffer_id, DataBuffer::kDeBFlagNone);
      RETURN_IF_NOT_OK(LoadBuffer(keys, &db));
      RETURN_IF_NOT_OK(out_connector_->Add(worker_id, std::move(db)));
      buffer_id += num_workers_;
    }
    RETURN_IF_NOT_OK(io_block_queues_[worker_id]->PopFront(&io_block));
  }
  return Status(StatusCode::kUnexpectedError, __LINE__, __FILE__, "Unexpected nullptr received in worker");
}

Status CelebAOp::LoadBuffer(const std::vector<int64_t> &keys, std::unique_ptr<DataBuffer> *db) {
  std::unique_ptr<TensorQTable> deq = std::make_unique<TensorQTable>();
  for (const auto &key : keys) {
    TensorRow row;
    RETURN_IF_NOT_OK(LoadTensorRow(key, image_labels_vec_[key], &row));
    deq->push_back(std::move(row));
  }

  (*db)->set_tensor_table(std::move(deq));
  return Status::OK();
}

Status CelebAOp::LoadTensorRow(row_id_type row_id, const std::pair<std::string, std::vector<int32_t>> &image_label,
                               TensorRow *row) {
  std::shared_ptr<Tensor> image;
  std::shared_ptr<Tensor> label;

  Path path(folder_path_);
  Path image_path = path / image_label.first;
  RETURN_IF_NOT_OK(Tensor::CreateFromFile(image_path.toString(), &image));
  if (decode_ == true) {
    Status rc = Decode(image, &image);
    if (rc.IsError()) {
      image = nullptr;
      std::string err_msg = "Fail to decode image: " + image_path.toString();
      return Status(StatusCode::kUnexpectedError, __LINE__, __FILE__, err_msg);
    }
  }

  RETURN_IF_NOT_OK(
    Tensor::CreateEmpty(TensorShape({1, (uint32_t)image_label.second.size()}), data_schema_->column(1).type(), &label));
  RETURN_IF_NOT_OK(label->Zero());
  for (uint32_t index = 0; index < image_label.second.size(); index++) {
    if (image_label.second[index] == 1) {
      label->SetItemAt<uint32_t>({0, static_cast<dsize_t>(index)}, 1);
    } else {
      label->SetItemAt<uint32_t>({0, static_cast<dsize_t>(index)}, 0);
    }
  }
  label->Squeeze();

  (*row) = TensorRow(row_id, {std::move(image), std::move(label)});
  return Status::OK();
}

void CelebAOp::Print(std::ostream &out, bool show_all) const {
  if (!show_all) {
    // Call the super class for displaying any common 1-liner info
    ParallelOp::Print(out, show_all);
    // Then show any custom derived-internal 1-liner info for this op
    out << "\n";
  } else {
    // Call the super class for displaying any common detailed info
    ParallelOp::Print(out, show_all);
    // Then show any custom derived-internal stuff
    out << "\nNumber of rows:" << num_rows_ << "\nceleba dir: " << folder_path_ << "\n\n";
  }
}

// Reset Sampler and wakeup Master thread (functor)
Status CelebAOp::Reset() {
  RETURN_IF_NOT_OK(sampler_->ResetSampler());
  wp_.Set();  // wake up master thread after reset is done
  return Status::OK();
}

// Visitor accept method for NodePass
Status CelebAOp::Accept(NodePass *p, bool *modified) {
  // Downcast shared pointer then call visitor
  return p->RunOnNode(shared_from_base<CelebAOp>(), modified);
}

Status CelebAOp::ComputeColMap() {
  // Set the column name map (base class field)
  if (column_name_id_map_.empty()) {
    for (int32_t index = 0; index < data_schema_->NumColumns(); index++) {
      column_name_id_map_[data_schema_->column(index).name()] = index;
    }
  } else {
    MS_LOG(WARNING) << "Column name map is already set!";
  }
  return Status::OK();
}
}  // namespace dataset
}  // namespace mindspore
