# =============================================
# -*- coding: utf-8 -*-           
# @Time    : 2020/5/14 10:43 下午    
# @Author  : xiao9616           
# @Email   : 749935253@qq.com   
# @File    : test.py         
# @Software: PyCharm
# ============================================
import contextlib

@contextlib.contextmanager
def file_open(filename):
    print("file open")
    yield {}
    print("file end")


with file_open("xiao.txt") as f:
    print("file process")
