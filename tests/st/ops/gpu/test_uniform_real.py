# Copyright 2020 Huawei Technologies Co., Ltd
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ============================================================================
import mindspore.context as context
import mindspore.nn as nn
from mindspore import Tensor
from mindspore.ops import operations as P
from mindspore.common import dtype as mstype

context.set_context(mode=context.GRAPH_MODE, device_target="GPU")


class Net(nn.Cell):
    def __init__(self, shape, seed=0):
        super(Net, self).__init__()
        self.uniformreal = P.UniformReal(seed=seed)
        self.shape = shape

    def construct(self, a, b):
        return self.uniformreal(self.shape, a, b)


def test_net_1D():
    seed = 10
    shape = (3, 2, 4)
    a = 0.0
    b = 1.0
    net = Net(shape, seed)
    ta, tb = Tensor(a, mstype.float32), Tensor(b, mstype.float32)
    output = net(ta, tb)
    print(output.asnumpy())
    assert output.shape == (3, 2, 4)
