# 面试知识整理

## 1.编程语言

### 1.1 C++

#### bool

```c++
C++中的新类型(0为false,1为true)
占用字节数(bool:1字节 BOOL:4字节)
```

#### const

```c++
const char* p  char const* p ;	// 表示指针所指向的内存区域不可变
char* const  p ; //表示指针不可变,指针不能指向其他地方
const char* const  p ; 表示两者都不可以修改

const int n=5;
int* p = const_cast<int*>(&n); // 将const int* 类型转换成int*
```

#### inline

当函数比较短,调用函数需要出栈入栈,使用内联可以在预处理阶段直接替换,可以节省调用时间和内存空间

#### 引用

1.引用在定义时必须初始化,引用一旦确定就无法修改

2.只有常量引用可以使用常量来初始化

引用(左值)

```c++
int n = 5;
int& reN = n;
reN = 6; //n的值也是6,引用可以理解为变量的别名
```

常量引用

```c++
const int& reN = 12;	//可以通过
```

引用作为函数返回值

```c++
int& func(){
	int k = 3;
	return k;
}

int main(){
	int& m=func();
	m=4;	// k=4
}
```

交换两个指针

```c++
void pointChanege(int* & n1,int* & n2){
	int* k = n1;
	n1 = n2;
	n2 = k;
	return;
}

int main(){
	int n = 5;
	int m = 6;
	int* p1 = &n;
	int* p2 = &m;
	pointChange(p1,p2);
}

// 或者使用二级指针
void pointChanege(int** n1,int** n2){
	int* k = n1;
	n1 = n2;
	n2 = k;
	return;
}
```

引用的本质

编译器产生的关联了对应的存储器地址常量指针(指针不可重新指向)

#### 作用域

1.全局作用域 namespace

2.局部作用域 块作用域(由内向外,找最近的)

3.类作用域

#### 命名空间

1.一种作用域的划分,通常作为区分项目中模块或组件

2.namespace可以拆分,可以嵌套,可以取别名

```c++
namespace xiao{
	int age = 26;
}

namespace xiao{
  int length = 12;
  namespace xuan {
    int width = 34;
  }
}

namespace n = xiao::xuan;

int main(){
	xiao::age = 27;
  xiao::xuan::width = 23;
  n::width = 27;
}
```

3.::前面不加命名空间,表示使用全局变量

```c++
int width = 5;
namespace xiao{
	::width = 6;
	width = 7;
}
```

原理

还是编译器进行了处理,和函数名重载一样

```c++
int xiao::age = 27;	//在编译器处理完成后变量名变为 @age@xiao?3HA
```

#### 调用约定



#### explicit delete default

在类的构造函数前面添加该关键字,表示不能使用隐式转换

delete用来将这个构造函数删除

```c++
class Student{
	Student() = delete;
}
```

default表示该构造函数为默认

#### 虚函数原理

本质上是对象包含了一个指向函数的地址指针

### 1.2 python













