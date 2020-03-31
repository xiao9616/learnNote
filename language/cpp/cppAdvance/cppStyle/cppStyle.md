# C++编码规范

[TOC]

## 1.Google规范

![google](./googleStyle)

## 2.命名规范

### 2.1通用命名规范

类型和变量名应该是名词性的，函数应该是动词性的

```
int num_errors;		//good
int num_complered_connections;		//good

int n;		//bad
int nerr;		//bad
```

非约定俗成的缩写不要用

```
int num_dns_connection;		//good

int pc_reader;	//bad pc可以代表很多东西
```

### 2.2文件命名

文件名要全部小写，可以包含下划线或短线，按照项目约定来

```
my_class.cpp
my—class.cpp
myclass.cpp
```

定义类时文件名成对出现foo_bar.h和foo_bar.cpp,对应FooBar类

内联函数必须放在.h文件中，如果代码较多可以放在-inl.h中。对于包含大量内联代码的类，可以有三个文件：

my_class.h

my_class.cpp

my_class-inl.h

### 2.3类型命名

类型命名每个单词首字母大写，不包含下划线

所有类型（类，结构体，typedef，枚举）使用相同约定

```
class MyClass；
struct MyStruct;
typedef vector<int> VecInt；
enmus MyEnmus;
```

### 2.4变量命名

变量名一律小写，单词以下划线相连，类的成员变量以下划线结尾或者m开头

```
string table_name;

class people{
    private:
    	string name_;
    	int age_;
    	
    	string m_name;
    	int m_age;
}
```

结构体的数据成员可以和普通变量一样

```
struct table{
    string name;
    int num_entries;
}
```

全局变量，可以以g_开头

```
int g_num_errors;
```

常量命名，开头加k单词字母大写

或者全大写；

```
const int kDayInWeek;
const int DAY_IN_WEEK;
```

静态变量使用s开头

```
static int s_nums;
```

### 2.5函数命名

函数大写开头，每个单词首字母大写

```
AddTablEntry();
DeleteUrl();
```

类内的存取函数使用get/set命名

```
class MyClass{
    private:
    	int num_entries_;
    public:
    	int get_num_entries();
    	void set_num_entries();
}
```

### 2.6命名空间

统一使用小写

```
namespace awesomeproject{
    
}
```

### 2.7枚举命名

枚举名称使用小写，枚举值使用大写

```
enum UrlTableErrors{
    OK=0,
    ERROR_OUT_OF_MEMORY,
    ERROR_MALFORMED_INPUT,
}
```

### 2.8宏定义

全部使用大写

```
#define	 ROUND(x) ...
#define PI 3.1415926
```

### 2.9总结

1.不要随意缩写

2.宏/枚举/常量全部使用大写+下划线

3.变量/文件/命名空间全部使用小写+下划线

4.函数/类型/使用大小写混合，没有下划线

6.全局变量加g_ ,静态变量加 s_ ,类成员变量加 m_

## 3.格式

### 3.1缩进

使用空格进行缩进，每次2个，不要使用Tabs

### 3.2函数声明与定义

尽量保持在同一行

```
ReturnType ClassName::FunctionName(Type par_name1,Type par_name2){
    doSomething();
}
```

如果不行，则应该如下：

```
ReturnType ClassName::FunctionName(Type par_name1,
                                   Type par_name2){
    doSomething();
}
```

甚至：

```
ReturnType ClassName::FunctionName(
    Type par_name1,
    Type par_name2){
  doSomething();
}
```

如果函数为const，const应该放在最后一个参数同一行

```
ReturnType ClassName::FunctionName(Type par_name1,
                                   Type par_name2) const {
    doSomething();
}
```

调用时同上

### 3.3逻辑表达式

if条件左右都有空格

```
if (condition) {}	//good
if(condition){}	//bad
```

switch的case块可以使用大括号也可以不用

```
switch (var) {
    case 0: {
        break;
    }
    case 1: {
        break;
    }
    default:{
        break;
    }
}
```

空循环应该使用{}或者continue

```
while (condition) continue;	//good
for (int i=0;i<n;++i) {} 	//good
while (condition) ;	//bad
```

逻辑运算符位置要统一，前或者后

```
if (one > two &&
    three > four &&
    five > six) {
        
}
```

### 3.4预处理

预处理指令不要缩进，即使位于缩进代码块中

```
if (condition) {
#if DISASTER_PENDING
    doSomething();
#endif
}
```

### 3.5类格式

依次声明public/protectd/private,缩进一格(非强制)

```
class MyClass {
 public:
  MyClass();
  ~MyClass() {}
 private:
  int ages;
  string name;
}
```

### 3.6初始化列表

方式同函数参数列表，不能在同一行则如下：

```
MyClass::MyClass(int var)
   : some_var_(var),	//4 space
     some_other_var_(var+1){
  doSomething();    
}
```

### 3.7命名空间

无需额外缩进

```
namespace {
void do(){
    
}
}
```

## 4.注释

### 4.1文件注释

版权信息：Copyright 2008 Google Inc. ;

许可版本（license boilerplate）Apache 2.0 BSD LGPL GPL

作者

文件内容	.h对类的功能和用法作简单说明，.cpp对细节和算法讨论

### 4.2类注释

每个类需要附着描述类的功能和用法的注释

### 4.3TODO注释

对于那些临时的，短期的解决方案，或者还不够完美的代码使用TODO注释

```
//TODO(kl@emil.com) : usa a ...
```

## 5.编程约定

### 5.1预处理

1.用#include “ ”包含用户自己定义的头文件，用#include<  >包含外部文件

绝大多数编译器遇到引号式的包含时，会首先在当前目录下进行搜索

```
#include <vector>
#include “MyClass.h”
```

2.为了防止头文件被重复包含，使用define来进行编译条件设置。例如项目foo中头文件foo/bar/bar.h，则应该如下保护。（每个头文件都需要）

```
#ifndef FOO_BAR_BAR_H_
#define FOO_BAR_BAR_H_

	//your code

#endif // FOO_BAR_BAR_H_
```

对于支持pragma once的编译器来说还可以使用:

```
#pragma once
```

3.对于路径为project/src/base/logging.h应该按如下被包含：

```
#include "base/logging.h"
```

包含的顺序如下：C库/C++库/其他库头文件/项目内的头文件

4.用#if   #endif和#ifdef  #endif隐藏不推荐的，未完成的，临时的，用于测试的和废弃的代码

```
class MyClass{
    public:
#ifdef TEST
      void metheod(void);
#endif
	  void method(size_t start, size_t end);
}
```

5.使用static const替代#define定义常量

```
static const double PI=3.1415926；	//good
#define PI 3.1415926；	//bad
```

6.减少#include在头文件中的使用

如果头文件没有用到外部类成员，那么就无需引入头文件，而是作前向声明

在实现的cpp文件中再#include头文件

### 5.2声明

1.使用typedef简化复杂类型的表达式

2.用零值枚举表示未初始化，无效，不确定或者默认状态

```
enum Color {
    NONE,
    RED,
    GREEN,
    BLUE=NONE
}
```

### 5.3作用域

1.如果全局变量或常量与某个类关系近，可以将其声明为该类的静态成员

2.循环变量应该声明在for循环之内

```
for (int i=0; i<10; ++i){
    
}
```

3.在循环体中，如果使用了类对象，则需要在循环体外声明，防止多次构造和析构

```
MyClass my_class;
for (int i=0; i<10; ++i){
    
}
```

### 5.4函数和方法

1.使用枚举代替bool提高代码可读性

```
enum duration{
    DELETE_AFTER_CALL,
    KEEP_AFTER_CALL
}
```

2.非常量的引用暗示可能修改对象，但不能说明函数是否会保存该引用。使用指针则暗示会保存

```
ListElement(ListElement &prev, ListElement &next);

ListElement(ListElement *prev, ListElement *next);
```

3.用引用传递对象，用值传递基本类型和指针

用值传递基本类型和指针效率更高，如果引用传递对象无需在函数中修改，可声明时添加const保护

4.用const char*定义窄字符串参数

5.传递枚举值，而不是整型常量

### 5.5类

1.应显式声明默认构造函数，若支持实例化，总应该声明拷贝构造函数，赋值构造函数，析构函数

2.可派生子类的类，总应该实现虚析构函数

```
class base {
    public:
    	base(void);
    	virtual ~base();
}
```

3.使用默认参数减少函数的数量

```
class Brush {
    public:
    	Brush(void);
    	Brush(Color c);
    	Brush(Color c,Texture t);	//bad
}


class Brush {
    public:
    	Brush(Color c=Color.BLACK,Texture t=Texture.Soild);	//good
}
```

4.在类中使用对象指针和引用

使用前向声明，可以消除循环依赖，减少编译器需要处理的头文件

一种不好的做法是：

```
//Foo.h

#include "Bar.h"

class Foo {
    public:
      Foo(Bar b);	//需要Bar完整声明
    private:
      Bar b_;	//需要Bar完整声明
}
```

比较好的做法是：

```
//Foo.h

class B；	//使用前向声明代替#include

class Foo {
    public:
      Foo(const Bar &b);	//前向声明可满足要求
    private:
      Bar *b_;	//前向声明可满足要求
}

在源代码中再引入完整的声明
//Foo.cpp
#include "Foo.h"
#include "Bar.h"
```

### 5.6初始化

1.C++编译器根据成员变量的声明顺序初始化，所以尽量按照声明顺序进行初始化

### 5.7语句和表达式

1.复杂逻辑表达式尽量使用括号不要使用优先级

2.在控制流语句中使用块语句

3.不要与true/false比较相等性

```
if (i == true) {}	//bad
if (i != false) {} 	//bad

if (i) {}	//good
if ( i != 0) {}	//best
```

4.使用size_t充当循环变量和数组下标

