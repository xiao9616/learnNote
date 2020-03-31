

# unittest

unittest是Python自带的单元测试框架，我们可以用其来作为我们自动化测试框架的用例组织执行框架。

## 一.工作原理

编写业务函数mathfunc.py:

```
def add(a, b):
    return a+b

def minus(a, b):
    return a-b

def multi(a, b):
    return a*b

def divide(a, b):
    return a/b
```

unittest中最核心的四个概念是：TestCase, TestSuite, TestRunner, TestFixture。

### unittest.TestCase

一个class继承了unittest.TestCase，便是一个测试用例.如果其中有多个以 test 开头的方法，那么每有一个这样的方法，在load的时候便会生成一个TestCase实例，如：一个class中有四个test_xxx方法，最后在load到suite中时也有四个测试用例。

在每一个测试用例中可以重写以下函数:

setUp()该测试用例执行前的设置工作、
tearDown()该测试用例执行后的清理工作、
setUpClass()所有测试用例前的设置工作、
tearDownClass()所有测试用例执行后的清洗工作

verbosity 参数可以控制输出的错误报告的详细程度，默认是 1，如果设为 0，则不输出每一用例的执行结果。如果参数为2则表示输出详细结果。

编写测试函数:

```
class MyTestCase(unittest.TestCase):

    def setUp(self) -> None:
        super().setUp()

    def tearDown(self) -> None:
        super().tearDown()

    @classmethod
    def setUpClass(cls) -> None:
        super().setUpClass()

    @classmethod
    def tearDownClass(cls) -> None:
        super().tearDownClass()

    def test_add(self):
        self.assertEqual(3, add(1, 2))

    def test_minus(self):
        self.assertEqual(3, minus(6, 3))

    def test_mutil(self):
        self.assertEqual(6, multi(2, 3))

    @unittest.skip("skip this test")
    def test_divide(self):
        self.assertEqual(2, divide(6, 3))
        self.assertEqual(2.5, divide(5, 2))


if __name__ == '__main__':
    unittest.main()
```

### unittest.TestSuite

TestSuite用来控制多个测试用例和多个测试文件之间的测试顺序。（这里的示例中的几个测试方法并没有一定关系，但之后你写的用例可能会有先后关系，需要先执行方法A，再执行方法B）

```
import unittest
from test_mathfunc import MyTestCase

if __name__ == '__main__':
    suit = unittest.TestSuite()
    tests = [MyTestCase("test_add"), MyTestCase("test_minus"), MyTestCase("test_divide")]
    suit.addTests(tests)
    suit.addTest(MyTestCase("test_multi"))
    with open("./unittestreport.txt", 'a') as f:
        runner = unittest.TextTestRunner(stream=f, verbosity=2)
        runner.run(suit)
```

### unittest.TestRunner

TextRunner类的run()方法去一次执行多个脚本的用例

### unittest.TestFixture

用于一个测试环境的准备和销毁还原。当测试用例每次执行之前需要准备测试环境，每次测试完成后还原测试环境，比如执行前连接数据库、打开浏览器等，执行完成后需要还原数据库、关闭浏览器等操作。这时候就可以启用testfixture。

### unitest.TestLoader

TestLoadder用来加载TestCase到TestSuite中.

```
unittest.TestLoader().loadTestsFromTestCase(testCaseClass)
unittest.TestLoader().loadTestsFromModule(module)
unittest.TestLoader().loadTestsFromName(name,module=None)
unittest.TestLoader().loadTestsFromNames(names,module=None)
unittest.TestLoader().getTestCaseNames(testCaseclass)
unittest.TestLoader().discover()
```

