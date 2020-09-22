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

"""
Primitive operator classes.

A collection of operators to build nerual networks or computing functions.
"""

from .image_ops import (CropAndResize)
from .array_ops import (Argmax, Argmin, Cast, Concat, Pack, Unpack,
                        Diag, DiagPart, DType, ExpandDims, Eye,
                        Fill, GatherNd, GatherV2, SparseGatherV2, InvertPermutation,
                        IsInstance, IsSubClass, ArgMaxWithValue, OnesLike, ZerosLike,
                        Rank, Reshape, ResizeNearestNeighbor, ArgMinWithValue,
                        SameTypeShape, ScatterAdd, ScatterSub, ScatterMul, ScatterDiv, ScatterMax, ScatterMin,
                        ScatterUpdate, ScalarToArray, ScalarToTensor, ScatterNd, ScatterNdUpdate, Select,
                        Shape, Size, Slice, Split, TransShape, ParallelConcat, Padding,
                        ScatterNdAdd, ScatterNdSub, ScatterNonAliasingAdd, ReverseV2, Rint,
                        Squeeze, StridedSlice, Tile, TensorScatterUpdate,
                        Transpose, TruncatedNormal, TupleToArray, UnsortedSegmentMin, UnsortedSegmentProd,
                        UnsortedSegmentSum, SpaceToDepth, DepthToSpace, SpaceToBatch, BatchToSpace,
                        SpaceToBatchND, BatchToSpaceND, BroadcastTo, InplaceUpdate, ReverseSequence, EmbeddingLookup,
                        Unique)
from .comm_ops import (AllGather, AllReduce, _AlltoAll, ReduceScatter, Broadcast,
                       _MirrorOperator, ReduceOp, _VirtualDataset,
                       _VirtualDiv, _GetTensorSlice,
                       _HostAllGather, _HostReduceScatter)
from .debug_ops import (ImageSummary, InsertGradientOf, HookBackward, ScalarSummary,
                        TensorSummary, HistogramSummary, Debug, Print)
from .control_ops import ControlDepend, GeSwitch, Merge
from .inner_ops import ScalarCast

from .math_ops import (Abs, ACos, Asin, Asinh, AddN, AccumulateNV2, AssignAdd, AssignSub, Atan2, BatchMatMul, BitwiseAnd, BitwiseOr,
                       BitwiseXor, Inv, Invert, ApproximateEqual, InplaceAdd, InplaceSub,
                       ReduceMax, ReduceMin, ReduceMean, ReduceSum, ReduceAll, ReduceProd, CumProd, ReduceAny,
                       Cos, Div, DivNoNan, Equal, EqualCount, Exp, Expm1, Erf, Erfc, Floor, FloorDiv, FloorMod, Ceil,
                       Acosh, Greater, GreaterEqual, Less, LessEqual, Log, Log1p, LogicalAnd, Mod,
                       LogicalNot, LogicalOr, MatMul, Maximum,
                       Minimum, Mul, Neg, NMSWithMask, NotEqual,
                       NPUAllocFloatStatus, NPUClearFloatStatus,
                       NPUGetFloatStatus, Pow, RealDiv, IsNan, IsInf, IsFinite, FloatStatus,
                       Reciprocal, CumSum, HistogramFixedWidth, SquaredDifference, Xdivy, Xlogy,
                       Sin, Sqrt, Rsqrt, BesselI0e, BesselI1e, TruncateDiv, TruncateMod,
                       Square, Sub, TensorAdd, Sign, Round, SquareSumAll, Atan, Atanh, Cosh, Sinh, Eps, Tan)

from .random_ops import (RandomChoiceWithMask, StandardNormal, Gamma, Poisson, UniformInt, UniformReal,
                         RandomCategorical, Laplace, Multinomial)
from .nn_ops import (LSTM, SGD, Adam, FusedSparseAdam, FusedSparseLazyAdam, ApplyMomentum, BatchNorm,
                     BiasAdd, Conv2D,
                     DepthwiseConv2dNative,
                     DropoutDoMask, DropoutGrad, Dropout,
                     DropoutGenMask, Flatten, FusedBatchNorm, BNTrainingReduce, BNTrainingUpdate,
                     Gelu, Elu,
                     GetNext, L2Normalize, LayerNorm, L2Loss, CTCLoss, CTCLossV2,
                     LogSoftmax,
                     MaxPool, DataFormatDimMap,
                     AvgPool, Conv2DBackpropInput, ConfusionMulGrad,
                     MaxPoolWithArgmax, OneHot, Pad, MirrorPad, PReLU, ReLU, ReLU6, ReLUV2, HSwish, HSigmoid,
                     ResizeBilinear, Sigmoid,
                     SigmoidCrossEntropyWithLogits,
                     SmoothL1Loss, Softmax, Softsign, Softplus, LRN, RNNTLoss,
                     SoftmaxCrossEntropyWithLogits, ROIAlign,
                     SparseSoftmaxCrossEntropyWithLogits, Tanh,
                     TopK, BinaryCrossEntropy, KLDivLoss, SparseApplyAdagrad, LARSUpdate, ApplyFtrl, SparseApplyFtrl,
                     ApplyProximalAdagrad, SparseApplyProximalAdagrad, SparseApplyAdagradV2, SparseApplyFtrlV2,
                     FusedSparseFtrl, FusedSparseProximalAdagrad,
                     ApplyAdaMax, ApplyAdadelta, ApplyAdagrad, ApplyAdagradV2,
                     ApplyAddSign, ApplyPowerSign, ApplyGradientDescent, ApplyProximalGradientDescent,
                     ApplyRMSProp, ApplyCenteredRMSProp, BasicLSTMCell, InTopK)
from . import _quant_ops
from ._quant_ops import *
from .other_ops import (Assign, IOU, BoundingBoxDecode, BoundingBoxEncode, PopulationCount,
                        CheckValid, MakeRefKey, Partial, Depend, CheckBprop, Push, Pull)
from ._thor_ops import (CusBatchMatMul, CusCholeskyTrsm, CusFusedAbsMax1, CusImg2Col, CusMatMulCubeDenseLeft,
                        CusMatMulCubeFraczRightMul, CusMatMulCube, CusMatrixCombine, CusTranspose02314,
                        CusMatMulCubeDenseRight,
                        CusMatMulCubeFraczLeftCast, Im2Col, UpdateThorGradient, Cholesky)
from .sparse_ops import SparseToDense

__all__ = [
    'ReverseSequence',
    'CropAndResize',
    'TensorAdd',
    'Argmax',
    'Argmin',
    'ArgMaxWithValue',
    'ArgMinWithValue',
    'AddN',
    'AccumulateNV2',
    'Sub',
    'CumSum',
    'MatMul',
    'BatchMatMul',
    'Mul',
    'Pow',
    'Exp',
    'Expm1',
    'Rsqrt',
    'Sqrt',
    'Square',
    'SquaredDifference',
    'Xdivy',
    'Xlogy',
    'Conv2D',
    'Flatten',
    'MaxPoolWithArgmax',
    'FusedBatchNorm',
    'BNTrainingReduce',
    'BNTrainingUpdate',
    'BatchNorm',
    'MaxPool',
    'TopK',
    'Adam',
    'FusedSparseAdam',
    'FusedSparseLazyAdam',
    'Softplus',
    'Softmax',
    'Softsign',
    'LogSoftmax',
    'SoftmaxCrossEntropyWithLogits',
    'ROIAlign',
    'ConfusionMulGrad',
    'SparseSoftmaxCrossEntropyWithLogits',
    'SGD',
    'ApplyMomentum',
    'ExpandDims',
    'Cast',
    'IsSubClass',
    'IsInstance',
    'Reshape',
    'Squeeze',
    'Transpose',
    'OneHot',
    'GatherV2',
    'SparseGatherV2',
    'EmbeddingLookup',
    'Padding',
    'Concat',
    'Pack',
    'Unpack',
    'Tile',
    'BiasAdd',
    'Gelu',
    'Minimum',
    'Maximum',
    'StridedSlice',
    'ReduceSum',
    'ReduceMean',
    'LayerNorm',
    'Rank',
    'Less',
    'LessEqual',
    'RealDiv',
    'Div',
    'DivNoNan',
    'Inv',
    'Invert',
    'TruncatedNormal',
    'Fill',
    'OnesLike',
    'ZerosLike',
    'Select',
    'Split',
    'ReLU',
    'ReLU6',
    'Elu',
    'Erf',
    'Erfc',
    'Sigmoid',
    'HSwish',
    'HSigmoid',
    'Tanh',
    'RandomChoiceWithMask',
    'StandardNormal',
    'Multinomial',
    'Gamma',
    'Poisson',
    'UniformInt',
    'UniformReal',
    'Laplace',
    'RandomCategorical',
    'ResizeBilinear',
    'ScalarSummary',
    'ImageSummary',
    'TensorSummary',
    'HistogramSummary',
    "Debug",
    "Print",
    'InsertGradientOf',
    'HookBackward',
    'InvertPermutation',
    'Shape',
    'DropoutDoMask',
    'DropoutGenMask',
    'DropoutGrad',
    'Dropout',
    'Neg',
    'InplaceAdd',
    'InplaceSub',
    'Slice',
    'DType',
    'NPUAllocFloatStatus',
    'NPUGetFloatStatus',
    'NPUClearFloatStatus',
    'IsNan',
    'IsFinite',
    'IsInf',
    'FloatStatus',
    'Reciprocal',
    'SmoothL1Loss',
    'L2Loss',
    'CTCLoss',
    'RNNTLoss',
    'ReduceAll',
    'ReduceAny',
    'ScalarToArray',
    'ScalarToTensor',
    'TupleToArray',
    'ControlDepend',
    'GeSwitch',
    'Merge',
    'SameTypeShape',
    'CheckBprop',
    'CheckValid',
    'BoundingBoxEncode',
    'BoundingBoxDecode',
    'L2Normalize',
    'ScatterAdd',
    'ScatterSub',
    'ScatterMul',
    'ScatterDiv',
    'ScatterNd',
    'ScatterMax',
    'ScatterMin',
    'ScatterNdAdd',
    'ScatterNdSub',
    'ScatterNonAliasingAdd',
    'ReverseV2',
    'Rint',
    'ResizeNearestNeighbor',
    'HistogramFixedWidth',
    'Pad',
    'MirrorPad',
    'GatherNd',
    'TensorScatterUpdate',
    'ScatterUpdate',
    'ScatterNdUpdate',
    'Floor',
    'NMSWithMask',
    'IOU',
    'MakeRefKey',
    'Partial',
    'Depend',
    'AvgPool',
    # Back Primitive
    'Equal',
    'EqualCount',
    'NotEqual',
    'Greater',
    'GreaterEqual',
    'LogicalNot',
    'LogicalAnd',
    'LogicalOr',
    'Size',
    'DepthwiseConv2dNative',
    'UnsortedSegmentSum',
    'UnsortedSegmentMin',
    'UnsortedSegmentProd',
    "AllGather",
    "AllReduce",
    "ReduceScatter",
    "Broadcast",
    "ReduceOp",
    'ScalarCast',
    'GetNext',
    'ReduceMax',
    'ReduceMin',
    'ReduceProd',
    'CumProd',
    'Log',
    'Log1p',
    'SigmoidCrossEntropyWithLogits',
    'FloorDiv',
    'FloorMod',
    'TruncateDiv',
    'TruncateMod',
    'Ceil',
    'Acosh',
    'Asinh',
    "PReLU",
    "Cos",
    "Cosh",
    "ACos",
    "Diag",
    "DiagPart",
    'Eye',
    'Assign',
    'AssignAdd',
    'AssignSub',
    "Sin",
    "Sinh",
    "Asin",
    "LSTM",
    "Abs",
    "BinaryCrossEntropy",
    "KLDivLoss",
    "SparseApplyAdagrad",
    "SparseApplyAdagradV2",
    "SpaceToDepth",
    "DepthToSpace",
    "Conv2DBackpropInput",
    "Sign",
    "LARSUpdate",
    "Round",
    "Eps",
    "ApplyFtrl",
    "SpaceToBatch",
    "SparseApplyFtrl",
    "SparseApplyFtrlV2",
    "FusedSparseFtrl",
    "ApplyProximalAdagrad",
    "SparseApplyProximalAdagrad",
    "FusedSparseProximalAdagrad",
    "ApplyAdaMax",
    "ApplyAdadelta",
    "ApplyAdagrad",
    "ApplyAdagradV2",
    "ApplyAddSign",
    "ApplyPowerSign",
    "ApplyGradientDescent",
    "ApplyProximalGradientDescent",
    "BatchToSpace",
    "Atan2",
    "ApplyRMSProp",
    "ApplyCenteredRMSProp",
    "SpaceToBatchND",
    "BatchToSpaceND",
    "SquareSumAll",
    "BitwiseAnd",
    "BitwiseOr",
    "BitwiseXor",
    "BesselI0e",
    "BesselI1e",
    "Atan",
    "Atanh",
    "Tan",
    "BasicLSTMCell",
    "BroadcastTo",
    "DataFormatDimMap",
    "ApproximateEqual",
    "InplaceUpdate",
    "InTopK",
    "LRN",
    "Mod",
    "PopulationCount",
    "ParallelConcat",
    "Push",
    "Pull",
    'SparseToDense',
]

__all__.sort()