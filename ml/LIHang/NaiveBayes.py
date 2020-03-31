import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from collections import Counter
import math

def create_data():
    iris=load_iris()
    df=pd.DataFrame(iris.data,columns=iris.feature_names)
    print(df)
    df['label']=iris.target
    print(df)
    df.columns = ['sepal length', 'sepal width', 'petal length', 'petal width', 'label']
    data=np.array(df.iloc[:,:])
    print(data.size)
    return data[:,:-1],data[:,-1]

class navieBaye:
    def __init__(self):
        self.model=None

    @staticmethod
    def mean(x):
        return sum(x)/float(len(x))
    def stdev(self,x):
        avg=self.mean(x)
        return math.sqrt(sum([pow(i-avg,2) for i in x])/float(len(x)))
    def gaussian_probability(self,x,mean,stdev):
        exponent=math.exp(-(math.pow(x-mean,2)/(2*math.pow(stdev,2))))
        return (1/(math.sqrt(2*math.pi)*stdev))*exponent
    def summarize(self,train_data):
        summaries=[(self.mean(i),self.stdev(i)) for i in zip(*train_data)]
        return summaries
    def fit(self,x,y):
        labels=list(set(y))
        data={label:[] for label in labels}
        for f,label in zip(x,y):
            data[label].append(f)
        self.model={
            label:self.summarize(value) for label,value in data.items()
        }
        print("train is done")

    def calculate_probablities(self,input_data):
        probabilities={}
        for label,value in self.model.items():
            probabilities[label]=1
            for i in range(len(value)):
                mean,stdev=value[i]
                probabilities[label]*=self.gaussian_probability(input_data[i],mean,stdev)
        return probabilities
    def predict(self,x_test):
        label=sorted(self.calculate_probablities(x_test).items(),key=lambda x:x[-1])[-1][0]
        return label
    def score(self,x_test,y_test):
        right=0;
        for x,y in zip(x_test,y_test):
            label=self.predict(x)
            if label==y:
                right+=1
        return right/float(len(x_test))
if __name__ == '__main__':
    x,y=create_data()
    x_train,x_test,y_train,y_test=train_test_split(x,y,test_size=0.3)
    model=navieBaye()
    model.fit(x_train,y_train)
    model.calculate_probablities(x_test[0])
    model.predict(x_test[0])
    prediction=model.score(x_test,y_test)
    print(prediction)