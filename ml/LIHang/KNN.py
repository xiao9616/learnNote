import math
import numpy as np
import pandas as pd
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from collections import Counter
from sklearn.neighbors import KNeighborsClassifier
from random import random
import time
def L(x, y, p=2):
    if len(x) == len(y) and len(x) > 1:
        sum = 0
        for i in range(len(x)):
            sum += math.pow(x[i] - y[i], p)
        return math.pow(sum, 1 / p)
    else:
        return 0


class knn:
    def __init__(self, x_train, y_train, k=3, p=2):
        self.k = k
        self.p = p
        self.x_train = x_train
        self.y_train = y_train

    def predict(self, x):
        knn_list = []
        for i in range(self.k):
            dist = np.linalg.norm(x - x_train[i], ord=self.p)
            knn_list.append((dist, self.y_train[i]))

        for i in range(self.k, len(self.x_train)):
            max_index = knn_list.index(max(knn_list, key=lambda x: x[0]))
            dist = np.linalg.norm(x - x_train[i], ord=self.p)
            if knn_list[max_index][0] > dist:
                knn_list[max_index] = (dist, self.y_train[i])
        knn = [k[-1] for k in knn_list]
        count_pairs = Counter(knn)
        max_count = sorted(count_pairs.items(), key=lambda x: x[1])[-1][0]
        return max_count

    def score(self, x_test, y_test):
        right = 0
        for x, y in zip(x_test, y_test):
            label = self.predict(x)
            if label == y:
                right += 1
        return right / len(x_test)

# kd_tree
class KdNode(object):
    def __init__(self,dom_elt,split,left,right):
        self.dom_elt=dom_elt
        self.split=split
        self.left=left
        self.right=right

class KdTree(object):
    def __init__(self,data):
        k=len(data[0])
        def CreateNode(splite,data_set):
            if not data_set:
                return None
            data_set.sort(key=lambda x:x[splite])
            splite_position=len(data_set)//2
            median=data_set[splite_position]
            splite_next=(splite+1)%k
            return KdNode(median,splite,
                          CreateNode(splite_next,data_set[:splite_position]),
                          CreateNode(splite_next,data_set[splite_position+1:]))
        self.root=CreateNode(0,data)


def preorder(root):
    print(root.dom_elt)
    if root.left:
        preorder(root.left)
    if root.right:
        preorder(root.right)

from math import sqrt
from collections import namedtuple

result=namedtuple("result_tuple","nearest_point nearest_dist nodes_visited")

def find_nearest(tree,point):
    k=len(point)
    def travel(kd_node,target,max_dist):
        if kd_node is None:
            return result([0]*k,float("inf"),0)
        nodes_visited=1
        s=kd_node.split
        pivot=kd_node.dom_elt
        if target[s]<=pivot[s]:
            near_node=kd_node.left
            further_node=kd_node.right
        else:
            near_node=kd_node.right
            further_node=kd_node.left
        temp1=travel(near_node,target,max_dist)
        nearest=temp1.nearest_point
        dist=temp1.nearest_dist
        nodes_visited+=temp1.nodes_visited

        if dist<max_dist:
            max_dist=dist
        temp_dist=abs(pivot[s]-target[s])
        if max_dist<temp_dist:
            return result(nearest,dist,nodes_visited)

        temp_dist=sqrt(sum((p1-p2)**2 for p1,p2 in zip(pivot,target)))
        if temp_dist<dist:
            nearest=pivot
            dist=temp_dist
            max_dist=dist
        temp2=travel(further_node,target,max_dist)
        nodes_visited+=temp2.nodes_visited
        if temp2.nearest_dist<dist:
            nearest=temp2.nearest_point
            dist=temp2.nearest_dist
        return result(nearest,dist,nodes_visited)
    return travel(tree.root,point,float("inf"))

def random_point(k):
    return [random() for _ in range(k)]


def random_points(k,n):
    return [random_point(k) for _ in range(n)]

if __name__ == '__main__':
    iris = load_iris()
    df = pd.DataFrame(iris.data, columns=iris.feature_names)
    df['label'] = iris.target
    df.columns = ['sepal length', 'sepal width', 'petal length', 'petal width', 'label']
    print(df)

    data = np.array(df.iloc[:, :])
    x, y = data[:, :-1], data[:, -1]
    x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.2)
    print(x, y)

    clk = knn(x_train, y_train)
    score = clk.score(x_test, y_test)
    print(score)

    clk_sk = KNeighborsClassifier()
    clk_sk.fit(x_train, y_train)
    score_sk=clk.score(x_test, y_test)
    print(score_sk)

    N=400000
    t0=time.process_time()
    kd=KdTree(random_points(3,N))
    result=find_nearest(kd,[0.1,0.5,0.8])
    t1=time.process_time()
    print(t1-t0)
    print(result)
