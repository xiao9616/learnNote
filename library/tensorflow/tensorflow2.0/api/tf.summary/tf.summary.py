# =============================================
# -*- coding: utf-8 -*-           
# @Time    : 2020/5/14 上午11:36    
# @Author  : xiao9616           
# @Email   : 749935253@qq.com   
# @File    : tf.summary.py         
# @Software: PyCharm
# ============================================
import tensorflow as tf

'''
tf.summary:保存训练过程及参数（loss accuracy variable等）及分布，可用于tensorboard显示
summary通过递增的方式更新日志，这让我们可以边训练边使用tensorboard读取日志进行可视化，从而实时监控训练过程。
'''

'''
api:
tf.summary.audio()
tf.summary.image()
tf.summary.histogram()
tf.summary.record_if(condition=condi):根据条件来确定是否记录
tf.summary.scalar():记录标量
tf.summary.text()：记录文本

tf.summary.create_file_writer() : 创建一个summary file writer
tf.summary.create_noop_writer() :创建一个什么都不做的summary file writer
tf.summary.flush()：#强制将buffer缓存到磁盘
tf.summary.SummaryWriter():一个接口，summary writer

tf.summary.trace_on():开启追踪计算图
tf.summary.trace_off()：关闭追踪计算图
tf.summary.trace_export()：关闭并导出
tf.summary.write():写入默认的summary writer

tf.summary.experimental.get_step() :获取summary writer的step
tf.summary.experimental.set_step()
tf.summary.experimental.summary_scope():summary writer tag
tf.summary.experimental.write_raw_pb():为了兼容v1
'''

'''
how to work:
'''

# 创建一个summary writer
summary = tf.summary.create_file_writer("./summary")
with summary.as_default():
    for i in range(100):
        '''
        model
        '''
        # 确定跟踪的变量
        # tf.summary.scalar("tags", loss, step=i)
        #强制将buffer缓存到磁盘
        summary.flush()

