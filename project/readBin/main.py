# =============================================
# -*- coding: utf-8 -*-           
# @Time    : 2020/4/24 下午3:08    
# @Author  : xiao9616           
# @Email   : 749935253@qq.com   
# @File    : main.py         
# @Software: PyCharm
# ============================================
import os
import datetime
import time
import hashlib

filepath = "./rtthread.bin"


def get_time(timeStamp):
    return time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(timeStamp))


def md5sum(filepath):
    file_object = open(filepath, 'rb')
    file_content = file_object.read()
    file_object.close()
    file_md5 = hashlib.md5(file_content)
    return file_md5.hexdigest()


if __name__ == '__main__':
    fileinfo = os.stat(filepath)
    print("程序名称：", os.path.basename(filepath))
    print("程序修改时间：", get_time(fileinfo.st_mtime))
    print("程序大小：{} 字节".format(os.path.getsize(filepath)))
    print("md5sum:",md5sum(filepath))
