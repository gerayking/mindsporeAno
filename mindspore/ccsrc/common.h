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

#ifndef MINDSPORE_CCSRC_COMMON_H_
#define MINDSPORE_CCSRC_COMMON_H_

#include <unordered_map>
#include <string>

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include "abstract/dshape.h"
#include "abstract/abstract_value.h"
#include "abstract/abstract_function.h"
#include "pipeline/jit/parse/python_adapter.h"
#include "pipeline/jit/parse/parse.h"
#include "pipeline/jit/parse/parse_base.h"
#include "pipeline/jit/parse/resolve.h"

namespace py = pybind11;
#endif  // MINDSPORE_CCSRC_COMMON_H_
