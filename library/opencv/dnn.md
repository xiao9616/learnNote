# OpenCV中DNN模块的使用

[TOC]

## 1.简介

opencv现在支持以下框架的训练模型的前馈网络:

Caffe Tensorflow PyTorch DLDT Darknet

加载模型的通用API为：

```
Net readNet(const String& model, 
			const String& config = "", 
			const String& framework = "");
```

其中model为二进制训练好的网络权重文件，支持的后缀为：

```
.caffemodel(Caffe)
.pb(TensorFLow)
.t7|.net(Torch)
.weights(Darknet)
.bin(DLDT)
```

其中config针对模型二进制的描述文件，描述网络结构，支持后缀为：

```
.prototxt(Caffe)
.pbtxt(TensorFlow)
.cfg(Darknet)
.xml(DLDT)
```

framework显示声明参数，说明模型使用哪个框架训练出来的

example：读取一个网络模型，读取各层参数

```c++
string model = "./data/models/googlenet/bvlc_googlenet.caffemodel";
string protxt = "./data/models/googlenet/bvlc_googlenet.prototxt";

Net net = dnn::readNet(model, protxt);
vector<string> layer_names = net.getLayerNames();
for (int i = 0; i < layer_names.size(); ++i) {
    int id = net.getLayerId(layer_names[i]);
    auto layer = net.getLayer(id);
    printf("layer id:%d, type: %s, name:%s \n", id, layer->type.c_str(), layer->name.c_str());
}
```

## 2.模型的使用

### 2.1实现图像分类

读取模型

```
Net readNetFromCaffe(const String& model, 
					 const String& config = "");
```

使用模型实现预测的时候，需要读取图像作为输入，网络模型支持的输入数据是四维的输入，所以要把读取到的Mat对象转换为四维张量，OpenCV的提供的API为如下：

```
Mat cv::dnn::blobFromImage(
	InputArray 	image,	//输入图像
	double 	scalefactor = 1.0,
	const Size & 	size = Size(), //表示网络接受的数据大小
	const Scalar & 	mean = Scalar(),	//表示训练时数据集的均值
	bool 	swapRB = false,	//是否互换Red与Blur通道
	bool 	crop = false,	//剪切
	int 	ddepth = CV_32F 	//数据类型
)
```

example:

```
string model = "./data/models/googlenet/bvlc_googlenet.caffemodel";
string protxt = "./data/models/googlenet/bvlc_googlenet.prototxt";
string label_txt_file = "./data/models/googlenet/classification_classes_ILSVRC2012.txt";
vector<string> labels = readClassNames(label_txt_file);

Mat inputMat = imread("./data/images/flower.png");
Net net = dnn::readNet(model, protxt);
Mat inputBlob = blobFromImage(inputMat, 1.0, Size(224, 224), Scalar(104, 117, 123));

net.setInput(inputBlob);
Mat prob = net.forward();
cout << prob.size() << endl;
double classProb;
Point classLoc;
minMaxLoc(prob, NULL, &classProb, NULL, &classLoc);
printf("\n current image classification : %s, possible : %.2f", 		
labels.at(classLoc.x).c_str(), classProb);

std::vector<String> readClassNames(string labels_txt_file)
{
    std::vector<String> classNames;

    std::ifstream fp(labels_txt_file);
    if (!fp.is_open())
    {
        printf("could not open file...\n");
        exit(-1);
    }
    std::string name;
    while (!fp.eof())
    {
        std::getline(fp, name);
        if (name.length())
            classNames.push_back(name);
    }
    fp.close();
    return classNames;
}
```

同理可以使用其他接口，载入不同框架的模型

```
readNetFromCaffe();
readNetFromTensorflow();
readNetFromDarknet();
readNetFromTorch();
```

### 2.2设置目标运行设备与后台

在加载完网络模型后可以设置计算后台与计算目标设备

```
cv::dnn::Net::setPreferableBackend( int backendId )
```

backendId 表示后台计算id：
-	DNN_BACKEND_DEFAULT (DNN_BACKEND_INFERENCE_ENGINE)表示默认使用intel的预测推断库(需要下载安装Intel® OpenVINO™ toolkit， 然后重新编译OpenCV源码，在CMake时候enable该选项方可)， 可加速计算！
-	DNN_BACKEND_OPENCV 一般情况都是使用opencv dnn作为后台计算

```
void cv::dnn::Net::setPreferableTarget( int targetId )
```

targetId表示目标设备id：

-	DNN_TARGET_CPU其中表示使用CPU计算，默认是的
-	DNN_TARGET_OPENCL 表示使用OpenCL加速，一般情况速度都很扯
-	DNN_TARGET_OPENCL_FP16 可以尝试
-	DNN_TARGET_MYRIAD 树莓派上的

```
Net net = dnn::readNet(model, protxt);
net.setPreferableBackend(DNN_BACKEND_OPENCV);
net.setPreferableTarget(DNN_TARGET_CPU);
```

### 2.3实现目标检测

```
string model = "./data/models/ssd/MobileNetSSD_deploy.caffemodel";
string model_text = "./data/models/ssd/MobileNetSSD_deploy.prototxt";
string model_label = "./data/models/ssd/labelmap_det.txt";
String objNames[] = { "background",
                        "aeroplane", "bicycle", "bird", "boat",
                        "bottle", "bus", "car", "cat", "chair",
                        "cow", "diningtable", "dog", "horse",
                        "motorbike", "person", "pottedplant",
                        "sheep", "sofa", "train", "tvmonitor" };
Mat frame = imread("./data/images/dog.jpg");
Mat blobImage = blobFromImage(frame, 0.007843, Size(300, 300), Scalar(127.5, 127.5, 127.5), true, false);

Net net = readNetFromCaffe(model_text, model);
net.setInput(blobImage, "data");
Mat detection = net.forward();

Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());
cout << detection.size[2] << endl;
float confidence_threshold = 0.1;
for (int i = 0; i < detectionMat.rows; i++) {
    float confidence = detectionMat.at<float>(i, 2);
    if (confidence > confidence_threshold) {
        size_t objIndex = (size_t)(detectionMat.at<float>(i, 1));
        float tl_x = detectionMat.at<float>(i, 3) * frame.cols;
        float tl_y = detectionMat.at<float>(i, 4) * frame.rows;
        float br_x = detectionMat.at<float>(i, 5) * frame.cols;
        float br_y = detectionMat.at<float>(i, 6) * frame.rows;

        Rect object_box((int)tl_x, (int)tl_y, (int)(br_x - tl_x), (int)(br_y - tl_y));
        rectangle(frame, object_box, Scalar(0, 0, 255), 2, 8, 0);
        putText(frame, format(" confidence %.2f, %s", confidence, objNames[objIndex].c_str()), 									Point(tl_x - 10, tl_y - 5), FONT_HERSHEY_SIMPLEX, 0.7, 											Scalar(255, 0, 0), 2, 8);
    }
}
imwrite("ssd.jpg", frame);
```

