# =============================================
# -*- coding: utf-8 -*-           
# @Time    : 2020/5/23 下午3:41    
# @Author  : xiao9616           
# @Email   : 749935253@qq.com   
# @File    : autodiff.py         
# @Software: PyCharm
# @Discript:
# ============================================
'''
计算雅克比矩阵
tf.autodiff.ForwardAccumulator
tf.autodiff.GradientTape
tf.GradientTape
'''
import tensorflow as tf

x = tf.constant(3.0)
with tf.GradientTape() as g:
    g.watch(x)
    y = x * x
dy_dx = g.gradient(y, x)  # Will compute to 6.0
print(dy_dx)


x = tf.constant([[2.0, 3.0], [1.0, 4.0]])
dense = tf.keras.layers.Dense(1)
dense.build([None, 2])

with tf.autodiff.ForwardAccumulator(primals=dense.kernel, tangents=tf.constant([[1.], [0.]])) as acc:
    loss = tf.reduce_sum((dense(x) - tf.constant([1., -1.])) ** 2.)
print(acc.jvp(loss))
