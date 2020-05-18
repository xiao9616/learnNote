

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

### 3.元类编程

动态属性

```python
class Person:
    def __init__(self):
        self._age = 0

    @property
    def age(self):
        return self._age

    @age.setter
    def age(self, value):
        self._age = value


p = Person()

p.age = 21
print(p._age)
print(p.age)
```

getattr是在找不到属性时调用,getattribute是在所有属性访问之前被调用

属性描述符

```python
class IntField:
    def __get__(self, instance, owner):
        return self.value

    def __set__(self, instance, value):
        if not isinstance(value, numbers.Integral):
            raise ValueError("int value need")
        self.value = value

    def __delete__(self, instance):
        pass


class Person:
    def __init__(self):
        self._age = IntField()
```

new和init

```python
class Person:
    def __new__(cls, *args, **kwargs):
        print("in new")
        return super().__new__(cls)

    def __init__(self):
        print("in init")
        pass
```

new用来控制对象生成过程,在对象生成之前

init是用来完善对象的

如果new不返回对象,则不会调用init函数

### 4.抽象基类

与鸭子类型的区别就是，鸭子类型不需要指定共同的基类，鸭子类型本身语言就是动态的

```python
class dog():
    def say(self):
        print("dog")


class cat():

    def say(self):
        print("cat")


class duck():
    def say(self):
        print("duck")


ani_list = [dog, cat, duck]
for i in ani_list:
    i().say()
```

```
dog
cat
duck
```

抽象基类两种使用场景

1.某些情况下需要判断某个对象的类型

```python
from collections import abc
```

包含如下的抽象基类

```python
__all__ = ["Awaitable", "Coroutine",
           "AsyncIterable", "AsyncIterator", "AsyncGenerator",
           "Hashable", "Iterable", "Iterator", "Generator", "Reversible",
           "Sized", "Container", "Callable", "Collection",
           "Set", "MutableSet",
           "Mapping", "MutableMapping",
           "MappingView", "KeysView", "ItemsView", "ValuesView",
           "Sequence", "MutableSequence",
           "ByteString",
           ]
```

每个抽象基类都包含subclasshook，用来判断是否为内置类型或者是否实现了某些魔法函数

```python
@classmethod
def __subclasshook__(cls, C):
  if cls is Sized:        
      return _check_methods(C, "__len__")    
  return NotImplemented
```

```python
class imp(base):

    def get(self):
        print("imp get")

    def set(self):
        print("imp set")

    def __len__(self):
        return 6
from _collections_abc import *
print(isinstance(imp(),Sized)) #True
```

2.需要强制某些子类实现特定的方法（原生也可以通过raise NotImplentedError来实现）

abc实现

```python
import abc
from abc import abstractmethod, ABCMeta


class base(metaclass=ABCMeta):
    @abstractmethod
    def get(self):
        print("get")

    @abstractmethod
    def set(self):
        print("set")


class imp(base):

    def get(self):
        print("imp get")

    def set(self):
        print("imp set")
imp().get()
```

raise error实现

```python
class base:
    def get(self):
        raise NotImplementedError
class imp(base):
    def set(self):
        print("set")

imp().get()
```

```shell
Traceback (most recent call last):
  File "/home/user/github/YOLOv3_TensorFlow2/test.py", line 17, in <module>
    imp().get()
  File "/home/user/github/YOLOv3_TensorFlow2/test.py", line 12, in get
    raise NotImplementedError
NotImplementedError
```

raise方法只有当调用get方法时才会报错

### 5.魔法函数

本质上是为了方法的重载，主要的魔法函数：

```python
构造析构：
object.__new__(self, ...)
object.__init__(self, ...)
object.__del__(self)

二元操作符：
+	object.__add__(self, other)
-	object.__sub__(self, other)
*	object.__mul__(self, other)
//	object.__floordiv__(self, other)
/	object.__div__(self, other)
%	object.__mod__(self, other)
**	object.__pow__(self, other[, modulo])
<<	object.__lshift__(self, other)
>>	object.__rshift__(self, other)
&	object.__and__(self, other)
^	object.__xor__(self, other)
|	object.__or__(self, other)

扩展二元操作符：
+=	object.__iadd__(self, other)
-=	object.__isub__(self, other)
*=	object.__imul__(self, other)
/=	object.__idiv__(self, other)
//=	object.__ifloordiv__(self, other)
%=	object.__imod__(self, other)
**=	object.__ipow__(self, other[, modulo])
<<=	object.__ilshift__(self, other)
>>=	object.__irshift__(self, other)
&=	object.__iand__(self, other)
^=	object.__ixor__(self, other)
|=	object.__ior__(self, other)

一元操作符：
-	object.__neg__(self)
+	object.__pos__(self)
abs()	object.__abs__(self)
~	object.__invert__(self)
complex()	object.__complex__(self)
int()	object.__int__(self)
long()	object.__long__(self)
float()	object.__float__(self)
oct()	object.__oct__(self)
hex()	object.__hex__(self)
round()	object.__round__(self, n)
floor()	object__floor__(self)
ceil()	object.__ceil__(self)
trunc()	object.__trunc__(self)

比较函数：
<	object.__lt__(self, other)
<=	object.__le__(self, other)
==	object.__eq__(self, other)
!=	object.__ne__(self, other)
>=	object.__ge__(self, other)
>	object.__gt__(self, other)

类的表示、输出：
str()	object.__str__(self) 
repr()	object.__repr__(self)
len()	object.__len__(self)
hash()	object.__hash__(self) 
bool()	object.__nonzero__(self) 
dir()	object.__dir__(self)
sys.getsizeof()	object.__sizeof__(self)

类容器：
len()	object.__len__(self)
self[key]	object.__getitem__(self, key)
self[key] = value	object.__setitem__(self, key, value)
del[key] object.__delitem__(self, key)
iter()	object.__iter__(self)
reversed()	object.__reversed__(self)
in操作	object.__contains__(self, item)
字典key不存在时	object.__missing__(self, key)
```

#### __init __ __new __  __del __

__init __  方法是Python最基本的魔术方法，通过此方法我们可以定义一个对象的初始操作，实际上它背后还有一个__new __方法。__new __是用来创建类并返回这个类的实例, 而__init __只是将传入的参数来初始化该实例。
对象生命周期调用结束时，__del __ 方法会被调用。

#### __getitem__ __setitem__ __delitem__

如果我们想实现创建类似于序列和映射的类，可以通过重写魔法方法__getitem__、__setitem__、__delitem__、__len__方法去模拟。

为class生成可迭代对象iterable，并且可以序列化，可以切片

```python
class Company(object):
    def __init__(self, employee_list) -> None:
        self.employee = employee_list

    def __getitem__(self, item):
        return self.employee[item]

    def __setitem__(self, key, value):
        self.employee[key] = value

    def __delitem__(self, key):
        del self.employee[key]

    def __len__(self):
        return len(self.employee)


company = Company(["xiao", "wen", "xuan"])
for i in company:
    print(i)
print(company[:-2])
company[1] = "dada"
del company[1]
```

```shell
xiao
wen
xuan
['xiao']
```

#### __len__

len()调用的是对象的len方法

```python
class Company:
    def __init__(self, employee_list) -> None:
        self.employee = employee_list

    def __getitem__(self, item):
        return self.employee[item]

    def __len__(self):
        return len(self.employee)

company = Company(["xiao", "wen", "xuan"])
print(len(company))
```

#### __str__ __repr__

str()主要面向用户，其目的是可读性，返回形式为用户友好性和可读性都较强的字符串类型；而repr()面向的是Python解释器，或者说开发人员，其目的是准确性，其返回值表示Python解释器内部的含义，常作为编程人员debug用途。

在解释器中直接输入a时调用repr()函数，而`print(a)`则调用str()函数。

repr()的返回值一般可以用`eval()`函数来还原对象，通常来说有如下等式。

```python
obj == eval(repr(obj))
```

#### __hash__



#### __iter__ __next__

迭代器，常见的就是我们在使用`for`语句的时候，python内部其实是把`for`后面的对象上使用了内建函数`iter`

```python
a = [1, 2, 3]
for i in a:
    do_something()
```

其实在python内部进行了类似如下的转换：

```python
a = [1, 2, 3]
for i in iter(a):
    do_something()
```

iter返回的是什么呢，就是一个迭代对象，它主要映射到了类里面的__iter__函数，此函数返回的是一个实现了__next__的对象。

Iterable: 有迭代能力的对象，一个类，实现了__iter__，那么就认为它有迭代能力，通常此函数必须返回一个实现了__next__的对象，如果自己实现了，你可以返回self，当然这个返回值不是必须的；
Iterator: 迭代器(当然也是Iterable)，同时实现了__iter__和__next__的对象，缺少任何一个都不算是Iterator

```python
class MyRange(object):
    def __init__(self, end):
        self.start = 0
        self.end = end

    def __iter__(self):
        return self

    def __next__(self):
        if self.start < self.end:
            ret = self.start
            self.start += 1
            return ret
        else:
            raise StopIteration
a = MyRange(5)
print(isinstance(a, Iterable))
print(isinstance(a, Iterator))

for i in a:
    print(i)
```

```shell
True
True
0
1
2
3
4
```

next方法调用实例对象的next方法

```
next(a)
```

可以看见一个很明显的好处是，每次产生的数据，是产生一个用一个，什么意思呢，比如我要遍历`[0, 1, 2, 3.....]`一直到10亿，如果使用列表的方式，那么是会全部载入内存的，但是如果使用迭代器，可以看见，当用到了(也就是在调用了`next`)才会产生对应的数字，这样就可以节约内存了，这是一种懒惰的加载方式。

### 6 isinstance type区别

判断类型是否一致

```python
#imp继承base
b = imp()
print(type(b) is imp)	#True
print(type(b) is base)	#False
print(isinstance(b, imp)) 	#True
print(isinstance(b, base))	#True
```

### 7.垃圾回收机制

```python
 a = object()
 b = a
 del a
 print(b)
 print(a)
```

```shell
<object object at 0x1138a2840>
Traceback (most recent call last):
  File "/Users/xuan/learnNote/project/yolo3/yolo3/test.py", line 14, in <module>
    print(a)
NameError: name 'a' is not defined
```

垃圾回收机制通过引用计数来实现,只有引用计数为0时,对象才会被回收

对于类来说,当引用计数为0时,调用del魔法函数

```python
class A:
    def __del__(self):
        pass
```

### 8.staticmethod 	classmethod 	abstractmethod

静态方法：

```python
class static():
    @staticmethod
    def a():
        pass
static.a()
```

类方法：

```python
class cls():
    @classmethod
    def a(cls):
        pass
cls.a()
```

抽象方法：

```python
class base(metaclass=ABCMeta):
    @abstractmethod
    def get(self):
        print("get")
```

### 9.私有属性

```python
class A:
    def __init__(self):
        self.__name="xiao"
    def get_name(self):
        print(self.__name)
a=A()
a.get_name()
print(a._A__name)
```

对于具有双下划线开头的属性，python会转化该属性为

```
_ClassName__attr
```

的格式，所以python不是绝对安全的和绝对私有封装的

### 10.类和实例查找顺序

![image-20200515204221173](python_advance.assets/image-20200515204221173.png)

![image-20200515204228393](python_advance.assets/image-20200515204228393.png)

特别说明,super的执行顺序也是如此

### 11.python自省机制

```python
class person:

    def __init__(self) -> None:
        self.name = "xiao"


class student(person):
    def __init__(self, schoolname) -> None:
        self.school_name = schoolname


stu = student("yixiao")

print(stu.__dict__)
print(person.__dict__)
print(dir(stu))
print(dir(person))
```

```shell
{'school_name': 'yixiao'}
{'__module__': '__main__', '__init__': <function person.__init__ at 0x10f835950>, '__dict__': <attribute '__dict__' of 'person' objects>, '__weakref__': <attribute '__weakref__' of 'person' objects>, '__doc__': None}
['__class__', '__delattr__', '__dict__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__', '__getattribute__', '__gt__', '__hash__', '__init__', '__init_subclass__', '__le__', '__lt__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', 'school_name']
['__class__', '__delattr__', '__dict__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__', '__getattribute__', '__gt__', '__hash__', '__init__', '__init_subclass__', '__le__', '__lt__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__']
```

```python
stu.__dict__["school_name"]="erxiao"
print(stu.__dict__)
```

```
{'school_name': 'erxiao'}
```

## 关键字

### 1. is ==

is判断对象的id是否相等

==判断值是否相等

## 内置类型(内置class对象)

对象由三个信息组成:地址,类型,值

```python
a=1
id(a)	#地址
type(a)	#类型
a	#1就是a指向的值
```

### None

None是解释器中唯一的对象,所以地址相同

```python
a=None
b=None
print(a==b)	#True
print(id(a)==id(b)) #True
```

### 数值

float int complex bool

### 迭代类型

只要对象实现了next iter方法就可以称作迭代类型（只实现iter叫做可迭代iterable，同时实现iter next叫做迭代器iterator）

可以使用for进行迭代

class对象可以实现getItem方法，可以将class生成的对象变成可迭代的

### 序列类型

list bytes bytesarray memoryview  range tuple str array

通过实现getitem，setitem，delitem就可以将该对象转换为序列类型

```python
import numbers
from collections.abc import Sequence, MutableSequence


class Group(Sequence):

    def __init__(self, grouop_name, company_name, staffs) -> None:
        self.group_name = grouop_name
        self.company_name = company_name
        self.staffs = staffs

    def __getitem__(self, item):
        cls=type(self)
        if isinstance(item,slice):
            return cls(grouop_name=self.group_name,company_name=self.company_name,staffs=self.staffs[item])
        elif isinstance(item,numbers.Integral):
            return cls(grouop_name=self.group_name,company_name=self.company_name,staffs=[self.staffs[item]])

    def __contains__(self, item):
        if item in self.staffs:
            return True
        else:
            return False

    def __iter__(self):
        return iter(self.staffs)

    def __reversed__(self):
        return reversed(staffs)

    def __len__(self):
        return len(self.staffs)

staffs = ["xiao", "wen", "xuan"]
group = Group(company_name="gree", grouop_name="user", staffs=staffs)
print(group[0:2].staffs)
print(group[0].staffs)
print(len(group))
for i in group:
    print(i)
```

### 映射类型

dict



### 集合

set frozenset



### with上下文管理器

需要实现enter和exit魔法函数,分别表示with进入时执行enter,离开with时执行exit

简化try finally语法

需要实现enter和exit魔法函数,分别表示with进入时执行enter,离开with时执行exit

```python 
class person:
    def __enter__(self):
        print("enter")
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        print("exit")

    def doSomething(self):
        print("doing something")


with person() as p:
    print("do 1")
    p.doSomething()
```

```shell
enter
do 1
doing something
exit
```

使用 contextlib来简化使用

```python
import contextlib

@contextlib.contextmanager
def file_open(filename):
    print("file open")
    yield {}
    print("file end")


with file_open("xiao.txt") as f:
    print("file process")
```

```
file open
file process
file end
```

## 列表生成式 生成器表达式 字典推导式 集合推导式

```python
list = [i for i in range(10) if i % 2 == 0]
print(type(list))
print(list)

iter = (i for i in range(10) if i % 2 == 0)
print(type(iter))
for i in iter:
    print(i)

origin_dict = {"xiao": 22, "wen": 23, "xuan": 24}
reverse_dict = {value: key for key, value in origin_dict.items()}
print(type(reverse_dict))
print(reverse_dict)

reverse_set={value for key, value in origin_dict.items()}
print(type(reverse_set))
print(reverse_set)
```

```shell
<class 'list'>
[0, 2, 4, 6, 8]

<class 'generator'>
0 2 4 6 8

<class 'dict'>
{24: 'xuan', 22: 'xiao', 23: 'wen'}

<class 'set'>
{24, 22, 23}
```

## 多线程

### GIL

```python
import dis


def add(a):
    a += 1
    return a


print(dis.dis(add))
```

```
 12           0 LOAD_FAST                0 (a)
              2 LOAD_CONST               1 (1)
              4 INPLACE_ADD
              6 STORE_FAST               0 (a)

 13           8 LOAD_FAST                0 (a)
             10 RETURN_VALUE
None
```

dis反编译为字节码

GIL会根据执行的字节码行数或者时间片释放GIL,在遇到io操作时会主动释放

### 线程创建运行

方式1:

```python
import threading
import time


def thread1(name):
    print("thread1 start")
    time.sleep(2)
    print("thread1 end")


def thread2(name):
    print("thread2 start")
    time.sleep(4)
    print("thread2 end")


if __name__ == '__main__':
    thread1 = threading.Thread(target=thread1,args=("xiao",))
    thread2 = threading.Thread(target=thread2,args=("xuan",))
    thread1.start()
    thread2.start()

    thread1.join()
    thread2.join()

    print("end")

```

```
thread1 start
thread2 start
thread1 end
thread2 end
end
```

方式2:

```python
class thread2(threading.Thread):

    def run(self) -> None:
        print("thread2 start")
        time.sleep(2)
        print("thread2 end")
```

### 线程中通讯

方式一:共享全局变量

方式二:消息队列

### 线程同步

#### 锁lock

```python
import threading
import time
from threading import Lock

lock=Lock()
def thread1(name):
    global lock
    lock.acquire()
    print("thread1 start")
    time.sleep(2)
    print("thread1 end")
    lock.release()


def thread2(name):
    global lock
    lock.acquire()
    print("thread2 start")
    time.sleep(4)
    print("thread2 end")
    lock.release()


if __name__ == '__main__':
    thread1 = threading.Thread(target=thread1,args=("xiao",))
    thread2 = threading.Thread(target=thread2,args=("xuan",))
    thread1.start()
    thread2.start()

    thread1.join()
    thread2.join()

    print("end")
```

```
thread1 start
thread1 end
thread2 start
thread2 end
end
```

#### 可重入锁rlock

在同一个线程中,可以连续调用多次acquire

#### 条件锁Condition

通过wait等待,通过notify通知其他线程

## 协程