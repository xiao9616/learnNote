# =============================================
# -*- coding: utf-8 -*-           
# @Time    : 2020/5/14 上午11:29    
# @Author  : xiao9616           
# @Email   : 749935253@qq.com   
# @File    : tf.sysconfig.py         
# @Software: PyCharm
# ============================================
import tensorflow as tf

print(tf.sysconfig.get_compile_flags())
print(tf.sysconfig.get_include())
print(tf.sysconfig.get_lib())
print(tf.sysconfig.get_link_flags())
