

# python高级

## 面向对象

### 1.python中一切皆对象

函数和类也是对象,这是和java,c++不同的.注意括号的使用

```python
def func(name):
    print(name)

class cls():

    def __init__(self) -> None:
        print("xuan")

myFunc=func
myFunc('xiao')

myClass=cls
myClass()
```

```shell
xiao
xuan
```

可以被加载进列表,也可以作为函数参数,注意括号

```python
mylist = []
mylist.append(func)
mylist.append(cls)
for i in mylist:
    print(i)
    print(i())
```

```shell
<function func at 0x1058e3ea0>
wen
None
<class '__main__.cls'>
xuan
<__main__.cls object at 0x10d568668>
```

函数也可以作为函数的返回值(装饰器原理)

```python
def decorator():
    print("decorator")
    return func

func_2=decorator()
func_2("i have been decoratored")
```

```shell
decorator
i have been decoratored
```

### 2.type class object关系和区别

type->class对象

```python
a=1
b="abc"
print(type(1))
print(type(a))
print(type(int))
```

```shell
<class 'int'>
<class 'int'>
<class 'type'>

#type -> int ->1
```

class对象由type生成,包括python内置数据结构都是

```python
class Student():
    pass

stu = Student()
print(type(stu))
print(type(Student))

a = [1, 2, 3]
print(type(a))
print(type(list))
```

```shell
<class '__main__.Student'>
<class 'type'>

<class 'list'>
<class 'type'>
```

object是顶层基类,他的父类为空( ) . 不指定class对象的基类,那么该class对象都由object派生而来

```python
print(object.__bases__)
print(type(object))
print(type.__bases__)
```

```shell
()
<class 'type'>
(<class 'object'>,)
```

```python
print(Student.__bases__)
```

```shell
(<class 'object'>,)
```

<img src="python_advance.assets/image-20200514234153746.png" alt="image-20200514234153746" style="zoom:67%;" />

总结:

1.type() 对所有的class对象到底都是type,包括object

2.所有的class对象的基类__bases__都是object

### 3.内置类型(内置class对象)

对象由三个信息组成:地址,类型,值

```python
a=1
id(a)	#地址
type(a)	#类型
a	#1就是a指向的值
```

#### None

None是解释器中唯一的对象,所以地址相同

```python
a=None
b=None
print(a==b)	#True
print(id(a)==id(b)) #True
```

#### 数值

float int complex bool

#### 迭代类型

可以使用for进行迭代

#### 序列类型

list bytes bytesarray memoryview  range tuple str array

#### 映射类型

dict

#### 集合

set frozenset

#### 上下文管理器

with

## 函数

### 内置函数



### 魔法函数

