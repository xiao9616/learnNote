# More effective C++

### 1.指针和引用

1.1 指针和引用都是让你间接引用其他对象。由于不能使用指向空值的引用，所以当你用一个变量指向一个对象，但是该变量有时不会指向任何对象（空），这时应该把该变量声明为指针，反之应该使用引用。

```
string &rc;	//error

string s("zyx");
string &rs=s;	//good

string *ps；	//未初始化，合法但是危险
```

1.2 不存在空值引用意味着引用的代码效率更高，不需要检查合法性

```
void printDouble(const double &rd)
{
    cout<<rd;	// rd肯定指向一个double值
}


void printDouble(const double *rd)
{
	if(rd){
        cout<<*rd;	// rd需要检查是否为NULL
	}
    
}
```

1.3 指针可以被重新赋值，引用总是在初始化时被指定对象，不能改变

```
string s1("Nancy");
string s2("Xiao")；
string &rs=s1;
string *ps=&s1;

rs=s2;	//rs依旧引用s1，只是时s1的值变为Xiao
ps=&s2;	//ps指向s2，s1没有改变；
```

1.4 重载某个 操作符，应该使用引用。

```
vector<int> v(10);
v[5]=10;	//操作符[]返回引用

//如果[]返回一个指针，则应该这么写
*v[5] =10 ; //这样看上去是个向量指针，容易歧义，所以最好不要这样
```

在以下情况下你应该使用指针,一是你考虑到存在不指向任何对象的可能(在这种情况下,你能够设置指针为空),二是你需要能够在不同的时刻指向不同的对象(在这种情况下,你能改变指针的指向)。如果总是指向一个对象并且一旦指向一个对象后就不会改变指向,或者重载操作符时那么你应该使用引用。

### 2.尽量使用C++风格的类型转换

原来的类型转换（type）expression

```
（double）IntNums；
```

现在你应该这样写cast <type> (expression)

```
static_cast<double> IntNums;
```

2.1 static_cast

和C风格的类型转换一样，含义也一样。

```
int firstNumber,secondNumber;
double result=((double)firstNUmber)/secondNumber;	//C风格

double result=static_cast<double>(firstNumber)/secondNumber;	//C++风格
```

2.2 const_cast

const_cast用来转换const，volatile属性

```
//有如下定义
class Widget {};
class SpecialWidget:public Widget {};
void update(SpecialWidget *psw);

SpecialWidget sw;
const SpecialWidget &csw=sw;	//const引用

update(const_cast<SpecialWidget *>(&csw));	//正确 C++style
update((SpecialWidget *)&csw);	//正确 C style
update(& csw);	//错误，update不接受const变量
```

2.3 dynamic_cast

dynamic_cast把指向基类的指针或引用转换成指向派生类或其兄弟类型的指针或引用

```
Widget *pw;
void update(SpecialWidget *psw);
void updateViaRef(SpecialWidget &rsw)；

update(dynamic_cast<SpecialWidget *>(pw));
updateViaRef(dynamic_cast<SpecialWidget &>(*pw));
```

2.4 reinterpret_cast

reinterpret_cast最普遍的用途是在函数指针类型之间进行转换。

```
typedef void (*FuncPtr)();	//FuncPtr是一个指向函数的指针

FuncPtr funcPtrArray[10];	//funcPtrArray是个能容纳10个FuncPtr指针的数组

int doSomething();	//返回值为int的函数

funcPtrArray[0]=&doSomething；	//error
funcPtrArray[0]=reinterpret_cast<FuncPtr>(&doSomething);
```

### 3.不要对数组使用多态

类继承的最重要的特性是你可以通过基类指针或引用来操作派生类。这样的指针或引用
具有行为的多态性,就好像它们同时具有多种形态。

C++允许你通过基类指针和引用来操作派生类数组。不过这根本就不是一个特性,因为这样的代码几乎从不如你所愿地那样运行。

```
class BST { ... };
class BalancedBST: public BST { ... };

void printBSTArray(ostream& s,const BST array[],int numElements)
{
	for (int i = 0; i < numElements; ) {
			s << array[i];
	}
}

BST BSTArray[10];
printBSTArray(cout, BSTArray, 10);	// 运行正常

BalancedBST bBSTArray[10];
printBSTArray(cout, bBSTArray, 10);	// 可以正常编译，但是数值跳跃间隔还是sizeof(BST),不是BanlancedBST
```

### 4.避免无用的缺省构造函数

对于很多对象来说,不利用外部数据进行完全的初始化是不合理的。比如一个没有输入姓名的地址簿对象,就没有任何意义。在一些公司里,所有的设备都必须标有一个公司 ID 号码,所以在建立对象以模型化一个设备时,不提供一个合适的 ID 号码,所建立的对象就根本没有意义。

对于如下类：

```
class EquipmentPiece {
 public:
  EquipmentPiece(int IDNumber);
};
```

没有缺省构造函数，三种情况下会出现问题：

4.1 建立数组会出现问题

```
EquipmentPiece bestPieces[10];	//error 没有缺省构造函数
EquipmentPiece *bestPieces=new EquipmentPiece[10];	//error 没有缺省构造函数

1.定义时初始化
int ID1，ID2 ... ID10;
EquipmentPiece bestPieces[]={	//ok
    EquipmentPiece(ID1),
    .
    .
    EquipmentPiece(ID10)
}

2.使用指针数组
typedef EquipmentPiece* PEP；
PEP bestPieces[10];
for (int i = 0; i < 10; ++i)
	bestPieces[i] = new EquipmentPiece( ID Number );	//ok
```

4.2使用模板类会出现问题，因为实例化一个模板，模板类型应该提供一个默认构造函数。

```
//array类
template<class T>
class Array {
    public:
    Array(int size);
    ...
    private:
    T *data;
};
template<class T>
Array<T>::Array(int size)
{
    data = new T[size]; // 为每个数组元素依次调用 T::T()，需要T类型有缺省构造函数
}
```

4.3虚基类是否需要

派生类在实例化时都必须给虚基类构造函数提供参数。这就要求所有由没有缺省构造函数的虚基类继承下来的派生类(无论有多远)都必须知道并理解提供给虚基类构造函数的参数的含义。

```
class EquipmentPiece {
    public:
    EquipmentPiece( int IDNumber = UNSPECIFIED);

    private:
    static const int UNSPECIFIED;
};

这允许这样建立 EquipmentPiece 对象
EquipmentPiece e; 	//这样合法
```

这样的修改使得其他成员函数变得复杂,因为不再能确保 EquipmentPiece 对象进行了有意义的初始化。

### 5.类型转换函数

C++编译器能够在两种数据类型之间进行隐式转换，允许把 char 隐式转换为 int 和从short 隐式转换为 double，这种可怕的转换可能会导致数据的丢失。

你自己可以定义转换构造函数进行这些转换：单参数构造函数和显式类型转换函数

5.1单参数构造函数

```
class Name {
    // for names of things
    public:
    Name(const string& s);	// 转换 string 到Name
};
```

5.2显式类型转换函数

```
class Rational {
    // 有理数类
    public:
        Rational(int numerator = 0,
        int denominator = 1);// 转换 int 到有理数类
        double asDouble() const;
};

Rational r(1,2);
cout<<r.adDouble();
```

为了解决隐式类型转换，加入了关键字explicit

```
template<class T>
class Array {
    public:
      explicit Array(int size);	//explicit 使得编译器会拒绝为了隐式类型转换而调用构造函数
};
```

### 6.自增，自减的前缀和后缀

重载++，--，为了区分前后缀差异，规定后缀形式有一个 int 类型参数,当函数被调用时,编译器传递一个 0 做为 int 参数的值给该函数。

```
class UpInt{
    public:
    	UpInt &operator++();	//前缀
    	const UpInt operator++(int);后缀
    	UpInt &operator+=(int);	
}

UpInt &UpInt::operator++()
{
    *this+=1;
    return *this;
}


const UpInt UpInt::operator++(int)
{
    UpInt oldValue=*this;
    ++(*this);
    return oldValue;
}
```

### 7.尽量不要重载&&，||，‘，’

C++使用布尔表达式短路求值法，一旦确定了布尔表达式的真假值,即使还有部分表达式没有被测试,布尔表达式也停止运算。

如果重载了&&，||的话，不能保证还能满足短路求值法，使得使用它的程序员会困惑。

### 8.new/delete的不同含义

new操作符，这个操作符就象 sizeof 一样是语言内置的,你不能改变它的含义,它的功能总是一样的。它要完成的功能分成两部分。第一部分是分配足够的内存以便容纳所需类型的对象。第二部分是它调用构造函数初始化内存中的对象。

```
string *ps=new string("Memory Management");
```

new操作，new 操作符调用一个函数来完成必需的内存分配,你能够重写或重载这个函数来改变它的行为。new 操作符为分配内存所调用函数的名字是 operator new。通常如下声明：

```
void *operator new(size_t size);
```

new 操作符实际进行了如下的过程：

```
void *memory=operator new(sizeof(string));
call string("Memory Management") on memory;
string *ps=static_cast<string *>(memory);
```

### 9.利用析构函数防止资源泄露

```
while (dataSource) {
    ALA *pa = readALA(dataSource);
    pa->processAdoption(); //处理收容动物
    delete pa; //删除 readALA 返回的对象
}
```

上述代码如果载pa->processAdoption()中发生异常，则pa占用资源就不会被释放，造成内存泄露

使用智能指针可以解决这个问题，使用一个对象代替指针。

```
template<class T>
class auto_ptr {
    public:
        auto_ptr(T *p = 0): ptr(p) {} // 保存 ptr,指向对象
        ~auto_ptr() { delete ptr; } // 删除 ptr 指向的对象
    private:
        T *ptr;
};
```

用 auto_ptr 对象代替 raw 指针,你将不再为堆对象不能被删除而担心,即使在抛出异常时,对象也能被及时删除。

```
while (dataSource) {
    auto_ptr<ALA> pa(readALA(dataSource));
    pa->processAdoption();
}
```

pa 被声明为一个 auto_ptr<ALA>对象,而不是一个指针,所以会被当作局部变量被释放，自动调动析构函数。而他的行为却和指针一样。

auto_ptr 后的思想是:用一个对象存储需要被自动释放的资源,然后依靠对象的析构函数来释放资源,这种思想不只是可以运用在指针上,还能用在其它资源的分配和释放上。

### 10.在构造函数中防止资源泄露

考虑如下的构造函数：

```
//声明
BookEntry(const string& name,
		  const string& address = "",
          const string& imageFileName = "",
          const string& audioClipFileName = "");
//定义
BookEntry::BookEntry(const string& name,
                     const string& address,
                     const string& imageFileName,
                     Const string& audioClipFileName)
: theName(name), theAddress(address),
theImage(0), theAudioClip(0)
{
    if (imageFileName != "") {
        theImage = new Image(imageFileName);
    }
    if (audioClipFileName != "") {
        theAudioClip = new AudioClip(audioClipFileName);
    }
}

BookEntry::~BookEntry()
{
    delete theImage;
    delete theAudioClip;
}
```

如果AudioClip 的构造函数自己抛出一个异常，那么谁来负责删除 theImage 已经指向的对象?

```
BookEntry *pb = 0;
try {
    pb = new BookEntry("Addison-Wesley Publishing Company",
    "One Jacob Way, Reading, MA 01867");
    ...
    }
catch (...) {
    // 捕获所有异常
    delete pb; // 删除 pb,当抛出异常时
    throw; // 传递异常给调用者
    }
delete pb;
```

你会发现在 BookEntry 构造函数里为 Image 分配的内存仍旧被丢失了,这是因为如果new 操作没有成功完成,程序不会对 pb 进行赋值操作。

```
try {
    if (imageFileName != "") {
        theImage = new Image(imageFileName);
    }
    if (audioClipFileName != "") {
        theAudioClip = new AudioClip(audioClipFileName);
    }
}
catch (...) {
    delete theImage;
    // 捕获所有异常
    // 完成必要的清除代码
    delete theAudioClip;
    throw;
}
```

修改构造函数如上，但这样做不太完美。

如果theImage 和 theAudioClip 是常量(constant)指针类型，必须通过 BookEntry 构造函数的成员初始化表来初始化这样的指针。

```
Image * const theImage; // 指针现在是
AudioClip * const theAudioClip; // const 类型
```

通常需要这样初始化

```
BookEntry::BookEntry(const string& name,
                     const string& address,
                     const string& imageFileName,
                     const string& audioClipFileName)
: theName(name), theAddress(address),
  theImage(imageFileName != "" ? new Image(imageFileName): 0),
  theAudioClip(audioClipFileName != "" ? new AudioClip(audioClipFileName): 0)
{}
```

这样做导致我们原先一直想避免的问题重新出现:如果 theAudioClip 初始化时一个异常被抛出,theImage 所指的对象不会被释放。

可以考虑用函数返回指针指向初始化过的 theImage 和 theAudioClip 对象。

```
BookEntry::BookEntry(const string& name,
                     const string& address,
                     const string& imageFileName,
                     const string& audioClipFileName)
: theName(name), theAddress(address),
  theImage(initImage(imageFileName)),
  theAudioClip(initAudioClip(audioClipFileName))
{}

Image * BookEntry::initImage(const string& imageFileName)
{
    if (imageFileName != "") return new Image(imageFileName);
    // theAudioClip 被第二个初始化, 所以如果在 theAudioClip
	// 初始化过程中抛出异常,它必须确保 theImage 的资源被释放。
    else return 0;
}

AudioClip * BookEntry::initAudioClip(const string&audioClipFileName)
{
    try {
        if (audioClipFileName != "") {
        return new AudioClip(audioClipFileName);
        }
        else return 0;
    }
    catch (...)
    {
        delete theImage;
        throw;
    }
}
```

现在这个思想很类似与智能指针，但是这样代码难以管理

```
const auto_ptr<Image> theImage;			// 它们现在是
const auto_ptr<AudioClip> theAudioClip; // auto_ptr 对象

BookEntry::BookEntry(const string& name,
                     const string& address,
                     const string& imageFileName,
                     const string& audioClipFileName): theName(name), theAddress(address),
theImage(imageFileName != "" ? new Image(imageFileName): 0),
theAudioClip(audioClipFileName != "" ? new AudioClip(audioClipFileName): 0)
{}
```

用对应的 auto_ptr 对象替代指针成员变量,就可以防止构造函数在存在异常时发生资源泄漏,你也不用手工在析构函数中释放资源。

在对象构造中,处理各种抛出异常的可能,是一个棘手的问题,但是 auto_ptr(或者类似于 auto_ptr 的类)能化繁为简。它不仅把令人不好理解的代码隐藏起来,而且使得程序在面对异常的情况下也能保持正常运行。

### 11.禁止将异常传递到析构函数之外

如果析构函数本身的调用就是源自于某些其它异常的抛出,那么 terminate 函数将被自动调用,彻底终止你的程序。

对于析构函数可能发生异常的情况，应该在可能发生异常的地方使用try-catch

```
Session::~Session()
{
    try {
        logDestruction(this);
    }
    catch (...) { }
}
```

catch 表面上好像没有做事情 , 这是一个假象 , 实际上它阻止了任何从logDestruction 抛出的异常被传递到析构函数的外面。

不允许异常传递到析构函数外面还有第二个原因。如果一个异常被析构函数抛出而没有在函数内部捕获住,那么析构函数就不会完全运行。

### 12.catch的参数是拷贝过来的

1.参数是拷贝过来的

```
//class Widget {}

void passThorwWidget()
{
    Widget localWidget;
    throw localWidget;
}

catch (Width &w)
catch (Width *w)
catch (Width w)
```

不论通过传值捕获异常还是通过引用捕获(不能通过指针捕获这个异常,因为类型不匹配)都将进行 lcalWidget 的拷贝操作,也就说传递到 catch子句中的是 localWidget 的拷贝。必须这么做,因为当 localWidget 离开了生存空间后,其析构函数将被调用。如果把 localWidget 本身(而不是它的拷贝)传递给 catch 子句,这个子句接收到的只是一个被析构了的 Widget,一个 Widget 的“尸体”。这是无法使用的。

2.异常对象被拷贝是其静态类型

```
void passAndThrowWidget()
{
    SpecialWidget localSpecialWidget;

    Widget& rw = localSpecialWidget;	// rw 引用 SpecialWidget
    throw rw;	//它抛出一个类型为 Widget的异常
}
```

3.

```
catch (Widget& w)	// 捕获 Widget 异常
{
    ... // 处理异常
    throw; // 重新抛出异常,让它继续传递
} 
catch (Widget& w) // 捕获 Widget 异常
{
    ... // 处理异常
    throw w; // 传递被捕获异常的拷贝
}
```

4.一般来说,catch 子句匹配异常类型时不会进行隐式转换。

```
try {
    int	value；
    if (someFunction()) {
    throw value;	// 如果 someFunction()返回真,抛出一个整形值
}
}
catch (double d) {	// 只处理 double 类型的异常
...
}
```

不过在 catch 子句中进行异常匹配时可以进行两种类型转换。第一种是继承类与基类间的转换。一个用来捕获基类的 catch 子句也可以处理派生类类型的异常。

第二种是允许从一个类型化指针(typed pointer)转变成无类型指针(untyped pointer),所以带有 const void* 指针的 catch 子句能捕获任何类型的指针类型异常:

```
catch (const void*) 			//捕获任何指针类型异常
```

5.catch 子句匹配顺序总是取决于它们在程序中出现的顺序，一个派生类异常可能被处理其基类异常的 catch 子句捕获。

```
try {
...
}

catch (logic_error& ex) {
   // 这个 catch 块 将捕获所有的 logic_error异常, 包括它的派生类
} 

catch (invalid_argument& ex) { // 这个块永远不会被执行
	//invalid_argument是logic_error的派生类
}
```

所以不要把处理基类异常的 catch 子句放在处理派生类异常的 catch 子句的前面，上面的catch块应该反过来

### 13.通过引用reference捕获异常

当你写一个 catch 子句时,必须确定让异常通过何种方式传递到 catch 子句里。你可以有三个选择:与你给函数传递参数一样,通过指针(by pointer),通过传值(by value)或通过引用(by reference)。

1.通过指针

理论上这种方法的实现对于这个过程来说是效率最高的。因为在传递异常信息时,只有采用通过指针抛出异常的方法才能够做到不拷贝对象

```
void someFunction(){
    exception ex;
    throw &ex;	//抛出一个指针
}
```

这简直糟糕透了,因为处理这个异常的 catch 子句接受到的指针,其指向的对象已经不再存在。全局与静态对象都能够做到这一点,但是程序员很容易忘记这个约束。

2.值传递

当它们被抛出时系统将对异常对象拷贝两次，派生类的异常对象被做为基类异常对象捕获时,那它的派生类行为就被切掉了

3.引用

通过引用捕获异常能使你避开上述所有问题。不象通过指针捕获异常,这种方法不会有对象删除的问题而且也能捕获标准异常类型。也不象通过值捕获异常,这种方法没有 slicing problem,而且异常对象只被拷贝一次。

### 14.尽量使用构造的方式返回值

1.返回指针

```
const Rational * operator*(const Rational& lhs,const Rational& rhs);
```

这样的调用会很滑稽，而且调用者需要删除函数返回的指针，否则会造成内存泄露。

```
Rational a = 10;
Rational b(1, 2);
Rational c = *(a * b);
delete c;
```

2.返回引用

```
const Rational& operator*(const Rational& lhs,const Rational& rhs)
{
    Rational result(lhs.numerator() * rhs.numerator(),
    lhs.denominator() * rhs.denominator());
    return result;//返回时,其指向的对象已经不存在了
}
```

3.返回对象

一种高效的做法是，利用构造返回一个对象，而不是直接返回

```
const Rational operator*(const Rational& lhs,const Rational& rhs)
{
    return Rational(lhs.numerator() * rhs.numerator(),
    				lhs.denominator() * rhs.denominator());
}
```

### 15.使用重载避免隐式类型转换

对于如下类：

```
class UPInt { 
    public: // integers 类
        UPInt();
        UPInt(int value);
};
const UPInt operator+(const UPInt& lhs, const UPInt& rhs)
```

对于如下操作：

```
UPInt upi1, upi2，upi3;
upi3=upi1+10；
upi3=10+upi2；
```

这些语句也能够成功运行。方法是通过建立临时对象把整形数 10 转换为 UPInts，但是建立临时对象进行隐式类型转换是有代价的，我们不想要这种开销。

所以要实现这种功能，重载是个好办法

```
const UPInt operator+(const UPInt& lhs,const UPInt& rhs);
const UPInt operator+(const UPInt& lhs,int rhs);
const UPInt operator+(int lhs,const UPInt& rhs);
```

不要重载如下的函数：

```
const UPInt operator+(int lhs, int rhs);
```

这是因为每一个重载的 operator 必须带有一个用户定义类型(user-defined type)的参数。

### 16.+=还是=？

operator+ 根据 operator+=实现的

```
const Rational operator+(const Rational& lhs,const Rational& rhs)
{
	return Rational(lhs) += rhs;
}

const Rational operator-(const Rational& lhs,const Rational& rhs)
{
	return Rational(lhs) -= rhs;
}
```

总的来说 operator 的赋值形式（+=）比其单独形式（+）效率更高,因为单独形式要返回一个新对象,从而在临时对象的构造和释放上有一些开销。赋值形式把结果写到左边的参数里,因此不需要生成临时对象来容纳 operator 的返回值。

但是这样会带来调用的复杂性

```
Rational a, b, c, d, result;
result = a + b + c + d;	//单独形式
 
result = a; 
result += b;	//赋值形式 
result += c; 
result += d;
```

### 17.理解虚函数

虚函数类在机理是使用 virtual table （vtbl）和 virtual table pointers（vptr）

一个vtbl通常是一个函数指针数组，程序中只要有虚函数或者继承了虚函数，就会有自己的vtbl。类中vtbl是指向虚函数实现的指针数组。

```
class C1 {
    public:
        C1();
        virtual ~C1();
        virtual void f1();
        virtual int f2(char c) const;
        virtual void f3(const string& s);
        void f4() const;
};
```

虚函数所需的第一个代价:你必须为每个包含虚函数的类的 virtualtalbe 留出空间。类的 vtbl 的大小与类中声明的虚函数的数量成正比。

Virtual table 只实现了虚拟函数的一半机制,如果只有这些是没有用的。只有用某种方法指出每个对象对应的 vtbl 时,它们才能使用。这是 virtual table pointer 的工作,它来建立这种联系。

虚函数所需的第二个代价是:在每个包含虚函数的类的对象里,你必须为额外的指针付出代价。

![原理图](/home/560204/gitee/LearnNote/cpp/cppAdvance/effectiveCpp/vptr.png)

虚函数不能是内联的。这是因为“内联”是指“在编译期间用被调用的函数体本身来代替函数调用的指令,”但是虚函数的“虚”是指“直到运行时才能知道要调用的是哪一个函数。

虚函数所需的第三个代价:你实际上放弃了使用内联函数。

### 18.智能指针

智能指针从模板中生成，大多数看起来如下：

```
template<class T>
class SmartPtr {
    public:
        SmartPtr(T* realPtr = 0);
        SmartPtr(const SmartPtr& rhs);
        ~SmartPtr();// 释放灵巧指针
        SmartPtr& operator=(const SmartPtr& rhs);
        T* operator->() const;// dereference 一个灵巧指针
        T& operator*() const;// dereference 灵巧指针
    private:
        T *pointee;// 灵巧指针所指的对象
};
```

T& operator->() const;

```
template<class T>
T& SmartPtr<T>::operator*() const
{
    //perform "smart pointer" processing;
    return *pointee;
}
```

### 19.C/C++混合使用需要解决的问题

1.函数同名的问题

由于C++存在函数重载，所以会有许多同名的函数，编译器为了给予区分，在编译过程中会对函数名进行名变换。因为链接程序通常无法分辨同名的函数，所以名变换是对链接程序的妥协，而C的编译器没有这种功能。

c++中有一个函数叫 drawline 而编译器将它变换为 xyzzy,你总使用名字 drawLine,不会注意到背后的 obj 文件引用的是 xyzzy的。但如果 drawLine 是一个 C 函数,obj 文件(或者是动态链接库之类的文件)中包含的编译后的 drawLine 函数仍然叫 drawLine;没有名变换动作。当你试图将 obj 文件链接为程序时,将得到一个错误,因为链接程序在寻找一个叫 xyzzy 的函数,而没有这样的函数存在。

要解决这个问题,你需要一种方法来告诉 C++编译器不要在这个函数上进行名变换。

要禁止名变换,使用 C++的 extern 'C'指示:

```
extern “C”
void drawLine(int x1, int y1, int x2, int y2);
```

你甚至可以在 C++函数上申明 extern 'C'

```
extern “C” void twiddleBits(unsigned char bits);
```

经常,你有一堆函数不想进行名变换,为每一个函数添加 extern 'C'是痛苦的。幸好,这没必要。extern 'C'可以对一组函数生效,只要将它们放入一对大括号中

```
extern "C" {
    void drawLine(int x1, int y1, int x2, int y2);
    void twiddleBits(unsigned char bits);
    void simulate(int iterations);
}
```

当用C++编译时,你应该加 extern 'C',但用 C 编译时,不应该这样。通过只在 C++编译器下定义的宏__cplusplus,你可以将头文件组织得这样

```
#ifdef __cplusplus
extern "C" {
#endif
    void drawLine(int x1, int y1, int x2, int y2);
    void twiddleBits(unsigned char bits);
    void simulate(int iterations);
#ifdef __cplusplus
}
#endif
```

2.静态初始化

为了解决 main()应该首先被调用,而对象又需要在 main()执行前被构造的两难问题,许多编译器在 main()的最开始处插入了一个特别的函数,由它来负责静态初始化。

```
int main(int argc, char *argv[])
{
    performStaticInitialization();
    the statements you put in main go here;
    performStaticDestruction();
}
```

所以只要程序的任意部分是 C++写的,你就应该用 C++写 main()函数

为了少改动程序，将C 写的 main()改名为 realMain(),然后用 C++版本的 main()调用realMain():

```
extern "C"
int realMain(int argc, char *argv[]); // function in C
int main(int argc, char *argv[]) // write this in C++
{
    return realMain(argc, argv);
}
```

3.数据兼容

将在两种语言间传递的东西限制在用 C 编译的数据结构的范围内;这些结构的 C++版本可以包含非虚成员函数。