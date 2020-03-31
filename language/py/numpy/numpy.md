
# numpy笔记
numpy提供了两种基本的对象:

            ndarray:它是存储单一数据类型的多维数组,简称数组
            ufunc:它是一种能够对数组进行处理的特殊函数

#### np的操作：

array,arange,np.数据类(np.int32),typeDict
empty,eye,ones,zeros,full,concatenate,split,transpose,swapaxes

#### ufunc函数：

broadcast_arrays,ogrid

#### ndarray的操作：

dtype,ndim,shape,reshape,strides,data,T,astype,flags,view,copy,repeat

## 一.ndarray

### 1.基础

#### 1.1数据结构


```python
import numpy as np
a=np.array([[1,2,3],[4,5,6]],dtype=np.float32)
a.dtype
a.ndim
a.shape
a.strides
a.data
a.T
type(a)
```

ndarray.dtype：存储了数组保存的元素的类型。float32

ndarray.ndim：它是一个整数，保存了数组的维度，即多少个轴

ndarray.shape：它是一个整数的元组，每个元素一一对应地保存了数组某个维度的大小（即某个轴的长度）。

ndarray.strides：它是一个整数的元组，每个元素保存着每个轴上相邻两个元素的地址差。即当某个轴的下标增加1 时，数据存储区中的指针增加的字节数
组中元素类型为float32；该数组有2 个轴。每个轴的长度都是 3 个元素。
第 0 轴增加1时，下标增加 12字节（也就是 3个元素，即一行的距离）；
第 1 轴增加 1时，下标增加 4字节（也就是一个元素的距离）。

ndarray.data：它指向数组的数据的存储区

ndarray.T:表示其转置

#### 1.2数据排列格式
排列格式有两种：C语言格式和Fortran语言格式。

C语言中，多维数组的第 0 轴是最外层的。即 0 轴的下标增加 1时，元素的地址增加的字节数最多
Fortran语言中，多维数组的第 0 轴是最内层的。即 0 轴的下标增加 1时，元素的地址增加的字节数最少

numpy中默认是以 C语言格式存储数据。如果希望改为Fortran格式，则只需要在创建数组时，设置order参数为"F" 


```python
b=np.array(a,order="F")
a.flags,b.flags
```

#### 1.3dtype

需要指定dtype参数时，你可以使用numpy.float16，也可以传递一个表示数值类型的字符串。numpy中的每个数值类型都有几种字符串表示。字符串和类型之间的对应关系都存储在numpy.typeDict字典中。


```python
np.typeDict
```

dtype是一种对象，它不同于数值类型。只有dtype.type才能获取对应的数值类型


```python
a.dtype,a.dtype.type
```

使用ndarray.astype()方法可以对数组元素类型进行转换。


```python
b=a.astype(dtype=np.int32)
b.dtype.type
```

#### 1.4shape

使用ndarray.reshape()方法调整数组的维度。你可以在某个维度设置其长度为 -1，此时该维度的长度会被自动计算


```python
a=np.arange(0,8)
b=a.reshape(2,4)
c=b.reshape(-1,2)
print(a)
print(b)
print(c)
```

可以直接修改ndarry的shape属性，此时直接修改原始数组。


```python
a.shape=(4,2)
print(a)
```

#### 1.3view

从同一块数据区创建不同的dtype数组。即使用不同的数值类型查看同一段内存中的二进制数据。
它们使用的是同一块内存。
改变的是读取数据的方式，会造成和原有数据的不一致


```python
b=a.view(np.float32)
a,b
```

如果我们直接修改原始数组的dtype，则同样达到这样的效果，此时直接修改原始数组。


```python
b.dtype=np.int32
b
```

#### 1.4 strides

可以直接修改ndarray对象的strides属性。此时修改的是原始数组。


```python
a=np.array([[1,2,3],[4,5,6],[7,8,9]],dtype=np.int32)
a.strides=(8,4)
a
```

#### 1.5拷贝？

有三种情况

(1)简单的赋值操作并不拷贝ndarray的任何数据，这种情况下是新的变量引用ndarray对象
（类似于列表的简单赋值）


```python
b=a
b is a
```

(2)如ndarray.view()方法创建一个新的ndarray但是与旧ndarray共享相同的数据存储区。新创建的那个数组称作视图数组。对于数组的分片操作返回的是一个ndarray的视图。对数组的索引返回的不是视图，而是含有基础数据。


```python
c=a.view()
e=a[1:2]
c.base is a,e.base is a
```

(3)ndarray.copy()操作会返回一个完全的拷贝，不仅拷贝ndarray也拷贝数据存储区。


```python
f=a.copy()
f is a
```

### 2.数组的创建

np.empty(shape,[,dtype,order])
一个新的ndarray，指定了shape和dtype，但是没有初始化元素。因此其内容是随机的。
empty_like
返回一个新的ndarray，shape与a相同，但是没有初始化元素。因此其内容是随机的。


```python
result1=np.empty((2,2))
result2=np.empty_like(result1)
result1,result2
```

np.eye(N[, M, k, dtype])：返回一个二维数组，对角线元素为1，其余元素为0。
k默认为0表示对角线元素为1，
如为正数则表示对角线上方一格的元素为1，
如为负数表示对角线下方一格的元素为1.


```python
result=np.eye(2,M=3)
result
```


```python
result1=np.eye(3,k=-1)
result1
```

np.identity(n[, dtype]) ：返回一个单位矩阵


```python
result3=np.identity(3)
result3
```

np.ones(shape[, dtype, order])：返回一个新的ndarray，指定了shape和type，每个元素初始化为1.
np.ones_like(a[, dtype, order, subok]) ：返回一个新的ndarray，shape与a相同，每个元素初始化为1。
np.zeros(shape[, dtype, order]) ：返回一个新的ndarray，指定了shape和type，每个元素初始化为0.
np.zeros_like(a[, dtype, order, subok])：返回一个新的ndarray，shape与a（另一个数组）相同，每个元素初始化为0。

p.full(shape, fill_value[, dtype, order])：
返回一个新的ndarray，指定了shape和type，每个元素初始化为fill_value。


```python
result=np.full((2,3),888)
result
```

从现有数据创建

np.asarray(a[, dtype, order])：将a转换成一个ndarray。其中a是array_like的对象
np.asmatrix(data[, dtype])：返回matrix
np.copy(a[, order])：返回ndarray的一份深拷贝

按区间创建

np.arange([start,] stop[, step,][, dtype]):返回均匀间隔的值组成的一维ndarray。区间是半闭半开的[start,stop)

np.linspace(start, stop[, num, endpoint, ...]) ：返回num个均匀采样的数值组成的一维ndarray（默认为50）。
                                                                         区间是闭区间[start,stop]。endpoint为布尔值，如果为真则表示stop是最后采样的值（默认为True），否则结果不包含stop。 
                                                                         
np.logspace(start, stop[, num, endpoint, base, ...])：返回对数级别上均匀采样的数值组成的一维ndarray。采样点开始于base^start，结束于base^stop。base为对数的基，默认为 10。                                                                         

### 3.数组索引

#### 3.1一维数组

一个切片作为索引下标，如a1[i:j]。通过切片获得的新的数组是原始数组的一个视图，
它与原始数组共享相同的一块数据存储空间。 

一个整数列表对数组进行存取，如a1[[i1,i2,i3]]。此时会将列表中的每个整数作为下标(i1/i2/i3)，

使用列表作为下标得到的数组(为 np.array([a1[i1],a1[i2],a1[i3]]))不和原始数组共享


```python
a=np.arange(0,10,dtype=np.int32)
print(a)
t=a[[0,2,3]]
print(t)
s=a[2:8:2]
print(s)
```

可以指定一个整数数组作为数组下标,当下标数组是一维数组时，其结果和用列表作为下标的结果相同,当下标是多维数组时，结果也是多维数组


```python
a=np.arange(0,10,dtype=np.int32)
b=np.array([[1,3,5],[2,4,6]])
t=a[b]
print(t)
```

可以指定一个布尔数组作为数组下标，如a1[b]。此时将获得数组a1中与数组b中的True对应的元素。新数组不和原始数组共享数据。

可以赋一个值，此时该值会填充被选取出来的每一个位置,数组或者列表的形状要跟你选取出来的位置的形状完全匹配


```python
a[b]=[[0,0,0],[0,0,0]]
print(a)
```

#### 3.2多维度数组

多维数组使用元组作为数组的下标，如a[1,2]，当然你也可以添加圆括号为a[(1,2)]。

多维数组切片


```python
a=np.arange(0,15).reshape(3,5)
print(a)
b=a[2:,::2]
print(b)
```

#### 3.3操作多维数组

numpy.concatenate((a1, a2, ...), axis=0)：连接多个数组。其中(a1,a2,...)为数组的序列，给出了待连接的数组，它们沿着axis指定的轴连接。


```python
a1=np.arange(0,10).reshape(2,5)
a2=np.arange(11,21).reshape(2,5)
c1=np.concatenate([a1,a2],axis=1)
c2=np.concatenate([a1,a2],axis=0)
print(c1)
print(c2)
```

numpy.vstack(tup):等价于numpy.concatenate((a1, a2, ...), axis=0)。沿着 0 轴拼接数组

沿0轴拼接（垂直拼接），增加行

numpy.hstack(tup):等价于numpy.concatenate((a1, a2, ...), axis=1)。沿着 1 轴拼接数组

沿1轴拼接（水平拼接），增加列

numpy.split(ary, indices_or_sections, axis=0)用于沿着指定的轴拆分数组ary。indices_or_sections指定了拆分点：

如果为整数N，则表示平均拆分成N份。如果不能平均拆分，则报错

如果为序列，则该序列指定了划分区间（无需指定最开始的0起点和终点）。如[1,3]指定了区间：[0,1],[1,3],[3:]

numpy.array_split(ary, indices_or_sections, axis=0)的作用也是类似。唯一的区别在于：当indices_or_sections为整数，且无法平均拆分时，并不报错，而是尽可能的维持平均拆分。


```python
a=np.arange(0,20).reshape(4,5)
np.split(a,2,axis=0)
```


```python
np.split(a,[1,3],axis=1)
```

numpy.transpose(a, axes=None)：重置轴序。如果axes=None，则默认重置为逆序的轴序（如原来的shape=(1,2,3)，逆序之后为(3,2,1)）。如果axes!=None，则要给出重置后的轴序。它获得的是原数组的视图。


```python
a.shape=(5,2,2)
np.transpose(a)
```

numpy.swapaxes(a, axis1, axis2)：交换指定的两个轴axis1/axis2。它获得是原数组的视图。


```python
b=np.swapaxes(a,0,1)
print(a)
print(b)
```

#### 3.4打印

要想任何时候都打印全部数据，可以在print(array)之前设置选项numpy.set_printoptions(threshold='nan')。这样后续的打印ndarray就不会省略中间数据。


```python
np.set_printoptions(threshold=1000)
```

### 4.其他

在numpy中，有几个特殊的数：

numpy.nan表示NaN（Not a Number），它并不等价于numpy.inf（无穷大）。
numpy.inf：正无穷
numpy.PINF：正无穷（它就引用的是numpy.inf）
numpy.NINF：负无穷

numpy.nan_to_num(x)：将数组x中的下列数字替换掉，返回替换掉之后的新数组：

NaN：替换为0
正无穷：替换为一个非常大的数字
负无穷：替换为一个非常小的数字

## 二.ufunc函数

ufunc 函数是对数组的每个元素进行运算的函数。numpy很多内置的ufunc函数使用C语言实现的，计算速度非常快。

基本上所有的ufunc函数可以指定一个out参数来保存计算结果数组，并返回out数组。同时如果未指定out参数，则创建新的数组来保存计算结果。

### 1.广播

np.broadcast_arrays() 查看广播之后的数组 


```python
a1=np.array([1,2,3,4])
a2=np.arange(0,16).reshape(4,4)
a3=np.arange(0,4).reshape(4,1)
np.broadcast_arrays(a1,a2,a3)
```

ndarray.repeat()方法来手动重复某个轴上的值.其用法为ndarray.repeat(repeats, axis=None)，其中：

repeats为重复次数
axis指定被重复的轴，即沿着哪一轴重复。如果未指定，则将数组展平然后重复。返回的也是一个展平的数组


```python
a=np.array([[1,2],[3,4]])
print(a.repeat(2))
print(a.repeat(3,axis=0))
```

### 2.逻辑运算

由于python中的布尔运算使用and/or/not关键字，因此它们无法被重载。numpy提供的数组布尔运算只能通过ufunc函数进行，这些函数以logical_开头。进行逻辑运算时，对于数值零视作False；对数值非零视作True。运算结果也是一个布尔类型的数组：

与：ufunc函数的形式：numpy.logical_and(x1,x2[,out=y])

或：ufunc函数的形式：numpy.logical_or(x1,x2[,out=y])

否定：ufunc函数的形式：numpy.logical_not(x[,out=y])

异或：ufunc函数的形式：numpy.logical_xor(x1,x2[,out=y])

numpy.any(x)：只要数组中有一个元素值为True（如果数值类型，则为非零），则结果就返回True；否则返回False

numpy.all(x)：只有数组中所有元素都为True（如果数值类型，则为非零），则结果才返回True；否则返回False

### 3.位运算

numpy提供的位运算如下，这些位运算同时提供了函数形式（这些函数以bitwise_开头）以及表达式形式。其中输入数组必须是整数或者布尔类型（如果是浮点数则报错）：

按位与：表达式形式y=x1&x2，使用ufunc函数的形式：numpy.bitwise_and(x1,x2[,out=y])

按位或：表达式形式y=x1|x2，使用ufunc函数的形式：numpy.bitwise_or(x1,x2[,out=y])

按位取反：表达式形式y=~x，使用ufunc函数的形式：numpy.bitwise_not(x[,out=y])

按位异或：表达式形式y=x1^x2，使用ufunc函数的形式：numpy.bitwise_xor(x1,x2[,out=y])

### 4.自定义 ufunc 函数

my_ufunc=frompyfunc(func,nin,nout)。其中：

func：计算单个元素的函数
nin：func的输入参数的个数
nout：func返回值的个数


```python
def func_power(x,n):
    return x**n
my_func=np.frompyfunc(func_power,2,1)
my_func([1,2,3],3)
```

### 5.数学函数

下面是一元的数学函数：

abs/fabs：计算整数、浮点数或者复数的绝对值。对于非复数值，可以使用更快的fabs
sqrt ：计算平方根，相当于a**0.5
square：计算平方，相当于a**2
exp：计算指数 
log/log10/log2/log1p：
sign：计算 
ceil：计算各元素的ceiling值：大于等于该值的最小整数
floor：计算个元素的floor值：小于等于该值的最大整数
rint：将各元素四舍五入到最接近的整数，保留dtype
modf：将数组的小数和整数部分以两个独立数组的形式返回
isnan：返回一个布尔数组，该数组指示那些是NaN
isfinite/isinf：返回一个布尔数组，该数组指示哪些是有限的/无限数
cos/cosh/sin/sinh/tan/tanh：普通和双曲型三角函数
arccos/arcsosh/arcsin/arcsinh/arctan/arctanh:反三角函数

### 6.线性代数

numpy.dot(a, b, out=None)：计算矩阵的乘积。对于一维数组，他计算的是内积；对于二维数组，他计算的是线性代数中的矩阵乘法。


```python
a1=np.arange(0,12).reshape(3,4)
a2=np.arange(0,12).reshape(4,3)
r=np.dot(a1,a2)
print(r)
```

numpy.vdot(a, b)：返回一维向量之间的点积。如果a和b是多维数组，则展平成一维再点积


```python
vr=np.vdot(a1,a2)
print(vr)
```

numpy.cross(a, b, axisa=-1, axisb=-1, axisc=-1, axis=None):计算两个向量之间的叉乘。

numpy.inner(a, b)：计算矩阵的内积(返回一个标量，点乘)。对于一维数组，它计算的是向量点积；对于多维数组，则它计算的是：每个数组最后轴作为向量，由此产生的内积。

numpy.outer(a, b, out=None)：计算矩阵的外积(返回向量，叉乘)。它始终接收一维数组。如果是多维数组，则展平成一维数组。
