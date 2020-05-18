# =============================================
# -*- coding: utf-8 -*-           
# @Time    : 2020/5/14 10:43 下午    
# @Author  : xiao9616           
# @Email   : 749935253@qq.com   
# @File    : test.py         
# @Software: PyCharm
# ============================================

import threading
import time
from threading import Lock

lock=Lock()
def thread1(name):
    global lock
    lock.acquire()
    print("thread1 start")
    time.sleep(2)
    print("thread1 end")
    lock.release()


def thread2(name):
    global lock
    lock.acquire()
    print("thread2 start")
    time.sleep(4)
    print("thread2 end")
    lock.release()


if __name__ == '__main__':
    thread1 = threading.Thread(target=thread1,args=("xiao",))
    thread2 = threading.Thread(target=thread2,args=("xuan",))
    thread1.start()
    thread2.start()

    thread1.join()
    thread2.join()

    print("end")
