#coding = utf-8
'''
Author:xiao
date= 上午8:47
'''
# 不带参数


def logger(func):
    def wrapper(*args, **kwargs):
        print("准备打印日志")
        func(*args, **kwargs)
        print("日志打印完毕")
    return wrapper


@logger
def add(a, b):
    print("{}+{}={}".format(a, b, a + b))

# 带参数


def say_hello(nation):
    def deco(func):
        def wrapper(*args, **kwargs):
            if nation == 'china':
                print("你好")
            if nation == 'america':
                print('hello')
            else:
                return
            func(*args, **kwargs)
        return wrapper
    return deco


@say_hello('china')
def xiaoming():
    pass


@say_hello('america')
def jack():
    pass

# 基于类的装饰器
# 要求实现:
# __init__:接受被装饰的函数
# __call__:实现装饰逻辑


class log(object):

    def __init__(self, func) -> None:
        self.func = func

    def __call__(self, *args, **kwargs):
        print("[INFO]:{}() is running".format(self.func.__name__))
        return self.func(*args, **kwargs)


@log
def say(something):
    print("say" + something)

# 带参数的类装饰器


class logs(object):
    def __init__(self, level):
        self.level = level

    def __call__(self, func):
        def wrapper(*args, **kwargs):
            print("[{}]:{}() is running".format(self.level, func.__name__))
            func(*args, **kwargs)
        return wrapper


@logs('WARNING')
def say_level(something):
    print("say" + something)

# @property装饰过的函数会将一个函数定义成一个属性


class student():
    def __init__(self, name):
        self.name = name

    @property
    def age(self):
        return self._age

    @age.setter
    def age(self, value):
        self._age = value

    @age.getter
    def age(self):
        return self._age


if __name__ == '__main__':
    add(1, 2)
    xiaoming()
    jack()
    say("hello")
    say_level('hello')
    s1 = student('xiao')
    s1.age = 23
    print(s1.age)
