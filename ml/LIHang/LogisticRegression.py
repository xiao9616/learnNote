from math import exp
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split

def create_data():
    iris=load_iris()
    df=pd.DataFrame(iris.data,columns=iris.feature_names)
    df['label']=iris.target
    df.columns=['sepal length','sepal width','petal length','petal width','label']
    data=np.array(df.iloc[:100,[0,1,-1]])
    return data[:,:2],data[:,-1]
class logisticregression:
    def __init__(self,max_iter=200,lr=0.01):
        self.max_iter=max_iter
        self.lr=lr
    def sigmiod(self,x):
        return 1/(1+exp(-x))
    def data_matrix(self,x):
        data_mat=[]
        for d in x:
            data_mat.append([1.0,*d])
        return data_mat

    def fit(self,x,y):
        data_mat=self.data_matrix(x)
        self.weights=np.zeros((len(data_mat[0]),1),dtype=np.float32)

        for iter_ in range(self.max_iter):
            for i in range(len(x)):
                result=self.sigmiod(np.dot(data_mat[i],self.weights))
                error=y[i]-result
                self.weights+=self.lr*error*np.transpose([data_mat[i]])
    def score(self,x_test,y_test):
        right=0
        x_test=self.data_matrix(x_test)
        for x,y in zip(x_test,y_test):
            result=np.dot(x,self.weights)
            if(result>0 and y==1)or(result<0 and y==0):
                right+=1
        return right/len(x_test)
x, y = create_data()
x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.3)
lr_clf=logisticregression()
lr_clf.fit(x_train,y_train)
print(lr_clf.score(x_test,y_test))
