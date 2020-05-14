# =============================================
# -*- coding: utf-8 -*-           
# @Time    : 2020/5/14 上午10:26    
# @Author  : xiao9616           
# @Email   : 749935253@qq.com   
# @File    : mutil_gpu.py         
# @Software: PyCharm
# ============================================
'''
多GPU使用：
使用单个gpu虚拟出来多个gpu
分布式训练:tf.distribute.MirroredStrategy()
或者手动操作tf.device
'''

import tensorflow as tf

tf.debugging.set_log_device_placement(True)
gpu_physical = tf.config.experimental.list_physical_devices("GPU")

if gpu_physical:
    # 设置虚拟gpu
    tf.config.experimental.set_virtual_device_configuration(gpu_physical[0],
                                                            [tf.config.experimental.VirtualDeviceConfiguration(
                                                                memory_limit=1024),
                                                                tf.config.experimental.VirtualDeviceConfiguration(
                                                                    memory_limit=1024)])
    gpu_logical = tf.config.experimental.list_logical_devices('GPU')
    gpu_physical = tf.config.experimental.list_physical_devices('GPU')
    print(gpu_logical)
    print(gpu_physical)

strategy = tf.distribute.MirroredStrategy()
with strategy.scope():
    inputs = tf.keras.layers.Input(shape=(1,))
    predictions = tf.keras.layers.Dense(1)(inputs)
    model = tf.keras.models.Model(inputs=inputs, outputs=predictions)
    model.compile(loss='mse', optimizer=tf.keras.optimizers.SGD(learning_rate=0.2))
