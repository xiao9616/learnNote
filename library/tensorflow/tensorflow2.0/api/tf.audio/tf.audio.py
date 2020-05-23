# =============================================
# -*- coding: utf-8 -*-           
# @Time    : 2020/5/23 下午3:31    
# @Author  : xiao9616           
# @Email   : 749935253@qq.com   
# @File    : tf.audio.py         
# @Software: PyCharm
# @Discript:
# ============================================
'''
什么是WAV和PCM？
WAV：wav是一种无损的音频文件格式，WAV符合 PIFF(Resource Interchange File Format)规范。所有的WAV都有一个文件头，这个文件头音频流的编码参数。WAV对音频流的编码没有硬性规定，除了PCM之外，还有几乎所有支持ACM规范的编码都可以为WAV的音频流进行编码。

PCM:PCM（Pulse Code Modulation----脉码调制录音)。所谓PCM录音就是将声音等模拟信号变成符号化的脉冲列，再予以记录。PCM信号是由[1]、[0]等符号构成的数字信号，而未经过任何编码和压缩处理。与模拟信号比，它不易受传送系统的杂波及失真的影响。动态范围宽，可得到音质相当好的影响效果。

简单来说：wav是一种无损的音频文件格式，pcm是没有压缩的编码方式。
'''

import tensorflow as tf

wav_tensor=tf.audio.decode_wav(
    contents="wav_path", desired_channels=-1, desired_samples=-1, name=None
)
tf.audio.encode_wav(
    audio=wav_tensor , sample_rate=tf.convert_to_tensor() name=None
)
