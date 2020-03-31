# 机器学习

## 1.数学基础

### 1.1微积分

导数是个标量

梯度是个矢量

### 1.2线性代数

#### 特征距离

欧式距离

曼哈顿距离

汉明距离

### 1.3概率论

### 1.4凸优化

## 2.术语

权重（weight）

偏差（bias）

模型（model）

样本（sample）

标签（label）

训练集（training  set）

特征（feature）

损失函数（loss function）

解析解（analytical solution）

数值解（numerical solution）

样本批次大小（batch size）

学习率（learning rate）

超参数（hyper parameter）

激活函数（activation function）

训练误差（training error）

泛化误差（generalization error）

模型选择（model selection）

验证集（validation dataset）

K交叉验证（k-fold cross-validation）

我们把原始训练数据集分割成K个不重合的⼦数据集，然后我们做K次模型训练和验证。每⼀次，我们使⽤⼀个⼦数据集验证模型，并使⽤其他K - 1个⼦数据集来训练模型。

过拟合（over fitting）

模型的训练误差远小于它在测试数据集上的误差

解决方法：增大训练数据，正则化，dropout（根本原理还是使得某个权重不要过大，减少对某个权重的依赖）

欠拟合（under fitting）

模型⽆法得到较低的训练误差，我们将这⼀现象称作⽋拟合

局部最小（local minimum）

全局最小（global minimum）

鞍点（saddle point）

目标检测（object detection）

边界框（bounding box）

锚框（anchor box）

交并⽐（Intersection over Union，IoU）

⾮极⼤值抑制（non-maximum suppression，NMS）

## 3.损失函数（loss function）

可以从广义上将损失函数分为两大类回归损失和分类损失

### 3.1回归损失

均方误差/平方损失/L2损失（mean square error）
$$
MSE=\frac{\sum_{i=1}^{n}(y_i-\bar{y_i})^2}{n}
$$
平均绝对误差/L1损失（mean absolute error）
$$
MAE=\frac{\sum_{i=1}^{n}\left\|(y_i-\bar{y_i})\right\|}{n}
$$
平均偏差误差（mean bias error）
$$
MBE=\frac{\sum_{i=n}^{n}(y_i-\bar{y_i})}{n}
$$

### 3.2分类损失

交叉熵损失（cross entropy Loss）
$$
CEL=-（y_ilog(\bar{y_i})+(1-y_i)log(1-\bar{y_i})）
$$


## 4.优化器（optimizer ）

### 4.1 SGD（stochastic gradient descent）随机梯度

随机均匀采样一个样本计算梯度替代所有样本的平均梯度

### 4.2 mini-batch SGD（mini-batch gradient descent）小批量随机梯度

随机采样多个样本组成小批量来计算梯度。当批量为1时，退化为SGD，批量为样本数量时，为梯度下降法

### 4.3 momentum 动量法

通过速度v，来积累了之间梯度指数级衰减的平均，并且继续延该方向移动

### 4.4 AdaGrad

梯度下降算法、随机梯度下降算法（SGD）、小批量梯度下降算法（mini-batch SGD）、动量法（momentum）、Nesterov动量法有一个共同的特点是：对于每一个参数都用相同的学习率进行更新。AdaGrad算法就是将每一个参数的每一次迭代的梯度取平方累加后在开方，用全局学习率除以这个数，作为学习率的动态更新。一般来说AdaGrad算法一开始是激励收敛，到了后面就慢慢变成惩罚收敛，速度越来越慢。按元素运算使得⽬标函数⾃变量中每个元素都分别拥有⾃⼰的学习率。

### 4.5 RMSProp(root mean squared)

不同于AdaGrad算法⾥状态变量st是截⾄时间步t所有小批量随机梯度按元素平⽅和，RMSProp算法将这些梯度按元素平⽅做指数加权移动平均。

### 4.6 AdaDelta

AdaDelta算法跟RMSProp算法的不同之处在于使⽤
$$
\sqrt{\Delta x_{t-1}}
$$
来代超参数η

### 4.7 Adam

Adam算法是RMSProp算法与动量法的结合,Adam算法在RMSProp算法的基础上对小批量随机梯度也做了指数加权移动平均。

## 5.计算

### 5.1 命令式（imperative）和符号式（symblic）编程

命令式编程更⽅便，平时的编程方式都是命令式的。当我们在Python⾥使⽤命令式编程时，⼤部分代码编写起来都很直观。同时，命令式编程更容易调试。这是因为我们可以很⽅便地获取并打印所有的中间变量值，或者使⽤Python的调试⼯具。

符号式编程，并不会直接计算中间值，而是先构建计算图，再统一计算。

### 5.2 异步计算

异步计算指，前端线程⽆须等待当前指令从后端线程返回结果就继续执⾏后⾯的指令。

### 5.3 多GPU计算

数据并⾏⽬前是深度学习⾥使⽤最⼴泛的将模型训练任务划分到多块GPU的⽅法。在模型训练的任意⼀次迭代中，给定⼀个随机小批量，我们将该批量中的样本划分成k份并分给每块显卡的显存⼀份。然后，每块GPU将根据相应显存所分到的小批量⼦集和所维护的模型参数分别计算模型参数的本地梯度。接下来，我们把k块显卡的显存上的本地梯度相加，便得到当前的小批量随机梯度。之后，每块GPU都使⽤这个小批量随机梯度分别更新相应显存所维护的那⼀份完整的模型参数。

## 6.Machine Learning 机器学习

### 6.1基础知识

#### 6.1.1模型评价指标

1) True positives(TP):  被正确地划分为正例的个数，即实际为正例且被分类器划分为正例的实例数；
 2) False positives(FP): 被错误地划分为正例的个数，即实际为负例但被分类器划分为正例的实例数；
 3) False negatives(FN):被错误地划分为负例的个数，即实际为正例但被分类器划分为负例的实例数；
 4) True negatives(TN): 被正确地划分为负例的个数，即实际为负例且被分类器划分为负例的实例数。

positive=1、negative=-1。用1表示True，-1表示False，那么实际的类标=TF\*PN，TF为true或false，PN为positive或negative。

1) 正确率（accuracy）
	正确率是我们最常见的评价指标，accuracy = (TP+TN)/(P+N)，正确率是被分对的样本数在所有样本数中的占比，通常来说，正确率越高，分类器越好。

2) 错误率（error rate)
	错误率则与正确率相反，描述被分类器错分的比例，error rate = (FP+FN)/(P+N)，对某一个实例来说，分对与分错是互斥事件，所以accuracy =1 -  error rate。

3) 灵敏度（sensitivity）
	sensitivity = TP/P，表示的是所有正例中被分对的比例，衡量了分类器对正例的识别能力。

4) 特异性（specificity)
	specificity = TN/N，表示的是所有负例中被分对的比例，衡量了分类器对负例的识别能力。

5) 精度（precision）查准率
	precision=TP/(TP+FP)，精度是精确性的度量，表示被分为正例的示例中实际为正例的比例。

6) 召回率（recall）查全率
	召回率是覆盖面的度量，度量有多个正例被分为正例，recall=TP/(TP+FN)=TP/P=sensitivity，可以看到召回率与灵敏度是一样的。

ROC曲线是（Receiver Operating Characteristic Curve，受试者工作特征曲线）的简称，是以灵敏度（真阳性率）为纵坐标，以1减去特异性（假阳性率）为横坐标绘制的性能评价曲线。可以将不同模型对同一数据集的ROC曲线绘制在同一笛卡尔坐标系中，ROC曲线越靠近左上角，说明其对应模型越可靠。也可以通过ROC曲线下面的面积（Area Under Curve, AUC）来评价模型，AUC越大，模型越可靠。

PR曲线是Precision Recall Curve的简称，描述的是precision和recall之间的关系，以recall为横坐标，precision为纵坐标绘制的曲线。该曲线的所对应的面积AUC实际上是目标检测中常用的评价指标平均精度（Average Precision, AP）。AP越高，说明模型性能越好。

### KNN(k Nearest Neighbor)K近邻

knn思路是：如果一个样本在特征空间中的k个最相似(即特征空间中最邻近)的样本中的大多数属于某一个类别，则该样本也属于这个类别，其中K通常是不大于20的整数，算法的结果很大程度取决于K的选择。

优点：简单

缺点：   1.K的选择对结果影响很大

​		2.计算量很大

### SVM(support vector machine)支持向量机



### Navie Bayes朴素贝叶斯

最大化后验概率

### HMM(hidden markov model)隐马尔可夫

HMM用来描述一个含有隐含未知参数的马尔可夫过程,主要是针对序列建模,序列包含不可观察的隐含状态序列和可以观测的观测序列,并从观测序列中确定状态序列的隐含参数.一般来说,马尔可夫链是指状态序列.隐含状态到可见状态的概率叫做输出概率,隐含状态之间存在转换概率.

对于HMM来说，如果提前知道所有隐含状态之间的转换概率和所有隐含状态到所有可见状态之间的输出概率，做模拟是相当容易的,但是应用HMM模型时候呢，往往是缺失了一部分信息的.

解决三类问题:

1.根据观测序列,求转换概率(最重要)

2.已知转换概率,根据观测序列,求状态序列

解法:最大化观测序列的概率(维特比算法)

3.已知转换概率,根据观测序列,求出现序列的概率

### CRF(Conditional Random Field)条件随机场



## 7.Deep Learning 深度学习

### R-CNN

#### R-CNN（region-based CNN）

1.selective search

颜色相似性（颜色直方图）

#### Fast R-CNN

#### Faster R-CNN

#### Mask R-CNN

#### YOLO

## 数据集

