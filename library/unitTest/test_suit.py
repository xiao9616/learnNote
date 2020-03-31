# coding = utf-8
'''
Author:xiao
date= 下午4:04
'''

import unittest
from test_mathfunc import MyTestCase

if __name__ == '__main__':
    suit = unittest.TestSuite()
    tests = [MyTestCase("test_add"), MyTestCase("test_minus"), MyTestCase("test_divide")]
    suit.addTests(tests)
    suit.addTest(MyTestCase("test_multi"))
    suit.addTests(unittest.TestLoader().loadTestsFromTestCase(MyTestCase))
    with open('unittestreport.txt', 'a') as f:
        runner = unittest.TextTestRunner(stream=f, verbosity=2)
        runner.run(suit)
