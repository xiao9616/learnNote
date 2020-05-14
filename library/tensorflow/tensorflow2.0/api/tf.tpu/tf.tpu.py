# =============================================
# -*- coding: utf-8 -*-           
# @Time    : 2020/5/14 上午10:53    
# @Author  : xiao9616           
# @Email   : 749935253@qq.com   
# @File    : tf.tpu.py         
# @Software: PyCharm
# ============================================
import os
import tensorflow as tf
# 获取tpu集群
tpu=tf.distribute.cluster_resolver.TPUClusterResolver()
# 链接集群
tf.config.experimental_connect_to_cluster(tpu)
# 初始化tpu
tf.tpu.experimental.initialize_tpu_system(tpu)
# tpu策略
strategy=tf.distribute.experimental.TPUStrategy(tpu)
with strategy.scope():




