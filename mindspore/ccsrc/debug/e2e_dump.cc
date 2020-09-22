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
#include "debug/e2e_dump.h"
#include <limits.h>
#include <fstream>
#include <string>
#include <optional>
#include <nlohmann/json.hpp>
#include "utils/log_adapter.h"
#include "utils/system/file_system.h"
#include "utils/system/env.h"
#include "utils/convert_utils.h"
#include "utils/ms_context.h"
#include "debug/common.h"

using json = nlohmann::json;

namespace mindspore {
Dump::Dump()
    : dump_enable_(false),
      trans_flag_(false),
      dump_path_("/tmp/"),
      dump_net_name_("net_name"),
      dump_mode_(0),
      dump_iter_(0),
      cur_iter_(0) {}

bool Dump::IsKernelNeedDump(const std::string &kernel_name) {
  if (dump_mode_ == 0) {
    // Dump All Kernels mode
    return true;
  } else {
    auto iter = std::find(dump_kernels_.begin(), dump_kernels_.end(), kernel_name);
    if (iter != dump_kernels_.end()) {
      return true;
    }
  }
  return false;
}

bool Dump::ParseDumpConfig(const std::string &dump_config_file) {
  std::ifstream jsonFile(dump_config_file);
  if (!jsonFile.is_open()) {
    MS_LOG(ERROR) << dump_config_file << " open failed.";
    dump_enable_ = false;
    return false;
  }
  json j;
  jsonFile >> j;
  if (j.find("DumpSettings") == j.end()) {
    MS_LOG(ERROR) << "DumpSettings is not exist.";
    dump_enable_ = false;
    return false;
  } else {
    json dumpSettings = j.at("DumpSettings");
    // convert json to string
    std::stringstream ss;
    ss << dumpSettings;
    std::string cfg = ss.str();
    MS_LOG(INFO) << "E2E Dump Settings Json: " << cfg;
    if (!IsConfigExist(dumpSettings)) {
      return false;
    }
    if (!IsConfigValid(dumpSettings)) {
      return false;
    }
  }
  return true;
}

bool Dump::IsConfigExist(const nlohmann::json &dumpSettings) {
  if (dumpSettings.find("trans_flag") == dumpSettings.end() || dumpSettings.find("enable") == dumpSettings.end() ||
      dumpSettings.find("mode") == dumpSettings.end() || dumpSettings.find("path") == dumpSettings.end() ||
      dumpSettings.find("net_name") == dumpSettings.end() || dumpSettings.find("iteration") == dumpSettings.end() ||
      dumpSettings.find("kernels") == dumpSettings.end()) {
    MS_LOG(ERROR) << "DumpSettings keys is not exist.";
    dump_enable_ = false;
    return false;
  }
  return true;
}

bool Dump::IsConfigValid(const nlohmann::json &dumpSettings) {
  auto trans_flag = dumpSettings.at("trans_flag");
  auto enable = dumpSettings.at("enable");
  auto mode = dumpSettings.at("mode");
  auto path = dumpSettings.at("path");
  auto net_name = dumpSettings.at("net_name");
  auto iteration = dumpSettings.at("iteration");
  auto kernels = dumpSettings.at("kernels");
  if (!(enable.is_boolean() && trans_flag.is_boolean() && mode.is_number() && path.is_string() &&
        net_name.is_string() && iteration.is_number() && kernels.is_array())) {
    MS_LOG(ERROR) << "Element's type in Dump config json is invalid.";
    dump_enable_ = false;
    return false;
  }

  dump_enable_ = enable;
  auto context_ptr = MsContext::GetInstance();
  MS_EXCEPTION_IF_NULL(context_ptr);
  // dump_enable_ is true, close mem reuse
  context_ptr->set_enable_mem_reuse(!dump_enable_);
  trans_flag_ = trans_flag;
  dump_mode_ = mode;
  dump_path_ = path;
  dump_net_name_ = net_name;
  dump_iter_ = iteration;
  for (const auto &kernel : kernels) {
    dump_kernels_.push_back(kernel);
  }
  return true;
}

bool Dump::SetDumpConfFromJsonFile() {
  const char *config_path_str = std::getenv("MINDSPORE_CONFIG_PATH");
  if (config_path_str != nullptr) {
    MS_LOG(INFO) << "Getenv MINDSPORE_CONFIG_PATH :" << config_path_str;
  } else {
    MS_LOG(INFO) << "No need E2E Dump. please export MINDSPORE_CONFIG_PATH eg: MINDSPORE_CONFIG_PATH=/etc";
    dump_enable_ = false;
    return false;
  }
  auto context_ptr = MsContext::GetInstance();
  MS_EXCEPTION_IF_NULL(context_ptr);
  auto id = context_ptr->device_id();
  char real_path[PATH_MAX] = {0};
  if (nullptr == realpath(config_path_str, real_path)) {
    MS_LOG(ERROR) << "Env e2e dump path error, " << config_path_str;
    dump_enable_ = false;
    return false;
  }
  std::string dump_config_file = std::string(real_path) + "/e2e_dump_config_" + std::to_string(id) + ".json";
  std::shared_ptr<system::FileSystem> fs = system::Env::GetFileSystem();
  MS_EXCEPTION_IF_NULL(fs);
  if (!fs->FileExist(dump_config_file)) {
    MS_LOG(ERROR) << dump_config_file << " not exist.";
    dump_enable_ = false;
    return false;
  }

  return ParseDumpConfig(dump_config_file);
}

bool Dump::DumpToFile(const std::string &filename, const void *data, size_t len) {
  if (filename.empty() || data == nullptr || len == 0) {
    MS_LOG(ERROR) << "Incorrect parameter.";
    return false;
  }

  auto realpath = Common::GetRealPath(filename);
  if (!realpath.has_value()) {
    MS_LOG(ERROR) << "Get real path failed.";
    return false;
  }
  std::ofstream fd;
  fd.open(realpath.value(), std::ios::binary | std::ios::out);
  if (!fd.is_open()) {
    MS_LOG(ERROR) << "Open file " << realpath.value() << " fail.";
    return false;
  }
  (void)fd.write(reinterpret_cast<const char *>(data), SizeToLong(len));
  fd.close();
  return true;
}
}  // namespace mindspore
