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
"""Convolutional variational layers."""
from mindspore.ops import operations as P
from mindspore._checkparam import twice
from ...layer.conv import _Conv
from ...cell import Cell
from .layer_distribution import NormalPrior, NormalPosterior

__all__ = ['ConvReparam']


class _ConvVariational(_Conv):
    """
    Base class for all convolutional variational layers.
    """

    def __init__(self,
                 in_channels,
                 out_channels,
                 kernel_size,
                 stride=1,
                 pad_mode='same',
                 padding=0,
                 dilation=1,
                 group=1,
                 has_bias=False,
                 weight_prior_fn=NormalPrior,
                 weight_posterior_fn=lambda name, shape: NormalPosterior(name=name, shape=shape),
                 bias_prior_fn=NormalPrior,
                 bias_posterior_fn=lambda name, shape: NormalPosterior(name=name, shape=shape)):
        kernel_size = twice(kernel_size)
        stride = twice(stride)
        dilation = twice(dilation)
        super(_ConvVariational, self).__init__(
            in_channels,
            out_channels,
            kernel_size,
            stride,
            pad_mode,
            padding,
            dilation,
            group,
            has_bias,
            weight_init='normal',
            bias_init='zeros'
        )
        if pad_mode not in ('valid', 'same', 'pad'):
            raise ValueError('Attr \'pad_mode\' of \'Conv2d\' Op passed '
                             + str(pad_mode) + ', should be one of values in \'valid\', \'same\', \'pad\'.')

        # convolution args
        self.in_channels = in_channels
        self.out_channels = out_channels
        self.kernel_size = kernel_size
        self.stride = stride
        self.pad_mode = pad_mode
        self.padding = padding
        self.dilation = dilation
        self.group = group
        self.has_bias = has_bias

        # distribution trainable parameters
        self.shape = [self.out_channels,
                      self.in_channels // self.group, *self.kernel_size]

        self.weight.requires_grad = False

        if isinstance(weight_prior_fn, Cell):
            self.weight_prior = weight_prior_fn
        else:
            self.weight_prior = weight_prior_fn()

        self.weight_posterior = weight_posterior_fn(shape=self.shape, name='bnn_weight')

        if self.has_bias:
            self.bias.requires_grad = False

            if isinstance(bias_prior_fn, Cell):
                self.bias_prior = bias_prior_fn
            else:
                self.bias_prior = bias_prior_fn()

            self.bias_posterior = bias_posterior_fn(shape=[self.out_channels], name='bnn_bias')

        # mindspore operations
        self.bias_add = P.BiasAdd()
        self.conv2d = P.Conv2D(out_channel=self.out_channels,
                               kernel_size=self.kernel_size,
                               mode=1,
                               pad_mode=self.pad_mode,
                               pad=self.padding,
                               stride=self.stride,
                               dilation=self.dilation,
                               group=self.group)

        self.log = P.Log()
        self.sum = P.ReduceSum()

    def construct(self, inputs):
        outputs = self._apply_variational_weight(inputs)
        if self.has_bias:
            outputs = self._apply_variational_bias(outputs)
        return outputs

    def extend_repr(self):
        str_info = 'in_channels={}, out_channels={}, kernel_size={}, weight_mean={}, stride={},  pad_mode={}, ' \
                    'padding={}, dilation={}, group={}, weight_std={}, has_bias={}'\
            .format(self.in_channels, self.out_channels, self.kernel_size, self.stride, self.pad_mode, self.padding,
                    self.dilation, self.group, self.weight_posterior.mean, self.weight_posterior.untransformed_std,
                    self.has_bias)
        if self.has_bias:
            str_info = str_info + ', bias_mean={}, bias_std={}'\
                .format(self.bias_posterior.mean, self.bias_posterior.untransformed_std)
        return str_info

    def _apply_variational_bias(self, inputs):
        bias_posterior_tensor = self.bias_posterior("sample")
        return self.bias_add(inputs, bias_posterior_tensor)

    def compute_kl_loss(self):
        """Compute kl loss"""
        weight_post_mean = self.weight_posterior("mean")
        weight_post_sd = self.weight_posterior("sd")

        kl = self.weight_prior("kl_loss", "Normal",
                               weight_post_mean, weight_post_sd)
        kl_loss = self.sum(kl)
        if self.has_bias:
            bias_post_mean = self.bias_posterior("mean")
            bias_post_sd = self.bias_posterior("sd")

            kl = self.bias_prior("kl_loss", "Normal",
                                 bias_post_mean, bias_post_sd)
            kl = self.sum(kl)
            kl_loss += kl
        return kl_loss


class ConvReparam(_ConvVariational):
    r"""
    Convolutional variational layers with Reparameterization.

    See more details in paper `Auto-Encoding Variational Bayes
    <https://arxiv.org/abs/1312.6114>`

    Args:
        in_channels (int): The number of input channel :math:`C_{in}`.
        out_channels (int): The number of output channel :math:`C_{out}`.
            kernel_size (Union[int, tuple[int]]): The data type is int or
            tuple with 2 integers. Specifies the height and width of the 2D
            convolution window. Single int means the value if for both
            height and width of the kernel. A tuple of 2 ints means the
            first value is for the height and the other is for the width of
            the kernel.
        stride(Union[int, tuple[int]]): The distance of kernel moving,
            an int number that represents the height and width of movement
            are both strides, or a tuple of two int numbers that represent
            height and width of movement respectively. Default: 1.
        pad_mode (str): Specifies padding mode. The optional values are
            "same", "valid", "pad". Default: "same".

            - same: Adopts the way of completion. Output height and width
              will be the same as the input.
              Total number of padding will be calculated for horizontal and
              vertical direction and evenly distributed to top and bottom,
              left and right if possible. Otherwise, the last extra padding
              will be done from the bottom and the right side. If this mode
              is set, `padding` must be 0.

            - valid: Adopts the way of discarding. The possibly largest
              height and width of output will be return without padding.
              Extra pixels will be discarded. If this mode is set, `padding`
              must be 0.

            - pad: Implicit paddings on both sides of the input. The number
              of `padding` will be padded to the input Tensor borders.
              `padding` should be greater than or equal to 0.

        padding (Union[int, tuple[int]]): Implicit paddings on both sides of
            the input. Default: 0.
        dilation (Union[int, tuple[int]]): The data type is int or tuple
            with 2 integers. Specifies the dilation rate to use for dilated
            convolution. If set to be :math:`k > 1`,
            there will be :math:`k - 1` pixels skipped for each sampling
            location. Its value should be greater or equal to 1 and bounded
            by the height and width of the input. Default: 1.
        group (int): Split filter into groups, `in_ channels` and
            `out_channels` should be divisible by the number of groups.
            Default: 1.
        has_bias (bool): Specifies whether the layer uses a bias vector.
            Default: False.
        weight_prior_fn: prior distribution for convolution kernel.
            It should return a mindspore distribution instance.
            Default: NormalPrior. (which creates an instance of standard
            normal distribution).
        weight_posterior_fn: posterior distribution for sampling convolution
            kernel. It should be a function handle which returns a mindspore
            distribution instance.
            Default: NormalPosterior.
        bias_prior_fn: prior distribution for bias vector. It should return
            a mindspore distribution.
            Default: NormalPrior(which creates an instance of standard
            normal distribution).
        bias_posterior_fn: posterior distribution for sampling bias vector.
            It should be a function handle which returns a mindspore
            distribution instance.
            Default: NormalPosterior.

    Inputs:
        - **input** (Tensor) - Tensor of shape :math:`(N, C_{in}, H_{in}, W_{in})`.

    Outputs:
        Tensor of shape :math:`(N, C_{out}, H_{out}, W_{out})`.

    Examples:
        Examples:
    >>> net = ConvReparam(120, 240, 4, has_bias=False)
    >>> input = Tensor(np.ones([1, 120, 1024, 640]), mindspore.float32)
    >>> net(input).shape
    (1, 240, 1024, 640)
    """

    def __init__(
            self,
            in_channels,
            out_channels,
            kernel_size,
            stride=1,
            pad_mode='same',
            padding=0,
            dilation=1,
            group=1,
            has_bias=False,
            weight_prior_fn=NormalPrior,
            weight_posterior_fn=lambda name, shape: NormalPosterior(name=name, shape=shape),
            bias_prior_fn=NormalPrior,
            bias_posterior_fn=lambda name, shape: NormalPosterior(name=name, shape=shape)):
        super(ConvReparam, self).__init__(
            in_channels,
            out_channels,
            kernel_size,
            stride=stride,
            pad_mode=pad_mode,
            padding=padding,
            dilation=dilation,
            group=group,
            has_bias=has_bias,
            weight_prior_fn=weight_prior_fn,
            weight_posterior_fn=weight_posterior_fn,
            bias_prior_fn=bias_prior_fn,
            bias_posterior_fn=bias_posterior_fn
        )

    def _apply_variational_weight(self, inputs):
        weight_posterior_tensor = self.weight_posterior("sample")
        outputs = self.conv2d(inputs, weight_posterior_tensor)
        return outputs
