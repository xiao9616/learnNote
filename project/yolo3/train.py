# =============================================
# -*- coding: utf-8 -*-           
# @Time    : 2020/4/24 10:20 下午    
# @Author  : xiao9616           
# @Email   : 749935253@qq.com   
# @File    : train.py         
# @Software: PyCharm
# ============================================
import tensorflow as tf
from tensorflow import keras

from tensorflow.keras.models import Model
from tensorflow.keras.layers import Input
from tensorflow.keras.optimizers import Adam
from yolo3.yolo3_Model import yolo3Model
from yolo3.util import generator

num_anchors=3
num_classes=5

model_input = Input(shape=(416, 416, 3))
model_output = yolo3Model(model_input, num_anchors, num_classes)
model = Model(model_input, model_output)
model.summary()
model.compile(optimizer=Adam(lr=1e-3),loss=)
model.fit_generator(generator())
