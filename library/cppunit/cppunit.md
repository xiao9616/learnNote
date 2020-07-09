# CppUint

## 结构

CppUnit核心内容主要包括六个方面，

1. 测试对象（Test，TestFixture，...）：用于开发测试用例，以及对测试用例进行组织管理。

2. 测试结果（TestResult）：处理测试用例执行结果。TestResult与下面的TestListener采用的是观察者模式（Observer Pattern）。

3. 测试结果监听者（TestListener）：TestListener作为TestResult的观察者，担任实际的结果处理角色。

4. 结果输出（Outputter）：将结果进行输出，可以制定不同的输出格式。
5. 对象工厂（TestFactory）：用于创建测试对象，对测试用例进行自动化管理。

6. 测试执行体（TestRunner）：用于运行一个测试。

```
         Test              TestFixture      TestResult          TestListener     
        _______|_________            |                                    |          
        |               |            |                           TestSuccessListener
    TestComposite   TestLeaf         |                                    |          
        |               |____________|                           TestResultCollector          
    TestSuit                  |
                           TestCase                     
                              |
                      TestCaller<Fixture>
                      
                        Outputter                                    TestFactory                    
        ____________________|_________________                            |
        |                   |                |                   TestFactoryRegistry
    CompilerOutputter  TextOutputter    XmlOutputter                      |
                                                             TestSuiteFactory<TestCaseType>
                                                             
                                                 TestRunner    
                                                             
```

## 关键类

### Test

所有测试对象的基类。

CppUnit采用树形结构来组织管理测试对象（类似于目录树），因此这里采用了组合设计模式（Composite Pattern），Test的两个直接子类TestLeaf和TestComposite分别表示“测试树”中的叶节点和非叶节点，其中TestComposite主要起组织管理的作用，就像目录树中的文件夹，而TestLeaf才是最终具有执行能力的测试对象，就像目录树中的文件。

Test最重要的一个公共接口为：

```c++
virtual void run(TestResult *result) = 0;
```

其作用为执行测试对象，将结果提交给result。在实际应用中，我们一般不会直接使用Test、TestComposite以及TestLeaf，除非我们要重新定制某些机制。

### TestFixture

用于维护一组测试用例的上下文环境。

在实际应用中，我们经常会开发一组测试用例来对某个类的接口加以测试，而这些测试用例很可能具有相同的初始化和清理代码。为此，CppUnit引入TestFixture来实现这一机制。

TestFixture具有以下两个接口，分别用于处理测试环境的初始化与清理工作：

```c++
virtual void setUp();
virtual void tearDown();
```

### TestCase

测试用例，从名字上就可以看出来，它便是单元测试的执行对象。用户需从TestCase派生出子类并实现runTest以开发自己所需的测试用例。

### TestSuit

测试包，按照树形结构管理测试用例

TestSuit是TestComposite的一个实现，它采用vector来管理子测试对象（Test），从而形成递归的树形结构。

### TestCaller

TestCase适配器（Adapter），它将成员函数转换成测试用例

虽然我们可以从TestCase派生自己的测试类，但从TestCase类的定义可以看出，它只能支持一个测试用例，这对于测试代码的组织和维护很不方便，尤其是那些有共同上下文环境的一组测试。为此，CppUnit提供了TestCaller以解决这个问题。

TestCaller是一个模板类，它以实现了TestFixture接口的类为模板参数，将目标类中某个符合runTest原型的测试方法适配成TestCase的子类。在实际应用中，我们大多采用TestFixture和TestCaller相组合的方式

### TestResult和TestListener

处理测试信息和结果

前面已经提到，TestResult和TestListener采用了观察者模式，TestResult维护一个注册表，用于管理向其登记过的TestListener，当TestResult收到测试对象（Test）的测试信息时，再一一分发给它所管辖的TestListener。这一设计有助于实现对同一测试的多种处理方式。

### TestFactory

测试工厂

这是一个辅助类，通过借助一系列宏定义让测试用例的组织管理变得自动化

### TestRunner

用于执行测试用例，TestRunner将待执行的测试对象管理起来，然后供用户调用。其接口为：

```
virtual void addTest( Test *test ); 
virtual void run( TestResult &controller, const std::string &testPath = "" );
```

这也是一个辅助类，需注意的是，通过addTest添加到TestRunner中的测试对象必须是通过new动态创建的，用户不能删除这个对象，因为TestRunner将自行管理测试对象的生命期。

### 断言

CPPUNIT_ASSERT(condition)：判断condition的值是否为真，如果为假则生成错误信息。

CPPUNIT_ASSERT_MESSAGE(message, condition)：与CPPUNIT_ASSERT类似，但结果为假时报告messsage信息。

CPPUNIT_FAIL(message)：直接报告messsage错误信息。

CPPUNIT_ASSERT_EQUAL(expected, actual)：判断expected和actual的值是否相等，如果不等输出错误信息。

CPPUNIT_ASSERT_EQUAL_MESSAGE(message, expected, actual)：与CPPUNIT_ASSERT_EQUAL类似，但断言失败时输出message信息。

CPPUNIT_ASSERT_DOUBLES_EQUAL(expected, actual, delta)：判断expected与actual的偏差是否小于delta，用于浮点数比较。

CPPUNIT_ASSERT_THROW(expression, ExceptionType)：判断执行表达式expression后是否抛出ExceptionType异常。

CPPUNIT_ASSERT_NO_THROW(expression)：断言执行表达式expression后无异常抛出。

### 基础用法

```c++
#include <cppunit/TestCase.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TextOutputter.h>

// 定义测试用例
class SimpleTest : public CppUnit::TestCase
{
public:
    void runTest() // 重载测试方法
    {
        int i = 1;
        CPPUNIT_ASSERT_EQUAL(0, i);
    }
};

int main(int argc, char* argv[])
{
    CppUnit::TestResult r; 
    CppUnit::TestResultCollector rc;
    r.addListener(&rc); // 准备好结果收集器 

    SimpleTest t;
    t.run(&r); // 运行测试用例

    CppUnit::TextOutputter o(&rc, std::cout);
    o.write(); // 将结果输出

    return 0;
}
```

```c++
//
// Created by user on 2020/7/9.
//

#include "StringTest.h"

void StringTest::setUp() {
    m_str1 = "Hello, world";
    m_str2 = "Hi, cppunit";
}

void StringTest::tearDown() {
    TestFixture::tearDown();
}

void StringTest::testSwap() {
    std::string str1 = m_str1;
    std::string str2 = m_str2;
    m_str1.swap(m_str2);

    CPPUNIT_ASSERT(m_str1 == str2);
    CPPUNIT_ASSERT(m_str2 == str1);

}

void StringTest::testFind() {
    int pos1 = m_str1.find(',');
    int pos2 = m_str2.rfind(',');

    CPPUNIT_ASSERT_EQUAL(5, pos1);
    CPPUNIT_ASSERT_EQUAL(2, pos2);
}
//
// Created by user on 2020/7/9.
//

#ifndef FINGERVEIN_STRINGTEST_H
#define FINGERVEIN_STRINGTEST_H

#include <cppunit/TestCase.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TextTestResult.h>
#include <cppunit/TestRunner.h>


using namespace CppUnit;

class StringTest: public TestFixture {

public:
    void setUp() override;

    void tearDown() override;

    void testSwap();

    void testFind();
private:
    std::string     m_str1;
    std::string     m_str2;
};

TestResult result;
TestResultCollector resultCollector;
result.addListener(&resultCollector);


TestRunner runner;
runner.addTest(new TestCaller<StringTest>("testSwap", &StringTest::testSwap));
runner.addTest(new CppUnit::TestCaller<StringTest>("testFind", &StringTest::testFind));
runner.run(result); // 运行测试

CppUnit::TextOutputter o(&resultCollector, std::cout);
o.write();
```













