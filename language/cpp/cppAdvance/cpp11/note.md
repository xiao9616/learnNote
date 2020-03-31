## **C++11/14新特性** ##

[参考来源 https://blog.csdn.net/jiange_zh/article/details/79356417](https://blog.csdn.net/jiange_zh/article/details/79356417)

### **1.nullptr**

 nullptr 出现的目的是为了替代 NULL,传统 C++ 会把 NULL、0 视为同一种东西。nullptr 关键字，专门用来区分空指针、0。nullptr的类型为nullptr_t。

### **2.auto**

auto 和 decltype 这两个关键字实现了类型推导，让编译器来操心变量的类型。
- auto 不能用于函数传参，考虑重载的问题，我们应该使用模板。
- auto 不能用于推导数组类型

### **3. decltype**

声明返回类型

    template<typename T1,typename T2>
    auto add(T1 x,T2 y) ->decltype(x+y);

编译器分析表达式并得到它的类型，却不实际计算表达式的值。

    auto x = 1;
    auto y = 2;
    decltype(x+y) z;

### **4.foreach**

原来的for循环

    std::vector<int> arr(5, 100);
    for(std::vector<int>::iterator i = arr.begin(); i != arr.end(); ++i)
    {
                 std::cout << *i << std::endl;
    }
现在

    for(auto &i:arr)
    {
        std::cout << i << std::endl;
    }
### **5.初始化列表**

    struct A
    {
         int a;
         float b;
    };
    A a {1,1.0}；
    A b{};  //初始化为0，指针初始化为nullptr

initializer_list

    #include <initializer_list>
    class Magic {
    public:
        Magic(std::initializer_list<int> list) {
            for(auto &i:list){
    
            }
        }
    };
    
    Magic magic = {1,2,3,4,5};
    std::vector<int> v = {1, 2, 3, 4};
    max({1,2,3,4});
### **6.模板**

可变参数的模板

    void print()
    {
    
    }
    
    template<typename T,typename... Types>
    void print(const T&  firstArgs,const Types&... args){
        cout<<firstArgs<<endk;
        print(args...);
    }

类型别名模板

    template< typename T, typename U, int value>
    class SuckType {
    public:
        T a;
        U b;
        SuckType():a(value),b(value){}
    };
    
    template <typename T>
    using NewType = SuckType<int, T, 1>;    // 合法

默认模板参数

    template<typename T = int, typename U = int>
    auto add(T x, U y) -> decltype(x+y) {
        return x+y;
    }

### **7.构造函数**

**委托构造**

使得构造函数可以在同一个类中一个构造函数调用另一个构造函数，从而达到简化代码的目的

    class Base {
    public:
        int value1;
        int value2;
        Base() {
            value1 = 1;
        }
        Base(int value) : Base() {  // 委托 Base() 构造函数
            value2 = 2;
        }
    };

**继承构造**

有如下父类

    class A
    {
        A(int i) {}
        A(double d,int i){}
        A(float f,int i,const char* c){}
        //...等等系列的构造函数版本
    }

原来子类继承父类，需要显式的调用父类构造函数，如下：

    class  B:A
    {
        B(int i):A(i){}
        B(double d,int i):A(d,i){}
        B(folat f,int i,const char* c):A(f,i,e){}
        //......等等好多个和基类构造函数对应的构造函数
    }
现在可以这样：

    class  B:A
    {
        using A::A;
        //关于基类各构造函数的继承一句话搞定
    }

### **8.Lambda**
Lambda 表达式，实际上就是提供了一个类似匿名函数的特性，而匿名函数则是在需要一个函数，但是又不想费力去命名一个函数的情况下去使用的。

Lambda 表达式的基本语法如下：

    [ caputrue ] ( params ) opt -> ret { body; };
    
    1) capture是捕获列表； 
    2) params是参数表；(选填) 
    3) opt是函数选项；可以填mutable,exception,attribute（选填） 
    mutable说明lambda表达式体内的代码可以修改被捕获的变量，并且可以访问被捕获的对象的non-const方法。 
    exception说明lambda表达式是否抛出异常以及何种异常。 
    attribute用来声明属性。 
    4) ret是返回值类型（拖尾返回类型）。(选填) 
    5) body是函数体。

- 捕获列表：lambda表达式的捕获列表精细控制了lambda表达式能够访问的外部变量，以及如何访问这些变量。

    1) []不捕获任何变量。 
    2) [&]捕获外部作用域中所有变量，并作为引用在函数体中使用（按引用捕获）。 
    3) [=]捕获外部作用域中所有变量，并作为副本在函数体中使用(按值捕获)。注意值捕获的前提是变量可以拷贝，且被捕获的变量在 lambda 表达式被创建时拷贝，而非调用时才拷贝。如果希望lambda表达式在调用时能即时访问外部变量，我们应当使用引用方式捕获。
    4) [=,&foo]按值捕获外部作用域中所有变量，并按引用捕获foo变量。 
    5) [bar]按值捕获bar变量，同时不捕获其他变量。 
    6) [this]捕获当前类中的this指针，让lambda表达式拥有和当前类成员函数同样的访问权限。如果已经使用了&或者=，就默认添加此选项。捕获this的目的是可以在lamda中使用当前类的成员函数和成员变量。

### **9.容器**

- array

std::array 保存在栈内存中，相比堆内存中的 std::vector，我们能够灵活的访问这里面的元素，从而获得更高的性能。编译时创建一个固定大小的数组，std::array 不能够被隐式的转换成指针，使用 std::array只需指定其类型和大小即可,但是必须用常量表达式来指明大小.

    std::array<int, 4> arr= {1,2,3,4};
    int len = 4;
    std::array<int, len> arr = {1,2,3,4}; // 非法, 数组大小参数必须是常量表达式

- forward_list

std::forward_list 是一个列表容器，使用方法和 std::list 基本类似。 
和 std::list 的双向链表的实现不同，std::forward_list 使用单向链表进行实现，提供了 O(1) 复杂度的元素插入，不支持快速随机访问（这也是链表的特点），也是标准库容器中唯一一个不提供 size() 方法的容器。**当不需要双向迭代时，具有比 std::list 更高的空间利用率。**

- 无序容器

     std::unordered_map/std::unordered_multimap 和 std::unordered_set/std::unordered_multiset。

    无序容器中的元素是不进行排序的，内部通过 Hash 表实现，插入和搜索元素的平均复杂度为 O(constant)。

- tuple

std::make_tuple: 构造元组

    auto student=std::make_tuple(3.8, 'A', "张三");

std::tie: 元组拆包

    std::tie(gpa, grade, name) = student;

std::get: 获得元组某个位置的值 
    
    auto gpa=std::get<0>(student);

### **10.拷贝构造和转移构造**

    string a(x);                                         // line 1
    string b(x + y);                                    // line 2
    string c(some_function_returning_a_string());       // line 3

第一行(line 1)的x是一个左值(lvalues）使用深度拷贝构造函数，如下：

    string(const string& that)
    {
        size_t size = strlen(that.data) + 1;
        data = new char[size];
        memcpy(data, that.data, size);
    }

第二三行的参数是个右值，使用转移构造函数，如下：

    string(string&& that)   // string&& is an rvalue reference to a string
    {
    data = that.data;
    that.data = 0;
    }

由于没有深度拷贝堆内存中的数据，而是仅仅复制了指针，并把源对象的指针置空。事实上，我们“偷取”了属于源对象的内存数据。由于源对象是一个右值，不会再被使用，因此客户并不会觉察到源对象被改变了。在这里，我们并没有真正的复制，所以我们把这个构造函数叫做“转移构造函数”（move constructor），他的工作就是把资源从一个对象转移到另一个对象，而不是复制他们。**编译器会依据参数是左值还是右值在复制构造函数和转移构造函数间进行选择。**

**拷贝构造函数执行的是深度拷贝，因为源对象本身必须不能被改变。而转移构造函数却可以复制指针，把源对象的指针置空，这种形式下，这是安全的，因为用户不可能再使用这个对象了。**

### **11.move转移左值**

标准库的头文件< utility >中提供了一个模板函数std::move。实际上，**std::move仅仅是简单地将左值转换为右值，它本身并没有转移任何东西。它仅仅是让对象可以转移。**

unique_ptr只有转移构造函数，如下：

    unique_ptr(unique_ptr&& source)   // note the rvalue reference
    {
        ptr = source.ptr;
        source.ptr = nullptr;
    }

对unique_ptr对象进行赋值：

    unique_ptr<Shape> a(new Triangle);
    unique_ptr<Shape> b(a);              // still an error
    unique_ptr<Shape> c(std::move(a));   // okay

第二行不能编译通过，因为a是左值，但是参数unique_ptr&& source只能接受右值。第三行编译没有问题，第三行之后，a不再拥有对象，通过move将a变为一个右值。

### **12.explicit**

构造器前面加上explicit修饰， 指定这个构造器只能被明确的调用/使用， 不能作为类型转换操作符被隐含的使用。**普通构造函数能够被隐式调用。而explicit构造函数只能被显式调用。**

### **13.=default / =delete**
C++ 的类有四类特殊成员函数，它们分别是：默认构造函数、析构函数、拷贝构造函数以及拷贝赋值运算符。

- 将该函数声明为 "=default"函数，编译器将为显式声明的 "=default"函数自动生成函数体。
- 在函数声明后上“=delete;”，就可将该函数禁用。

### **14.using**

- 命名空间 

        using namespace std;
- 声明

        using _basic::_M_allocate;

- 模板

        template<typename T>
        using mystring=basic_string<T,char_traits<T>>;

- 函数指针

        using func=void(*)(int,int);

### **15.noexcept**

条件为真时不抛出异常

    void foo() noexcept(true){
    
    }

### **16.override**

    class base{
        virtual void func(float){
    
        }
    }
    
    class Devied:Base{
        virtual void func(float) override{
            //显示的声明为重写函数
        }
    }

### **17.final**

作用与类上，表示类不可被继承

    class Base final{
    
    }
作用与虚函数上，表示该虚函数不可被重写

    class Base{
        virtual void f() final;
    }

### 18.智能指针

C++11引入智能指针，从此不用再需要手动释放内存。智能指针其实就是对普通指针的封装（即封装成一个类），通过重载 * 和 ->两个运算符，使得智能指针表现的就像普通指针一样。shared_ptr/unique_ptr/weak_ptr

**unique_ptr**

独占指针，不可进行拷贝或者赋值操作给其他智能指针，可以使用move转移所有权

```C++
unique_ptr<Monster> monster1(new Monster());	//monster1 指向 一个怪物 　　
unique_ptr<Monster> monster2 = monster1;		//Error!编译期出错，不允许复制指针指向同一个资源。
unique_ptr<Monster> monster3 = move(monster1);	//转移所有权给monster3. 　　
monster1->doSomething();					//Oops!monster1指向nullptr，运行期崩溃
```

**shared_ptr**

多个shared_ptr指向同一处资源，当所有shared_ptr都全部释放时，该处资源才释放。可以拷贝和赋值操作。

```
{
    shared_ptr<Monster> monster1(new Monster());　　　//计数加到1
	do{std::shared_ptr<Monster> monster2 = monster1;　　　　//计数加到2
	}while(0);　　　　　　　　　　
　　//该栈退出后，计数减为1，monster1指向的堆对象仍存在
	shared_ptr<Monster> monster3 = monster1;　//计数加到2
	shared_ptr<Monster> monster4 = monster1;　//计数加到3
}
//该栈退出后，shared_ptr都释放了，计数减为0，它们指向的堆对象也能跟着释放.
```

**weak_ptr**

是为了辅助shared_ptr的存在，它只提供了对管理对象的一个访问手段，同时也可以实时动态地知道指向的对象是否存活。要创建弱指针，必须是已经拥有资源但是是一个共享指针。weak_ptr只能用于跟踪一个共享的资源，但并不实际拥有，也不会阻碍资源的释放。读取共享资源前需要先执行lock，得到shared_ptr后才能进行访问。

```
shared_ptr<Monster> monster1(new Monster());
weak_ptr<Monster> r_monster1 = monster1;
r_monster1->doSomething();	//Error! 编译器出错！weak_ptr没有重载* 和 -> ，无法直接当指针用
shared_ptr<Monster> s_monster1 = r_monster1.lock();//OK!可以通过weak_ptr的lock方法获得shared_ptr。
```

### 19.cast类型转换

**static_cast**

内置基本数据类型之间的相互转换，enum、struct、 int、char、float等,涉及到类的话，static_cast只能在有相互联系的类型中进行相互转换,不一定包含虚函数。

```
int c=static_cast<int>(7.987);

class A
{};
class B:public A
{};
class C
{};
 
int main()
{
    A* a=new A;
    B* b;
    C* c;
    b=static_cast<B>(a);  // 编译不会报错, B类继承A类
    c=static_cast<B>(a);  // 编译报错, C类与A类没有任何关系
    return 1;
}
```

**const_cast**

仅仅把一个它作用的表达式转换成常量。它可以使一个本来不是const类型的数据转换成const类型的，或者把const属性去掉。

```
  int a = 10;
  const int *p = &a;    // 被const修饰，不能使用该指针修改其指向内容的值  
  int *q;
  q = const_cast<int *>(p);     // 去除p的常量性给q,如果不去除直接赋值会报错 
  *q = 20; 
```

**reinterpret_cast**

强制类型转换是一种非常强的强制类型转换，它可以将任意两个无关的指针或引用进行转换

**dynamic_cast**

static_cast会在编译的过程中进行安全性检查，而dynamic_cast会在运行的过程中进行安全性检查。这两个都带安全性检查可以防止错误的类型转换导致程序跑偏。



**总结**
static_cast会进行静态的安全性检查，一般用于内置数据类型的转换和通常的类之间的转换。
const_cast主要是用来去掉指针和引用的const和volatile类型。
reinterpret_cast用于完全没有关系指针或引用之间的转换，比如字符指针转整形指针。
dynamic_cast通常用于基类和派生类之间的相互转换。