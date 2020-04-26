# =============================================
# -*- coding: utf-8 -*-           
# @Time    : 2020/4/26 6:39 下午    
# @Author  : xiao9616           
# @Email   : 749935253@qq.com   
# @File    : util.py         
# @Software: PyCharm
# ============================================
import numpy as np
import os
import glob

root = os.path.dirname(__file__)
ann_dir = os.path.join(root, "data", "ann", "*xml")
ann_fname = glob.glob(ann_dir)


def generator(batch_size, classes, ann_fname):
    pattern_shape = [52, 26, 13]
    anchor_shape = [3, 3]

    n = len(ann_fname)
    i = 0
    while True:
        inputs = []

        y_true = [np.zeros((batch_size, pattern_shape[i], pattern_shape[i], anchor_shape[1], 5 + len(classes))) for i in
                  range(anchor_shape[0])]
        for b in range(batch_size):
            if i == 0:
                np.random.shuffle(ann_fname)
            fname, label, boxes = get_parse(ann_fnames[i])


            i = (i + 1) % n

        yield inputs, y_true
