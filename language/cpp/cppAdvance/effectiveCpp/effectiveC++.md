# EffectiveC++

## 1.尽量使用const/enum/inline替代#define

1.1对于单纯常量，最好以const替换#define

```
#define PI 3.1415926

const float PI 3.1415926
```

1.2对于函数宏，最好使用inline函数替换#define

```
#define MAX（a，b） f((a)>(b)? (a):(b))

template<typename T>
inline void max(const T& a,const T& b)
{
    f(a>b ? a:b)
}
```

## 2.const

2.1const指针

const如果在星号左边，表示被指物为常量，如果在右边，表示为指针自身为常量

```
char* p					//no-const pointer,no-const data
const char* p			//no-const pointer,const data
char const * p			//no-const pointer,const data
char* const p			//const pointer , no-const data
const char* const p		//const pointer,const data
```

## 3.确保初始化

3.1构造函数member initialization list替换赋值操作

```
class people {
    int age;
    string name;
public:
	//成员初始化列表
    people(int age, const string &name) : age(age), name(name) {
        
    }
    //而不是赋值
    people(int age, const string &name) {
        age=age;
        name=name;
    }
};
```

## 4.拷贝构造/拷贝赋值构造/析构函数

4.1编译器会为空类声明拷贝构造/拷贝赋值构造/析构函数（只有需要的时候才会被创建），如果没有构造函数还会生成一个默认构造函数。

```
class people{
public:
    people(){}
    people(const people& p){}
    ~people(){}
    people& operator=(const people& p){}
}
```

4.2如果类包含引用或者const成员，则必须自己定义拷贝赋值构造函数。

4.3如果不需要编译器自己创建构造函数，可以自己声明为private，并且不要定义。

```
private:
people(const people&);
people& operator=(const people&);
```

4.3基类应该带有virtual析构函数，如果类中有任何virtual函数，则应该拥有一个virtual析构函数。如果希望该类不要派生了，则不要声明virtual析构函数。

4.4为了使得可以连续赋值，需要返回*this的引用

```
people p1,p2,p3;
p1=p2=p3;


people& operator=(const people& p){
	...
    return *this;
}
```

4.5保证自我赋值需要作证同测试,保证自己可以赋值给自己

```
people& operator=(const people& p){
	if(this=&p) return *this;
	delete data;
	data=new people(p.data);
    return *this;
}
```

## 5.资源管理

5.1auto_ptr 智能指针自动对所指向对象调用delete

```
auto_ptr<people> p=new people(),p1;
p1(p);	//p会变成null
```

如果通过拷贝构造函数，拷贝赋值构造函数赋值auto_ptr会使得他们变成null，拷贝对象获得资源唯一控制权

shared_ptr可以解决上述问题

```
shared_ptr<people> p=new people();
shared_ptr<people> p1（p）;
p1=p;	//p1和p指向同一对象
```

5.2new和delete成对使用

```
string* str1=new string;
string* str2=new string[100];

delete str1;
delete [] str2;
```

## 6.实现

6.1尽可能延后变量定义式的出现时间

```
string encrypyted;
if('''){
    throw logic_error("error")
}
return encryptyed;
```

上述代码如果抛出异常，则encryptyed没有被使用，需要承担构造和析构成本。应当延后定义，直到需要。

```
if('''){
    throw logic_error("error")
}
string encrypyted;
return encryptyed;
```

6.2尽量少转型

转型语法

```
(T) expression
T(expression)
const_cast<T> (expression)
dynamic_cast<T> (expression)
reinterpret_cast<T> (expression)
static_cast<T> (expression)
```

## 7.面向对象

7.1**public继承**意味着is-a

7.2继承类会遮掩基类的名称，可以使用using base：：使其重见天日

7.3可以为纯虚函数提供定义，但调用时必须明确指出其所属类的名称

```C++
class shape{
    public:
    	virtual void draw() const = 0;
}
void shape::draw(){
    cout<<"default draw"<<endl;
}

//main
shape* ps1=new rectangle();
ps1->draw();
ps1->shape::draw(); //调用纯虚函数默认的draw
```

但不建议这么做，使用虚函数可以同时实现声明接口和默认实现

纯虚函数只继承接口，虚函数继承接口和默认实现，非虚函数继承接口和强制实现

7.4不要重新定义继承来的non-virtual函数

```
class B{
    public:
    	void method();
}

class D;public B{
    public:
    	void method();
}

B* pb=new D;
D* pd=new D;
pb->method();	//调用B：：method
pd->method();	//调用D：：method
```

7.5 virtual是动态绑定，缺省参数是静态绑定，所以不要继承缺省参数

```C++
class shape{
public:
    	virtual void draw(color=red) const;
}

class rectangle:public shape{
public:
    virtual void draw(color=green) const;
}

shape* ps=new rectangle();
ps->draw();	//调用rectangle：：draw(red);
```

ps的静态类型是shape，动态类型是rectangle，缺省参数来自静态绑定

7.6non-virtual-interface(NVI)

```
class shape{
public:
    	void draw(color=red) const{
            doDraw();
    	}
private:
		virtual void doDraw() const{
            
		}
}

class rectangle:public shape{
private:
    virtual void doDraw const {
        
    }
}
```

7.7复合意味着has-a，意味着is-implemented-in-terms-of(根据某物实现出)

7.8 private继承意味着is-implemented-in-terms-of(根据某物实现），编译器不会对类型进行转化，继承的所有属性都会变成private，即使原来是protected/public

7.9多重继承比单一继承复杂，多重继承适用于public继承接口类/private继承实现类

## 8.模板与泛型

8.1隐式接口，编译时多态（template）

显式接口，运行时多态（virtual）

8.2typename标示类型名称,但不能在基类列和成员初始列中使用

```
template<typename T>
void print2d(const C& container){
    if(container.size()>=2){
        typename C::const_iterator iter(container.begin());
    }
}
```

### 9.位操作

```C
测试第 k 位: s & (1 << k)
设置第 k 位: s |= (1 << k)
第 k 位置零: s &= ~(1 << k)
切换第 k 位值: s ^= (1 << k)
乘以 2n: s << n
除以 2n: s >> n
交集: s & t
并集: s | t
减法: s & ~t
交换 x = x ^ y ^ (y = x)
取出最小非 0 位（Extract lowest set bit）: s & (-s)
取出最小 0 位（Extract lowest unset bit）: ~s & (s + 1)
交换值: x ^= y; y ^= x; x ^= y;
```

