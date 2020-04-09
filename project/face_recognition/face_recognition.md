# 人脸识别

## 特征检索

提高阈值，会提高准确率（认为是同一个人的情况下判断正确的占比），但会降低查全率（能匹配到的人脸在人脸库中全部匹配人脸的占比），因此需要针对不同的使用场景使用不同的阈值。例如：寻找失踪人口的场景，是宁可找错也不应放过的，阈值就会相应调低，让更多相似的人脸能被看到；在人脸支付场景，准确率是最重要的，那么阈值相应就会较高，当然也会导致匹配失败的次数增多。

把大量人脸特征集中存储可形成特征库，若要判断一个人在不在这个特征库中，只需要拿这个人的人脸照片对应的人脸特征，跟特征库里每个特征计算相似度，把相似度超过阈值的特征对应的照片找出即可。通过一个特征来比对一个特征库的场景，往往称为人脸1:N比对，之对应的两个特征库之间的比对，往往称为人脸M:N比对。

## 人脸图像数据集

[LFW（Labelled Faces in the Wild）](http://vis-www.cs.umass.edu/lfw/)YFW（Youtube Faces in the Wild）SFC（Social Face Classification Dataset）

FDDB 

AFW MALF、IJB-A和Wider Face

## 开源项目

[SeetaFace2](https://github.com/seetafaceengine/SeetaFace2)

[face_recognition](https://github.com/ageitgey/face_recognition)

[dlib](http://dlib.net/)

## 模型

DeepFace

DeepId

FaceNet

FacenessNet

Cascade CNN

LBP && joint Beyesian