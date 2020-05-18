# =============================================
# -*- coding: utf-8 -*-           
# @Time    : 2020/5/14 10:43 下午    
# @Author  : xiao9616           
# @Email   : 749935253@qq.com   
# @File    : test.py         
# @Software: PyCharm
# ============================================
from concurrent.futures import ThreadPoolExecutor
import time


def get_html(times):
    time.sleep(2)
    print("get page {} sucess".format(times))


executor = ThreadPoolExecutor(max_workers=2)
task1 = executor.submit(get_html, (3))
task2 = executor.submit(get_html, (2))

# 判定某个任务是否完成
print(task1.done())
# 如果任务没有被执行，则可以取消
print(task2.cancel())
time.sleep(3)
print(task1.done())
# 显示任务的结果
print(task1.result())
