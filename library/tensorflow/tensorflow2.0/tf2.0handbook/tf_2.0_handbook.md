# TensorFlow 2.0

## 基础

### 第一个程序


```python
import tensorflow as tf
print(tf.__version__)

a=tf.constant([[1.,2.],[3.,4.]])
b=tf.constant([[5.,6.],[7.,8.]])
c=tf.matmul(a,b)
print(c)
```


```python
random_float=tf.random.uniform(shape=())
zero_vertor=tf.zeros(shape=(2),dtype=tf.int32)
print(a.shape)
print(b.dtype)
print(c.numpy())
```

### 自动求导机制


```python
x=tf.Variable(initial_value=3.)
with tf.GradientTape() as tape:
    y=tf.square(x)
y_grad=tape.gradient(y,x)
print(y_grad.numpy())
```


```python
X = tf.constant([[1., 2.], [3., 4.]])
y = tf.constant([[1.], [2.]])
w = tf.Variable(initial_value=[[1.], [2.]])
b = tf.Variable(initial_value=1.)

with tf.GradientTape() as tape:
    L=0.5*tf.reduce_sum(tf.square(tf.matmul(X,w)+b-y))
w_grad, b_grad = tape.gradient(L, [w, b]) 
print(L.numpy(),w_grad.numpy(),b_grad.numpy())
```


```python
X = tf.constant(X)
y = tf.constant(y)

a = tf.Variable(initial_value=0.)
b = tf.Variable(initial_value=0.)
variables = [a, b]

num_epoch=10000
optimizer=tf.keras.optimizers.SGD(learning_rate=1e-3)
for e in range(num_epoch):
    with tf.GradientTape() as tape:
        y_pred=a*X+b
        loss=0.5*tf.reduce_sum(tf.square(y_pred-y))
    grads=tape.gradient(loss,variables)
    optimizer.apply_gradients(grads_and_vars=zip(grads,variables))
print(a.numpy(),b.numpy())
```

## 模型建立与训练

### 自定义模型Model


```python
import tensorflow.keras as k

X = tf.constant([[1.0, 2.0, 3.0], [4.0, 5.0, 6.0]])
y = tf.constant([[10.0], [20.0]])

class Linear(k.Model):
    def __init__(self):
        super().__init__()
        self.dense=k.layers.Dense(
            units=1,
            activation=None,
            kernel_initializer=tf.zeros_initializer(),
            bias_initializer=tf.zeros_initializer()
        )
    def call(self,input):
        output=self.dense(input)
        return output

model=Linear()
optimizer=k.optimizers.SGD(learning_rate=0.01)
for i in range(100):
    with tf.GradientTape() as tape:
        y_pred=model(X)
        loss=tf.reduce_mean(tf.square(y_pred-y))
    grads=tape.gradient(loss,model.variables)
    optimizer.apply_gradients(grads_and_vars=zip(grads,model.variables))
print(model.variables)
```

keras包含的模块:
tf.keras.datasets/Model/layers/losses/optimizer/metrics/applications/models/

Sequential/Function API


```python
import tensorflow.keras as k

model=k.models.Sequential(
    k.layers.Flatten(),
    k.layers.Dense(100,activation=tf.nn.relu),
    k.layers.Softmax()
)
```


```python
inputs = tf.keras.Input(shape=(28, 28, 1))
x = tf.keras.layers.Flatten()(inputs)
x = tf.keras.layers.Dense(units=100, activation=tf.nn.relu)(x)
x = tf.keras.layers.Dense(units=10)(x)
outputs = tf.keras.layers.Softmax()(x)
model = tf.keras.Model(inputs=inputs, outputs=outputs)
```

Model.compile方法配置训练过程


```python
model.compile(
    optimizer=tf.keras.optimizers.Adam(learning_rate=0.001),
    loss=tf.keras.losses.sparse_categorical_crossentropy,
    metrics=[tf.keras.metrics.sparse_categorical_accuracy]
)
```

Model.fit方法训练模型


```python
model.fit(data_loader.train_data, data_loader.train_label, epochs=num_epochs, batch_size=batch_size)
```

Model.evaluate评估模型


```python
model.evaluate(data_loader.test_data, data_loader.test_label)
```

### 自定义层,损失函数,评估指标


```python
import tensorflow as tf

class LinearLayer(tf.keras.layers.Layer):
    def __init__(self,units):
        super().__init__()
        self.units=units
    def build(self,input_shape):
        self.w=self.add_variable(name='w',shape=[input_shape[-1],self.units],
                                initializer=tf.zeros_initializer())
        self.b = self.add_variable(name='b',
            shape=[self.units], initializer=tf.zeros_initializer())
    def call(self,inputs):
        y_pred=tf.matmul(inputs,self.w)+self.b
        retuen y_pred

```


```python
import tensorflow as tf

class MeanSquaredLoss(tf.keras.losses.Loss):
    def call(self,y_true,y_pred):
        return tf.reduce_mean(tf.square(y_pred-y_true))
```


```python
import tensorflow as tf

class SparseCategoricaAccuracy(tf.keras.metrics.Metric):
    def __init__(self):
        super().__init__()
        self.total = self.add_weight(name='total', dtype=tf.int32, initializer=tf.zeros_initializer())
        self.count = self.add_weight(name='count', dtype=tf.int32, initializer=tf.zeros_initializer())

    def update_state(self,y_true,y_pred,sample_weight=None):
        values = tf.cast(tf.equal(y_true, tf.argmax(y_pred, axis=-1, output_type=tf.int32)), tf.int32)
        self.total.assign_add(tf.shape(y_true)[0])
        self.count.assign_add(tf.reduce_sum(values))
        
    def result(self):
        return self.count / self.total
```

## tensorlfow模块

### config


```python
import tensorflow as tf
import tensorflow.keras as k

gpus=tf.config.experimental.list_physical_devices(device_type='GPU')
cpus=tf.config.experimental.list_physical_devices(device_type='CPU')
print(gpus,cpus)
```

设置当前程序可见的设备范围（当前程序只会使用自己可见的设备，不可见的设备不会被当前程序使用）


```python
tf.config.experimental.set_visible_devices(devices=gpus[0],device_type='GPU')
```

或者


```python
import os
os.environ['CUDA_VISIBLE_DEVICES']='2,3'
```

控制程序的显存使用方式：

1.仅在需要时申请显存空间（程序初始运行时消耗很少的显存，随着程序的运行而动态申请显存）；

2.限制消耗固定大小的显存（程序不会超出限定的显存大小，若超出的报错）。

设置为动态申请


```python
gpus = tf.config.experimental.list_physical_devices(device_type='GPU')
for gpu in gpus:
    tf.config.experimental.set_memory_growth(device=gpu, True)
```

设置为固定大小


```python
gpus = tf.config.experimental.list_physical_devices(device_type='GPU')
tf.config.experimental.set_virtual_device_configuration(
    gpus[0],
    [tf.config.experimental.VirtualDeviceConfiguration(memory_limit=1024)]
```

单GPU模拟多GPU环境

在实体 GPU GPU:0 的基础上建立了两个显存均为 2GB 的虚拟 GPU。


```python
gpus=tf.config.experimental.list_physical_devices('GPU')
tf.config.experimental.set_virtual_device_configuration(
    gpus[0],
    [tf.config.experimental.VirtualDeviceConfiguration(memory_limit=2048),
    tf.config.experimental.VirtualDeviceConfiguration(memory_limit=2048)]
)
```

### 模型保存与恢复

tf.train.Checkpoint
只保存模型的参数，不保存模型的计算过程，因此一般用于在具有模型源代码的时候恢复之前训练好的模型参数


```python
checkpoint = tf.train.Checkpoint(model=model)
checkpoint.save('./save/model.ckpt')
```

生成checkpoint model.ckpt-1.index model.ckpt-1.data-0000-of-00001


```python
checkpoint = tf.train.Checkpoint(model=model)
checkpoint.restore('./save/model.ckpt-1')
checkpoint.restore(tf.train.latest_checkpoint('./save')) #返回最新的ckpt
```

Checkpoint.save在训练过程中会保存许多的中间模型数据,可以使用tf.train.CheckpointManager来管理

checkpoint = tf.train.Checkpoint(model=model)
manager = tf.train.CheckpointManager(checkpoint, directory='./save', checkpoint_name='model.ckpt', max_to_keep=k)
此处， directory 参数为文件保存的路径， checkpoint_name 为文件名前缀,max_to_keep 为保留的 Checkpoint 数目


```python
manager.save(checkpoint_number=100) #指定模型自定义编号
```

tf.saved_model不仅包含参数的权值，还包含计算的流程（即计算图） 。当模型导出为 SavedModel 文件时，无需建立模型的源代码即可再次运行模型，这使得 SavedModel 尤其适用于模型的分享和部署。


```python
tf.saved_model.save(model,'./save/1')
model=tf.saved_model.load('./save/1')
```

使用继承 tf.keras.Model 类建立的 Keras 模型 model ，使用 SavedModel 载入后将无法使用 model() 直接进行推断，而需要使用 model.call().并且构建模型时需要@tf.function修饰


```python
class MLP(tf.keras.Model):
    def __init__(self):
        super().__init__()
        self.flatten = tf.keras.layers.Flatten()
        self.dense1 = tf.keras.layers.Dense(units=100, activation=tf.nn.relu)
        self.dense2 = tf.keras.layers.Dense(units=10)

    @tf.function
    def call(self, inputs):         # [batch_size, 28, 28, 1]
        x = self.flatten(inputs)    # [batch_size, 784]
        x = self.dense1(x)          # [batch_size, 100]
        x = self.dense2(x)          # [batch_size, 10]
        output = tf.nn.softmax(x)
        return output

model = MLP()
```

### tf.data

灵活的数据集构建 API，能够帮助我们快速、高效地构建数据输入的流水线，尤其适用于数据量巨大的场景。

tf.data.Dataset

tf.data.Dataset 是一个 Python 的可迭代对象，因此可以使用 For 循环迭代获取数据.


```python
import tensorflow as tf
import numpy as np

X = tf.constant([2013, 2014, 2015, 2016, 2017])
Y = tf.constant([12000, 14000, 15000, 16500, 17500])

# 也可以使用NumPy数组，效果相同
# X = np.array([2013, 2014, 2015, 2016, 2017])
# Y = np.array([12000, 14000, 15000, 16500, 17500])

dataset = tf.data.Dataset.from_tensor_slices((X, Y))

for x, y in dataset:
    print(x.numpy(), y.numpy()) 
```


```python
import matplotlib.pyplot as plt 

(train_data, train_label), (_, _) = tf.keras.datasets.mnist.load_data()
train_data = np.expand_dims(train_data.astype(np.float32) / 255.0, axis=-1)      # [60000, 28, 28, 1]
mnist_dataset = tf.data.Dataset.from_tensor_slices((train_data, train_label))

for image, label in mnist_dataset:
    plt.title(label.numpy())
    plt.imshow(image.numpy()[:, :, 0])
    plt.show()
```

tf.data.Dataset 类为我们提供了多种数据集预处理方法


Dataset.map(f) ：对数据集中的每个元素应用函数 f ，得到一个新的数据集（这部分往往结合 tf.io 进行读写和解码文件， tf.image 进行图像处理）；

Dataset.shuffle(buffer_size) ：将数据集打乱（设定一个固定大小的缓冲区（Buffer），取出前 buffer_size 个元素放入，并从缓冲区中随机采样，采样后的数据用后续数据替换）；

Dataset.batch(batch_size) ：将数据集分成批次，即对每 batch_size 个元素，使用 tf.stack() 在第 0 维合并，成为一个元素。

Dataset.prefetch() ：预取出数据集中的若干个元素


Keras 支持使用 tf.data.Dataset 直接作为输入。当调用 tf.keras.Model 的 fit() 和 evaluate() 方法时，可以将参数中的输入数据 x 指定为一个元素格式为 (输入数据, 标签数据) 的 Dataset ，并忽略掉参数中的标签数据 y 


```python
model.fit(mnist_dataset, epochs=num_epochs)
```

### @tf.function

推荐使用 @tf.function （而非 1.X 中的 tf.Session ）实现 Graph Execution，从而将模型转换为易于部署且高性能的 TensorFlow 图模型

建议在函数内只使用 TensorFlow 的原生操作，不要使用过于复杂的 Python 语句，函数参数只包括 TensorFlow 张量或 NumPy 数组，并最好是能够按照计算图的思想去构建函数

一般而言，当模型由较多小的操作组成的时候， @tf.function 带来的提升效果较大。而当模型的操作数量较少，但单一操作均很耗时的时候，则 @tf.function 带来的性能提升不会太大。

@tf.function 使用名为 AutoGraph 的机制将函数中的 Python 控制流语句转换成 TensorFlow 计算图中的对应节点

### tf.compat.v1

TensorFlow 2.0 提供了 tf.compat.v1 模块以支持 TensorFlow 1.X 版本的 API。同时，只要在编写模型的时候稍加注意，Keras 的模型是可以同时兼容 Eager Execution 模式和 Graph Execution 模式的
