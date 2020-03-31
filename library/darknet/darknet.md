# [darknet](https://pjreddie.com/darknet/)

## 一.安装

### 1.下载

```
git clone https://github.com/pjreddie/darknet.git
```

### 2.编译

```
cd darknet
make -j8
```

带gpu编译，修改makefile

```
GPU=1
CUDNN=1
OPENCV=0
OPENMP=0
DEBUG=0
```

### 3.出现问题解决办法

3.1ImportError: libcudart.so.10.0: cannot open shared object file

```
sudo ldconfig /usr/local/cuda-10.0/lib64
```

3.2nvcc fatal : Path to libdevice library not specified

```
修改makefile
NVCC=/usr/local/cuda-10.1/bin/nvcc
```

3.3清除make

```
make clean
```

## 二.使用

### 1 ./darknet参数

-i 0

```
./darknet -i 0 指定GPU
```

-nogpu

```
./darknet -nogpu 不使用gpu
```

-gpus:多gpu

```
./darknet detector train .data .cfg .weights -gpus 0，1，2，3
```

detect:检测一张图片

```
./darknet detect .cfg .weights imgname 单张预测	
./darknet detect .cfg .weights 多张预测（每次要求输入图片路径，ctrl+c停止）
```

detector:(test train demo)目标检测

```
./darknet detector train .data .cfg .weights	//data训练数据和测试数据的位置类别名字
从头训练：train的weights是指特征提取网络的权重 一般是imagenet训练的卷积层
finetune：train的weights是目标检测网络权重可以是backup/.backup
./darknet detector test .data .cfg .weights
test的weights是指训练好的目标检测网络权重
```

-thresh:设置置信度阈值默认0.25

```
./darknet detect .cfg .weights imgname -thresh 0	显示所有
```

classify:分类

```
./darknet classify .cfg .weights imgname
```

classifier：(train valid predict)分类

```
./darknet classifier predict .data .cfg .weights imgname 对图片预测
同样可以不指定图片，预测多张图片
./darknet classifier train .data .cfg .backup //finetune，不指定backup就是从头训练
```

### 2.文件类型

1.data ：定义数据源，类别数目，类别名，模型存储路径

```
voc.data

classes= 20
train  = /home/pjreddie/data/voc/train.txt
valid  = /home/pjreddie/data/voc/2007_test.txt
names = data/voc.names
backup = backup
```

2.cfg：网络结构和超参数

```
[net]	# [xxx]开始的行表示网络的一层，其后的内容为该层的参数配置，[net]为特殊的层，配置整个网
# Testing
 batch=1 # batch与机器学习中的batch有少许差别，仅表示网络积累多少个样本后进行一次BP
 subdivisions=1	# 这个参数表示将一个batch的图片分sub次完成网络的前向传播batch=64，sub=16表示训练的过程中将一次性加载64张图片进内存，然后分16次完成前向传播，意思是每次4张，前向传播的循环过程中累加loss求平均，待64张图片都完成前向传播后，再一次性后传更新参数

# Training
# batch=64
# subdivisions=16
width=416  # 网络输入的长宽通道width和height的值越大，对于小目标的识别效果越好
height=416
channels=3
momentum=0.9 # 动量衰减参数
decay=0.0005 # 权重衰减正则项参数

# 数据增强参数
angle=0 #转角生成
saturation = 1.5 # 调整饱和度
exposure = 1.5 # 调整暴光
hue=.1 # 调整色调

learning_rate=0.001 # 学习率 如果loss波动太大，说明学习率过大，适当减小，变为1/5，1/10均可，如果loss几乎不变，可能网络已经收敛或者陷入了局部极小，此时可以适当增大学习率
burn_in=1000 # 在迭代次数小于burn_in时，其学习率的更新有一种方式，大于burn_in时，才采用policy的更新方式
max_batches = 50200 # 训练次数达到max_batches后停止学习，一次为跑完一个batch
policy=steps # 学习率调整的策略：constant, steps, exp, poly, step, sig, RANDOM等方式
steps=40000,45000
scales=.1,.1 # steps和scale是设置学习率的变化，比如迭代到400000次时，学习率衰减十倍，45000次迭代时，学习率又会在前一个学习率的基础上衰减十倍

[convolutional] # 卷积层，不解释
batch_normalize=1
filters=32 # yolo层前面的卷积层配置filter=（预测框个数）*（classes+5）
size=3
stride=1
pad=1
activation=leaky

[shortcut] 
from=-3	# 与前面第三层进行融合contacate
activation=linear

[yolo]
mask = 6,7,8 # 使用anchor的索引，0，1，2表示使用下面定义的anchors中的前三个anchor
anchors = 10,13,  16,30,  33,23,  30,61,  62,45,  59,119,  116,90,  156,198,  373,326
classes=20 #类别数目
num=9	# 每个grid cell总共预测几个box,和anchors的数量一致
jitter=.3 # 数据增强手段，此处jitter为随机调整宽高比的范围
ignore_thresh = .5 # 
truth_thresh = 1 #参与计算的IOU阈值大小.当预测的检测框与ground true的IOU大于ignore_thresh的时候，参与loss的计算，否则ignore_thresh过于大，接近于1的时候，那么参与检测框回归loss的个数就会比较少，同时也容易造成过拟合；而如果ignore_thresh设置的过于小，那么参与计算的会数量规模就会很大

random=1 # 为1打开随机多尺度训练，为0则关闭当打开随机多尺度训练时，前面设置的网络输入尺寸width和height其实就不起作用了

[upsample] 
stride=2

[route] # router合并前面若干层的输出
layers = -4
```

3.weights：模型权重

### 3.模型下载

```
wget https://pjreddie.com/media/files/modelname.weights

modelname.weights可以是如下：
yolov3	
yolov3-tiny 
darknet19
darknet53.conv.74
```

## 三.Demo

### 1.目标检测

#### 1.1目标

实现检测目标浣熊（raccoon）

#### 1.2数据准备

1.2.1浣熊数据集

```
git clone git@github.com:datitran/raccoon_dataset.git
```

也可以自己使用LabelImg打标签

```
annotation	标签数据（.xml）
images	图像文件（.jpg）
```

1.2.2xml标签转换为txt格式

创建4个文件夹：trainImage，validateImage,trainImageXML,validateImageXML分别放入对应文件

借助**createID.py**生成训练集和验证集的图片名称列表trainImageId.txt和validateImageId.txt

借助**trans.py**生成训练集和验证集的完整路径列表并完成标签xml文件到txt文件的转换

1.2.3 下载预训练权重文件

```
wget https://pjreddie.com/media/files/darknet53.conv.74
```

#### 1.3生成配置文件

1.3.1names

添加文件data/raccoon.names,写入自己定义的类别

```
raccoon
```

1.3.2data

添加文件cfg/raccoon.data

```
classes= 1
train  = /home/560204/SD/sd1/darknet/dataset/raccoon/trainImagePath.txt
valid  = /home/560204/SD/sd1/darknet/dataset/raccoon/validateImagePath.txt
names = data/raccoon.names
backup = /home/560204/SD/sd1/darknet/backup
```

1.3.3cfg

添加cfg文件，这里使用yolov3的网络结构，复制一份重命名为raccoon.cfg

```
1. classes = N （N为自己的分类数）
2. 修改每一个[yolo]层（一共有3处）之前的filters为 3*(classes+1+4)，如有3个分类，则修改 filters=24
3. (可选) 修改训练的最大迭代次数， max_batches = N
```

#### 1.4训练

```
./darknet detector train cfg/raccoon.data cfg/raccoon.cfg weights/darknet19.weights 
```

#### 1.5预测

```
./darknet detector test cfg/raccoon.data cfg/raccoon.cfg backup/raccoon_final.weights imgname
```

