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
#include "src/common/anf_importer/anf_populater/anf_tuple_getitem_populater.h"
#include <vector>
#include <memory>
#include "src/common/anf_importer/anf_populater/anf_node_populater_registry.h"
#include "ir/func_graph.h"
#include "ir/primitive.h"

namespace mindspore::lite {
int AnfTupleGetItemPopulater::Populate(const PrimitivePtr &prim, PrimitiveTValue *primitiveTValuePtr,
                                       const std::vector<AnfNodePtr> &inputs) {
  auto primitive = std::make_unique<schema::PrimitiveT>();
  auto attr = std::make_unique<schema::TupleGetItemT>();
  primitive->value.type = schema::PrimitiveType_TupleGetItem;
  primitive->value.value = attr.release();
  MS_ASSERT(primitiveTValuePtr != nullptr);
  primitiveTValuePtr->SetPrimitiveT(primitive.release());
  return 0;
}
AnfNodePopulaterRegistrar anfTupleGetItemPopulater("tuple_getitem", new AnfTupleGetItemPopulater());
}  // namespace mindspore::lite
