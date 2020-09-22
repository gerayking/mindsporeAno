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

import numpy as np
import pytest

import mindspore.context as context
import mindspore.nn as nn
from mindspore import Tensor
from mindspore.common import dtype as mstype
from mindspore.ops import operations as P
from mindspore.ops.operations import _grad_ops as G

context.set_context(mode=context.GRAPH_MODE, device_target='CPU')

class Slice(nn.Cell):
    def __init__(self):
        super(Slice, self).__init__()
        self.slice = P.Slice()

    def construct(self, x):
        return self.slice(x, (0, 1, 0), (2, 1, 3))

@pytest.mark.level0
@pytest.mark.platform_x86_cpu
@pytest.mark.env_onecard
def test_slice():
    x = Tensor(
        np.array([[[1, -1, 1], [2, -2, 2]], [[3, -3, 3], [4, -4, 4]], [[5, -5, 5], [6, -6, 6]]]), mstype.float32)
    expect = [[[2., -2., 2.]],
              [[4., -4., 4.]]]

    slice_op = Slice()
    output = slice_op(x)
    print("output:\n", output)
    assert (output.asnumpy() == expect).all()

class Slice2(nn.Cell):
    def __init__(self):
        super(Slice2, self).__init__()
        self.slice = P.Slice()

    def construct(self, x):
        return self.slice(x, (1, 0, 0), (1, 2, 3))

@pytest.mark.level0
@pytest.mark.platform_x86_cpu
@pytest.mark.env_onecard
def test_slice2():
    x = Tensor(np.arange(3 * 2 * 3).reshape(3, 2, 3), mstype.float32)
    expect = [[[6., 7.,  8.],
               [9., 10., 11.]]]

    slice_op = Slice2()
    output = slice_op(x)
    print("output:\n", output)
    assert (output.asnumpy() == expect).all()

if __name__ == '__main__':
    test_slice()
    test_slice2()
