# =============================================
# -*- coding: utf-8 -*-           
# @Time    : 2020/5/25 下午4:42    
# @Author  : xiao9616           
# @Email   : 749935253@qq.com   
# @File    : tfboard.py         
# @Software: PyCharm
# @Discript:
# ============================================
from datetime import datetime
import io
import itertools
from six.moves import range

import tensorflow as tf
from tensorflow import keras

import matplotlib.pyplot as plt
import numpy as np

fashion_mnist = keras.datasets.fashion_mnist
(train_images, train_labels), (test_images, test_labels) = \
    fashion_mnist.load_data()

# Names of the integer classes, i.e., 0 -> T-short/top, 1 -> Trouser, etc.
class_names = ['T-shirt/top', 'Trouser', 'Pullover', 'Dress', 'Coat',
    'Sandal', 'Shirt', 'Sneaker', 'Bag', 'Ankle boot']
img = np.reshape(train_images[0], (-1, 28, 28, 1))
logdir = "logs/train_data/" + datetime.now().strftime("%Y%m%d-%H%M%S")
# Creates a file writer for the log directory.
file_writer = tf.summary.create_file_writer(logdir)

# Using the file writer, log the reshaped image.
with file_writer.as_default():
  tf.summary.image("Training data", img, step=0)