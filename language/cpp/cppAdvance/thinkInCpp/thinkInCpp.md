# C++编程思想

[TOC]

## 第一部分

## 第二部分

### 1.设计模式

#### 1.1创建型模式

##### 1.1.1单例模式

单例模式用来控制类只能产生一个实例对象

实现单例的步骤
1.构造函数私有化
2.增加私有静态的当前类的指针变量
3.提供静态的对外接口

```
class A {
private:
    A() { }
public:
    static A *getInstace() {
        return a;
    }
private:
    static A *a;
};
A *A::a = NULL;
```

懒汉式：需要时再创建

```
class singLazzy {
private:
    singLazzy() {cout<<"singlelazzy"<<endl;}

public:
    static singLazzy *getInstace() {
        if (singleton == NULL) {
            singleton = new singLazzy;
        }
        return singleton;
    }
    static void freeSpace(){
        if (singleton != NULL) {
            delete singleton;
            cout<<"空间已经释放"<<endl;
        }
    }

private:
    static singLazzy *singleton;
};

singLazzy *singLazzy::singleton = NULL;
```

饿汉式:类初始化就创建对象

```
class singleHungry{
private:
    singleHungry(){cout<<"singlehungry"<<endl;};
public:
    static singleHungry* getInstace(){
        return singlehun;
    }

private:
    static singleHungry* singlehun;
};

singleHungry* singleHungry::singlehun=new singleHungry;
```

##### 1.1.2工厂模式

提供了一种创建对象的最佳方式，我们在创建对象时不会对客户端暴露创建逻辑，并且是通过使用一个共同的接口来指向新创建的对象。

```
class abstractFruit {
public:
    virtual void showName() = 0;
};

class apple : public abstractFruit {
public:
    virtual void showName() {
        cout << "我是苹果" << endl;
    }
};

class banana : public abstractFruit {
public:
    virtual void showName() {
        cout << "我是香蕉" << endl;
    }
};

class pear : public abstractFruit {
public:
    virtual void showName() {
        cout << "我是梨" << endl;
    }
};

class fruitFactory {
public:
    static abstractFruit *creatFruit(string name) {
        if (name == "apple") {
            return new apple;
        }
        if (name == "banana") {
            return new banana;
        }
        if (name == "pear") {
            return new pear;
        } else {
            return NULL;
        }
    }
};

int main() {
    fruitFactory *factory = new fruitFactory;
    abstractFruit *apple = factory->creatFruit("apple");
    apple->showName();
    return 0;
}
```

##### 1.1.3抽象工厂模式

围绕一个超级工厂创建其他工厂。该超级工厂又称为其他工厂的工厂。在抽象工厂模式中，接口是负责创建一个相关对象的工厂，不需要显式指定它们的类。每个生成的工厂都能按照工厂模式提供对象。

```
class abstractFactory {
public:
    virtual abstractFruit *createFruit() = 0;
};

......

class applefactory : public abstractFactory {
    virtual abstractFruit *createFruit() {
        return new apple;
    }
};

class bananafactory : public abstractFactory {
    virtual abstractFruit *createFruit() {
        return new banana;
    }
};

class pearfactory : public abstractFactory {
    virtual abstractFruit *createFruit() {
        return new pear;
    }
};
```

##### 1.1.4建造者模式

建造者模式（Builder Pattern）使用多个简单的对象一步一步构建成一个复杂的对象。

```
class Packing {
    public:
        virtual string pack() {return "";}
};

class Wraper : public Packing {
    public:
    	string pack() {return "纸包装的食物";}
};

class Botton : public Packing {
    public:
    	string pack() {return "竹子包装的食物";}
};

class Item {
    public:
        virtual string name() = 0;
        virtual Packing *packing() = 0;
        virtual float price() = 0;
};

class Burger : public Item {
	public:	
		float price() {return 17.5;	}	
		Packing *packing() {
			Packing *pack = new Wraper();
			return pack;
		}	
        string name() {	
        	string n = "这是堡";
        	return n;
		}
};

class Drunk : public Item {
	public:	
		float price() {return 10.0;	}	
		Packing *packing() {
			Packing *pack = new Botton();
			return pack;
		}	
        string name() {	
        	string n = "这是饮料";
        	return n;
		}
};

class vegBurger : public Burger {
	public:	
		float price() {return 12.5;	}	
        string name() {	
        	string n = "这是蔬菜堡";
        	return n;
		}
};
```

##### 1.1.5原型模式

原型模式（Prototype Pattern）是用于创建重复的对象，同时又能保证性能。针对一个多个相似对象的情况，提供一个快速生成对象的方式。

本例中同一电脑，只有品牌是不同的，其他参数都是一样的。那我们就可以先用一个正常的对象，克隆出新的对象，然后再微调新对象的特殊属性。这样就达到快速生成相似对象的方法。

```
class Computer
{
public:
    void SetBrandName(string brandName)         //设置品牌
    {
        this->m_BrandName = brandName;
    }

    void SetCpu(string cpu)                     //设置CPU
    {
        this->m_Cpu = cpu;
    }

    void SetMemory(string memory)               //设置内存
    {
        this->m_Memory = memory;
    }

    void SetVideoCard(string videoCard)        //设置显卡
    {
        this->m_VideoCard=videoCard;
    }


    Computer Clone()                               //克隆函数
    {
        Computer ret;
        ret.SetBrandName(this->m_BrandName);
        ret.SetCpu(this->m_Cpu);
        ret.SetMemory(this->m_Memory);
        ret.SetVideoCard(this->m_VideoCard);
        return ret;
    }
    private:
    string m_BrandName;                         //品牌
    string m_Cpu;                               //CPU
    string m_Memory;                            //内存
    string m_VideoCard;                         //显卡
};

int main()
{
    Computer asusComputer;
    asusComputer.SetBrandName("华硕");
    asusComputer.SetCpu("I7 8700");
    asusComputer.SetMemory("16g");
    asusComputer.SetVideoCard("gtx 1080 ti");
    asusComputer.ShowParams();
    
     //再生产宏基电脑
    Computer acerComputer = asusComputer.Clone();
    acerComputer.SetBrandName("宏基");
}
```



#### 1.2结构型模式

##### 1.2.1 适配器模式

适配器模式（Adapter Pattern）是作为两个不兼容的接口之间的桥梁。

Adaptee类没有Request方法，而客户期待这个方法。为了使客户能够使用Adaptee类，提供一个中间环节，即类Adapter类，Adapter类实现了Target接口，并继承自Adaptee，Adapter类的Request方法重新封装了Adaptee的SpecificRequest方法，实现了适配的目的。

```
class Target{
    public:
		virtual void Request(){}
};

class Adaptee{
    public:
    	void SpecificRequest(){}
};

class Adapter:public Adaptee,public Target
{
    void Request(){
        this->SpeciaficRequest();
    }
};

int main(){
    Target *t=new Adapter();
    t->Requeset();
}

```

##### 1.2.2 装饰器模式

装饰器模式（Decorator Pattern）允许向一个现有的对象添加新的功能，同时又不改变其结构。这种类型的设计模式属于结构型模式，它是作为现有的类的一个包装。可以动态的给对象添加额外的职责或者功能。

```
class IShow {
public:
	virtual void show();
}; 

class Person :	public IShow {
public:
	Person(std::string name);
	void show() override{
        printf("我叫：%s\n", _name.c_str());
	}
private:
	std::string _name;
};

class IClothes :public IShow {
public:
	IClothes(IShow* show);
	~IClothes();
	virtual void show() override;
protected:
	IShow* _show;
};

class TShirt :public IClothes {
public:
	TShirt(IShow* show);
	void show()override{
    {
        _show->show();
        printf("穿上了漂亮的T恤,使我更精神！\n");
	}
};

int main() {
	IShow* per = new Person("张三");
	per = new TShirt(per);
	per->show();
}
```

##### 1.2.3 代理模式

在代理模式（Proxy Pattern）中，一个类代表另一个类的功能。这种类型的设计模式属于结构型模式。在代理模式中，我们创建具有现有对象的对象，以便向外界提供功能接口。

```
class IFactory
{
public:
	IFactory(){}
	virtual void makeProduct() = 0;
}


class PhoneFactory : IFactory
{
public:
	PhoneFactory(){}
	void makeProduct()
	{
		cout<<"生产手机"<<endl;
	}
}


class FoxconnProxy : IFactory
{
public:
	FoxconnProxy(IFactory* factory)
	{
		m_real = factory;
	}
	void makeProduct()
	{
		m_real->makeProduct();
	}
private:
	IFactory* m_real;
}

int main(){
    IFactory* factory = new PhoneFactory();
	FoxconnProxy* proxy =  new FoxconnProxy(factory);
	proxy->makeProduct();
}
```

##### 1.2.4 外观模式

外观模式（Facade Pattern）隐藏系统的复杂性，并向客户端提供了一个客户端可以访问系统的接口。这种类型的设计模式属于结构型模式，它向现有的系统添加一个接口，来隐藏系统的复杂性。

```
class SubSystem_0
{
public:
	void method()
	{
		std::cout << "SubSystem_0" << std::endl;
	}
};

class SubSystem_1
{
public:
	void method()
	{
		std::cout << "SubSystem_1" << std::endl;
	}
};

class SubSystem_2
{
public:
	void method()
	{
		std::cout << "SubSystem_2" << std::endl;
	}
};

class Facade
{
private:
	SubSystem_0 * m_pSystem_0;
	SubSystem_1 * m_pSystem_1;
	SubSystem_2 * m_pSystem_2;
public:
	Facade()
	{
		m_pSystem_0 = new SubSystem_0();
		m_pSystem_1 = new SubSystem_1();
		m_pSystem_2 = new SubSystem_2();
	}
	~Facade()
	{
		delete m_pSystem_0;
		delete m_pSystem_1;
		delete m_pSystem_2;
	}
	// 该方法具体怎么调用是根据需求来定
	void method()
	{
		m_pSystem_0->method();
		m_pSystem_1->method();
		m_pSystem_2->method();
	}
};

int main()
{
	Facade * p = new Facade();
	p->method();
}
```

##### 1.2.5 桥接模式

桥接（Bridge）是用于把抽象化与实现化解耦，使得二者可以独立变化。

```

//操作系统
class OS
{
public:
	virtual void InstallOS_Imp() {}
};
class WindowOS: public OS
{
public:
	void InstallOS_Imp() { cout<<"安装Window操作系统"<<endl; } 
};
class LinuxOS: public OS
{
public:
	void InstallOS_Imp() { cout<<"安装Linux操作系统"<<endl; } 
};
class UnixOS: public OS
{
public:
	void InstallOS_Imp() { cout<<"安装Unix操作系统"<<endl; } 
};


class Computer
{
public:
	virtual void InstallOS(OS *os) {}
};
class DellComputer: public Computer
{
public:
	void InstallOS(OS *os) { os->InstallOS_Imp(); }
};
class AppleComputer: public Computer
{
public:
	void InstallOS(OS *os) { os->InstallOS_Imp(); }
};
class HPComputer: public Computer
{
public:
	void InstallOS(OS *os) { os->InstallOS_Imp(); }
};


int main()
{
	OS *os1 = new WindowOS();
	OS *os2 = new LinuxOS();
	Computer *computer1 = new AppleComputer();
	computer1->InstallOS(os1);
	computer1->InstallOS(os2);
}
```

##### 1.2.6 组合模式

组合模式，就是将对象组合成树形结构以表示‘部分-整体’的层次结构。组合模式使得用户对单个对象和组合对象的使用具有一致性。

这种模式创建了一个包含自己对象组的类。该类提供了修改相同对象组的方式。

```
class ComponentPtr
{
protected:
	std::string m_strName;
public:
	ComponentPtr(std::string str)
	{
		m_strName = str;
	}
	virtual void add(ComponentPtr * p) = 0;
	virtual void remove(ComponentPtr * p) = 0;
	virtual void display() = 0;
};

class LeafPtr : public ComponentPtr
{
public:
	LeafPtr(std::string str) : ComponentPtr(str) {}
	void add(ComponentPtr * p)
	{
		std::cout << "Leaf cannot add" << std::endl;
	}
	void remove(ComponentPtr * p)
	{
		std::cout << "Leaf cannot remove" << std::endl;
	}
	void display()
	{
		std::cout << m_strName << std::endl;
	}
};

class CompositePtr : public ComponentPtr
{
private:
	// 这里使用智能指针不用自己释放new的内存
	std::vector<std::shared_ptr<ComponentPtr>> m_vec;
public:
	CompositePtr(std::string str) : ComponentPtr(str) {};
	~CompositePtr()
	{
		if (!m_vec.empty())
		{
			m_vec.clear();
		}
	}
	void add(ComponentPtr * p)
	{
		auto it = find_if(m_vec.begin(), m_vec.end(), 
			[p](std::shared_ptr<ComponentPtr> ptr) {return p == ptr.get(); });
		if (it == m_vec.end())
			m_vec.push_back(std::shared_ptr<ComponentPtr>(p));
	}
	void remove(ComponentPtr * p)
	{
		auto it = find_if(m_vec.begin(), m_vec.end(),
			[p](std::shared_ptr<ComponentPtr> ptr) {return p == ptr.get(); });
		if (it == m_vec.end())
			return;
		m_vec.erase(it);
	}
	void display()
	{
		for (auto it = m_vec.cbegin(); it != m_vec.cend(); it++)
		{
			(*it)->display();
		}
	}
};

int main()
{
	using namespace std;
	// 组合模式
	CompositePtr * p = new CompositePtr("总部");
	p->add(new LeafPtr("总部财务部门"));
	p->add(new LeafPtr("总部人力资源部门"));
	CompositePtr * p1 = new CompositePtr("上海分部");
	p1->add(new LeafPtr("上海分部财务部门"));
	p1->add(new LeafPtr("上海分部人力资源部门"));
	p->add(p1);
}	//形成一种树状的关系
```

##### 1.2.7享元模式

享元模式（Flyweight Pattern）主要用于减少创建对象的数量，以减少内存占用和提高性能。在有大量对象时，有可能会造成内存溢出，我们把其中共同的部分抽象出来，如果有相同的业务请求，直接返回在内存中已有的对象，避免重新创建。

```
class Flyweight  //抽象的享元类
{
public :
	virtual void Operator(int i) = 0;
};
 
class ConcreteFlyweight : public Flyweight  //共享的子类
{
public:
	void Operator(int i)
	{
		cout <<"共享的Flyweight： " << i<<endl;
	}
};


class FlyweightFactory  //享元工厂
{
private: 
	map<string, Flyweight*> flyweights;  //模块名列表
public:
	FlyweightFactory()
	{
		//这里需要用堆，因为这是给客户程序返回的，如果不用堆，则会返回局部对象的引用
		flyweights["x"] = new ConcreteFlyweight();
		flyweights["y"] = new ConcreteFlyweight();
		flyweights["z"] = new ConcreteFlyweight();//所有的属性为“z”的模块都只对应这个一个实例，这正是享元模式的精髓所在呀
	}
	
	Flyweight* GetFlyWeight(string key)
	{
		if (!flyweights.count(key))
			flyweights[key] = new ConcreteFlyweight();
		return flyweights[key];
	}
};
```

#### 1.3行为型模式

##### 1.3.1命令模式

命令模式就是一个函数对象：一个作为对象的函数。通过将函数封装成对象，就可以以参数的方式传递给函数或者其他对象。

```
class Command{
    public:
    	virtual void execute()=0;
}

class open:public Command {
    public:
    	void void execute(){cout<<"i am open!"}
}

class close:public Command {
    public:
    	void void execute(){cout<<"i am close!"}
}

class Macro {
    vector<Command *> commands;
    public:
    	void run(){
            auto it=command.begin();
            while(it!=commands.end()){
                (*it++)->execute();
            }
    	}
}
```

对于类Macro来说就可以接受Command命令，根据具体的命令对象来执行不同的命令。

命令模式的主要特点就是可以通过一个对象或者函数传递一个想要的动作。

##### 1.3.2 中介者模式

中介者模式（Mediator Pattern）是用来降低多个对象和类之间的通信复杂性。这种模式提供了一个中介类，该类通常处理不同类之间的通信，并支持松耦合，使代码易于维护。

```

class Person
{
protected:
	Mediator *m_mediator; //中介
public:
	virtual void SetMediator(Mediator *mediator){} //设置中介
	virtual void SendMessage(string message) {}    //向中介发送信息
	virtual void GetMessage(string message) {}     //从中介获取信息
};
//抽象中介机构
class Mediator
{
public:
	virtual void Send(string message, Person *person) {}
	virtual void SetA(Person *A) {}  //设置其中一方
	virtual void SetB(Person *B) {}
};
//租房者
class Renter: public Person
{
public:
	void SetMediator(Mediator *mediator) { m_mediator = mediator; }
	void SendMessage(string message) { m_mediator->Send(message, this); }
	void GetMessage(string message) { cout<<"租房者收到信息"<<message; }
};
//房东
class Landlord: public Person
{
public:
	void SetMediator(Mediator *mediator) { m_mediator = mediator; }
	void SendMessage(string message) { m_mediator->Send(message, this); }
	void GetMessage(string message) { cout<<"房东收到信息："<<message; }
};
//房屋中介
class HouseMediator : public Mediator
{
private:
	Person *m_A; //租房者
	Person *m_B; //房东
public:
	HouseMediator(): m_A(0), m_B(0) {}
	void SetA(Person *A) { m_A = A; }
	void SetB(Person *B) { m_B = B; }
	void Send(string message, Person *person) 
	{
		if(person == m_A) //租房者给房东发信息
			m_B->GetMessage(message); //房东收到信息
		else
			m_A->GetMessage(message);
	}
};


int main()
{	
	Mediator *mediator = new HouseMediator();
	Person *person1 = new Renter();    //租房者
	Person *person2 = new Landlord();  //房东
	mediator->SetA(person1);
	mediator->SetB(person2);
	person1->SetMediator(mediator);
	person2->SetMediator(mediator);
	person1->SendMessage("我想在南京路附近租套房子，价格800元一个月\n");
	person2->SendMessage("出租房子：南京路100号，70平米，1000元一个月\n");
	delete person1; delete person2; delete mediator;
	return 0;
}
```

##### 1.3.3 解释器模式

给定一个语言，定义它的文法表示，并定义一个解释器，这个解释器使用该标识来解释语言中的句子。这种模式被用在 SQL 解析、符号处理引擎等。

##### 1.3.4 访问者模式

