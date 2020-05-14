# =============================================
# -*- coding: utf-8 -*-           
# @Time    : 2020/5/14 上午8:55    
# @Author  : xiao9616           
# @Email   : 749935253@qq.com   
# @File    : tf.config.py         
# @Software: PyCharm
# ============================================
import tensorflow as tf

tf.debugging.set_log_device_placement(True)
'''
list_physical_devices
list_logical_devices
'''

cpu_physical = tf.config.experimental.list_physical_devices('CPU')
gpu_physical = tf.config.experimental.list_physical_devices('GPU')

cpu_logical = tf.config.experimental.list_logical_devices('CPU')
gpu_logical = tf.config.experimental.list_logical_devices('GPU')
print("cpu_logical : ", cpu_logical)
print("cpu_physical :", cpu_physical)
print("gpu_logical :", gpu_logical)
print("gpu_physical : ", gpu_physical)

'''
get_visible_devices
set_visible_devices:设置哪些设备可见
set_memory_growth:设置显存随情况增长，而不是全部占用
set_set_virtual_device_configuration:通过设置VirtualDeviceConfiguration(memory_limit=1024))也可以限制内存使用
'''
cpu_visible = tf.config.experimental.get_visible_devices("CPU")
gpu_visible = tf.config.experimental.get_visible_devices("GPU")
# tf.config.experimental.set_memory_growth(gpu_physical[0], True)
# tf.config.experimental.set_visible_devices(gpu_visible[0], 'GPU')
# tf.config.experimental.set_virtual_device_configuration(gpu_visible[0],tf.config.experimental.VirtualDeviceConfiguration(memory_limit=1024))
print(cpu_visible)
print(gpu_visible)

'''
set_soft_device_placement(True):设置自动选择存在的设备
'''
tf.config.set_soft_device_placement(True)

'''
device:使用device可以指定操作在不同的设备上进行
'''
with tf.device('/CPU:0'):
    a = tf.constant([[1., 2., 3.], [4., 5., 6.]])
    b = tf.constant([[1., 2.], [3., 4.], [5., 6.]])
    c = tf.matmul(a, b)
    print(c)

with tf.device('/GPU:0'):
    a = tf.constant([[1., 2., 3.], [4., 5., 6.]])
    b = tf.constant([[1., 2.], [3., 4.], [5., 6.]])
    c = tf.matmul(a, b)
    print(c)
