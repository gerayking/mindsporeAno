# DeeplabV3 Example

## Description
This is an example of training DeepLabV3 with PASCAL VOC 2012 dataset in MindSpore. 

## Requirements
- Install [MindSpore](https://www.mindspore.cn/install/en).
- Download the VOC 2012 dataset for training. 
  ``` bash
  python remove_gt_colormap.py --original_gt_folder GT_FOLDER --output_dir OUTPUT_DIR

  ```

> Notes: 
  If you are running a fine-tuning or evaluation task, prepare the corresponding checkpoint file.


## Running the Example
### Training
- Set options in config.py.
- Run `run_standalone_train.sh` for non-distributed training.
	``` bash 
	sh scripts/run_standalone_train.sh DEVICE_ID DATA_PATH
	```
- Run `run_distribute_train.sh` for distributed training.
	``` bash
	sh scripts/run_distribute_train.sh RANK_TABLE_FILE DATA_PATH
	```
### Evaluation
Set options in evaluation_config.py. Make sure the 'data_file' and 'finetune_ckpt' are set to your own path.
- Run run_eval.sh for evaluation.
	``` bash
	sh scripts/run_eval.sh DEVICE_ID DATA_PATH PRETRAINED_CKPT_PATH
	```

## Options and Parameters
It contains of parameters of DeeplabV3 model and options for training, which is set in file config.py.

### Options:
```
config.py:
    learning_rate                   Learning rate, default is 0.0014.
    weight_decay                	Weight decay, default is 5e-5.
    momentum                    	Momentum, default is 0.97.
    crop_size                       Image crop size [height, width] during training, default is 513.
    eval_scales                     The scales to resize images for evaluation, default is [0.5, 0.75, 1.0, 1.25, 1.5, 1.75].
	output_stride					The ratio of input to output spatial resolution, default is 16.
	ignore_label					Ignore label value,	default is 255.
	seg_num_classes					Number of semantic classes, including the background class (if exists). 
									foreground classes + 1 background class in the PASCAL VOC 2012 dataset, default is 21.
	fine_tune_batch_norm			Fine tune the batch norm parameters or not, default is False.
	atrous_rates					Atrous rates for atrous spatial pyramid pooling, default is None.
	decoder_output_stride			The ratio of input to output spatial resolution when employing decoder
									to refine segmentation results, default is None.
	image_pyramid					Input scales for multi-scale feature extraction, default is None.
	epoch_size						Epoch size, default is 6.
    batch_size                      batch size of input dataset: N, default is 2.
	enable_save_ckpt				Enable save checkpoint, default is true.
	save_checkpoint_steps			Save checkpoint steps, default is 1000.
	save_checkpoint_num				Save checkpoint numbers, default is 1.
```	


### Parameters:
```
Parameters for dataset and network:
    distribute						Run distribute, default is false.
	data_url						Train/Evaluation data url, required.
	checkpoint_url					Checkpoint path, default is None.
```