#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace cv::dnn;

tuple<Mat, vector<vector<int>>> getFaceBox(Net net, Mat &frame, double conf_threshold) {
    Mat frameOpenCVDNN = frame.clone();
    int frameHeight=frameOpenCVDNN.rows;
    int frameWidth = frameOpenCVDNN.cols;
    double inScaleFactor = 1.0;
    Size size = Size(300, 300);
    Scalar meanVal = Scalar(104, 117, 123);
    Mat inputBlob = blobFromImage(frameOpenCVDNN, inScaleFactor, size, meanVal, true, false);
    net.setInput(inputBlob, "data");
    Mat detection = net.forward("detection_output");
    Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());

    vector<vector<int>> bboxs;
    for (int i = 0; i < detectionMat.rows; ++i) {
        float condifence=detectionMat.at<float>(i,2);
        if (condifence > conf_threshold) {
            int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * frameWidth);
            int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * frameHeight);
            int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * frameWidth);
            int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * frameHeight);
            vector<int> box = {x1, y1, x2, y2};
            bboxs.push_back(box);
            rectangle(frameOpenCVDNN, Point(x1, y1), Point(x2, y2), Scalar(0, 255, 0), 2, 4);
        }
    }
    return make_tuple(frameOpenCVDNN, bboxs);
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}