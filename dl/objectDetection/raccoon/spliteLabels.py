# encoding: utf-8

# @author: wenxuan
# @contact: 749935253@qq.com
# @software: PyCharm
# @file: spliteLabels.py
# @time: 19-7-26 下午1:51


import numpy as np
import pandas as pd

full_labels = pd.read_csv("data/raccoon_labels.csv")
gb = full_labels.groupby('filename')
grouped_list = [gb.get_group(i) for i in gb.groups]
train_index = np.random.choice(len(grouped_list), size=160, replace=False)
test_index = np.setdiff1d(list(range(200)), train_index)

train = pd.concat([grouped_list[i] for i in train_index])
test = pd.concat([grouped_list[i] for i in test_index])
train.to_csv("train_labels.csv", index=None)
test.to_csv("test_labels.csv", index=None)
