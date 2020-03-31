import math
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from collections import Counter
from random import random
import time

class perceptron:
    def __init__(self) -> None:
        self.w=np.ones(len(data[0])-1,dtype=np.float32)
        self.b=0
        self.lr=0.1
    def sign(self,x,w,b):
        y=np.dot(x,w)+b
        return y
    def fit(self,x_train,y_train):
        is_wrong=False
        while not is_wrong:
            wrong_count=0
            for d in range(len(x_train)):
                x=x_train[d]
                y=y_train[d]
                if y*self.sign(x,self.w,self.b)<=0:
                    self.w+=self.lr*np.dot(x,y)
                    self.b+=self.lr*y
                    print(self.w)
                    print(self.b)
                    wrong_count+=1
            if wrong_count==0:
                is_wrong=True
        print("Perceptron Model")
        return "Perceptron Model"

if __name__ == '__main__':
    iris = load_iris()
    df = pd.DataFrame(iris.data, columns=iris.feature_names)
    df['label'] = iris.target
    df.columns = ['sepal length', 'sepal width', 'petal length', 'petal width', 'label']
    plt.scatter(df[:50]['sepal length'], df[:50]['sepal width'], label='0')
    plt.scatter(df[50:100]['sepal length'], df[50:100]['sepal width'], label='1')
    plt.xlabel('sepal length')
    plt.ylabel('sepal width')
    plt.legend()
    data = np.array(df.iloc[:100, [0, 1, -1]])
    x, y = data[:, :-1], data[:, -1]
    y = np.array([1 if i == 1 else -1 for i in y])
    perce=perceptron()
    perce.fit(x,y)
    x_points = np.linspace(4, 7, 10)
    y_ = -(perce.w[0] * x_points + perce.b) / perce.w[1]
    plt.plot(x_points, y_)
    plt.show()
