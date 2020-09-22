# AlexNet Example

## Description

Training AlexNet with dataset in MindSpore.

This is the simple tutorial for training AlexNet in MindSpore.

## Requirements

- Install [MindSpore](https://www.mindspore.cn/install/en).

- Download the dataset, the directory structure is as follows:

```
├─10-batches-bin
│
└─10-verify-bin
```

## Running the example

```python
# train AlexNet, hyperparameter setting in config.py
python train.py --data_path 10-batches-bin
```

You will get the loss value of each step as following:

```bash
epoch: 1 step: 1, loss is 2.2791853
...
epoch: 1 step: 1536, loss is 1.9366643
epoch: 1 step: 1537, loss is 1.6983616
epoch: 1 step: 1538, loss is 1.0221305
...
```

Then, evaluate AlexNet according to network model
```python
# evaluate AlexNet
python eval.py --data_path 10-verify-bin --ckpt_path checkpoint_alexnet-1_1562.ckpt
```

## Note
Here are some optional parameters:

```bash
--device_target {Ascend,GPU}
                     device where the code will be implemented (default: Ascend)
--data_path DATA_PATH
                     path where the dataset is saved
--dataset_sink_mode DATASET_SINK_MODE
                     dataset_sink_mode is False or True
```

You can run ```python train.py -h``` or ```python eval.py -h``` to get more information.
