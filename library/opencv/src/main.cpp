#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>

using namespace std;
using namespace cv;
using namespace cv::dnn;

void testMat() {

    //day 3
    Mat img = imread("./timg.jpeg");

    Mat zeros = Mat::zeros(Size(200, 200), CV_8UC3);
    Mat ones = Mat::ones(Size(200, 200), CV_8UC3);
    Mat kernel = (Mat_<char>(3, 3) << 1, 200, 3, 4, 500, 6, 700, 8, 9);
    imwrite("result.jpg", img);
    imwrite("zeros.jpg", zeros);
    imwrite("one.jpg", ones);

    //day 4
    int height = zeros.rows;
    int weight = zeros.cols;
    int chanle = zeros.channels();
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < weight; ++j) {
            if (chanle == 3) {
                Vec3b bgr = zeros.at<Vec3b>(i, j);
                bgr[0] = 255 - bgr[0];
                bgr[1] = 255 - bgr[1];
                bgr[2] = 255 - bgr[2];
                zeros.at<Vec3b>(i, j) = bgr;
            }
        }
    }
    imwrite("revZeros.jpg", zeros);

    //day 5
    Mat add_result = Mat::zeros(zeros.size(), zeros.type());
    add(zeros, zeros, add_result);  //substract multiply divide
    imwrite("add_result.jpg", add_result);
}

void testPix() {
    //day 6 LUT applyColorMap

    int lut[256];
    for (int i = 0; i < 256; ++i) {
        if (i < 20) {
            lut[i] = 0;
        } else {
            lut[i] = 255;
        }
    }
    Mat src = imread("./timg.jpeg", IMREAD_GRAYSCALE);
    Mat srcColor = imread("./timg.jpeg", IMREAD_COLOR);

    imwrite("srcGray.jpg", src);
    Mat LutResult = Mat::zeros(src.size(), src.type());
    Mat mapResult = Mat::zeros(src.size(), src.type());
    Mat Lutmat(1, 256, CV_8UC1, lut);
    LUT(src, Lutmat, LutResult);
    applyColorMap(srcColor, mapResult, COLORMAP_SPRING);
    imwrite("LutResult.jpg", LutResult);
    imwrite("mapResult.jpg", mapResult);

    //day 7 像素位操作
    src = imread("./timg.jpeg");
    Mat dst;
    bitwise_not(src, dst);
//    bitwise_and();
//    bitwise_xor();
//    bitwise_or();
    imwrite("bitNot.jpg", dst);

    // day 8    分离/合并通道
    vector<Mat> mv;
    Mat mergeImage;
    split(src, mv);
    mv[0] = Scalar(0);
    merge(mv, mergeImage);
    imwrite("mergeImage.jpg", mergeImage);

    //day 9 色彩空间转换
    Mat hsv;
    cvtColor(src, hsv, COLOR_BGR2HSV);
//    COLOR_BGR2YUV
//    COLOR_BGR2BGRA
//    COLOR_BGR2YCrCb
    imwrite("hsv.jpg", hsv);
    Mat hsvrange;
    inRange(src, (10, 20, 40), (99, 100, 100), hsvrange);
    imwrite("hsvRange.jpg", hsvrange);

    //day 10 像素统计值
    double minVal, maxval;
    Point minLoc, maxLoc;
    minMaxLoc(src, &minVal);
    cout << minVal << endl;

    Mat means, stddev;
    meanStdDev(src, means, stddev);
    cout<<"mean is"<<means.at<double>(0,0)<<endl;
}

void testImage(){
    // day 13 图片翻转
    Mat src = imread("./timg.jpeg");
    Mat flipx;
    flip(src, flipx, 0);
    imwrite("flipx.jpg", flipx);

    // day 14 图像插值 image interpolation
    int h = src.rows;
    int w = src.cols;
    Mat inter_nearest;
    resize(src, inter_nearest, Size(w * 2, h * 2), 0.0, 0.0, INTER_NEAREST);
    imwrite("inter_nearest.jpg", inter_nearest);

    //day 15 绘制图形
    RNG rng(0xFFFFFFF);
    Mat image(Size(512, 512), CV_8UC3, Scalar(0, 0, 0));
    for (int i = 0; i < 100; ++i) {
        int x1 = rng.uniform(0, 512);
        int y1 = rng.uniform(0, 512);
        int x2 = rng.uniform(0, 512);
        int y2 = rng.uniform(0, 512);

        int b = rng.uniform(0, 256);
        int g = rng.uniform(0, 256);
        int r = rng.uniform(0, 256);

        Rect rect;
        rect.x = x1;
        rect.y = y1;
        rect.width = x2 - x1;
        rect.height = y2 - y1;
        rectangle(image, rect, Scalar(b, g, r), 1, LINE_AA, 0);
        imwrite("rect.jpg", image);

    }

    //day 16 感兴区域（region of interest）ROI

    //day 17 直方图

    //day 18 值方图均衡化
    Mat srcGray;
    cvtColor(src, srcGray, COLOR_BGR2GRAY);
    Mat equalhist;
    equalizeHist(srcGray, equalhist);
    imwrite("equalhist.jpg", equalhist);

    //day 30 自定义滤波器
    Mat afterFilter;
    Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    filter2D(src, afterFilter, -1, kernel);
    imwrite("afterFliter.jpg", afterFilter);

    //day 39 模板匹配
    src = imread("./data/images/llk.jpg");
    Mat tpl = imread("./data/images/llk_tpl.png");
    int result_h = src.rows - tpl.rows + 1;
    int result_w = src.cols - tpl.cols + 1;
    Mat result = Mat::zeros(Size(result_w, result_h), CV_32FC1);
    matchTemplate(src, tpl, result, TM_CCOEFF_NORMED);
    imwrite("result.jpg", result);
    int h2 = result.rows;
    int w2 = result.cols;
    for (int row = 0; row < h2; ++row) {
        for (int col = 0; col < w2; ++col) {
            float v = result.at<float>(row, col);
            if (v > 0.95) {
                rectangle(src, Point(col, row), Point(col + tpl.cols, row + tpl.rows), Scalar(255, 0, 0), 1, 8, 0);

            }
        }
    }
    imwrite("matchResult.jpg", src);
}

void testBinary(){

    //day 42 OTUS
    Mat src = imread("./data/images/lena.png");
    Mat gray, binary,adaptiveBinary;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    double t = threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

    //day 44 自适应阈值
    adaptiveThreshold(gray, adaptiveBinary, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 25, 10);
    imwrite("adaptive.jpg", adaptiveBinary);
    cout << t << endl;
    imwrite("binary.jpg", binary);

    //day 46 连通组件标记
    RNG rng;
    Mat labels = Mat::zeros(src.size(), CV_32S);
    int nums_labels = connectedComponents(binary, labels, 8, CV_32S);

    cout << nums_labels << endl;

    vector<Vec3b> colors(nums_labels);
    colors[0] = Vec3b(0, 0, 0);
    for (int i = 1; i < nums_labels; ++i) {
        colors[i] = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));

    }

    Mat dst = Mat::zeros(src.size(), src.type());
    for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
            int label = labels.at<int>(i, j);
            if(label==0) continue;
            dst.at<Vec3b>(i, j) = colors[label];
        }
    }
    imwrite("connect.jpg", dst);
}

void testContours(){

    //day 48 轮廓
    Mat src = imread("./data/images/coins.jpg");

    Mat dst, gray, binary;
    GaussianBlur(src, dst, Size(3, 3), 0, 0);
    cvtColor(dst, gray, COLOR_BGR2GRAY);
    threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
    imwrite("binarycoin.jpg", binary);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(binary, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());
    for (int i = 0; i < contours.size(); ++i) {
        drawContours(src, contours, i, Scalar(0, 0, 255));
    }
    imwrite("contour.jpg", src);

    //day 49 轮廓外接矩形
    for (int j = 0; j < contours.size(); ++j) {
        Rect rect = boundingRect(contours[j]);
        //RotatedRect rect = minAreaRect(contours[j]);
        rectangle(src, rect, Scalar(0, 0, 0));
    }
    imwrite("contourRect.jpg", src);
}

void testDNN(){
    string model = "./data/models/googlenet/bvlc_googlenet.caffemodel";
    string protxt = "./data/models/googlenet/bvlc_googlenet.prototxt";

    Net net = dnn::readNet(model, protxt);
    vector<string> layer_names = net.getLayerNames();
    for (int i = 0; i < layer_names.size(); ++i) {
        int id = net.getLayerId(layer_names[i]);
        auto layer = net.getLayer(id);
        printf("layer id:%d, type: %s, name:%s \n", id, layer->type.c_str(), layer->name.c_str());
    }
}
vector<String> readClassNames(string labels_txt_file);
void testCaffe(){
    string model = "./data/models/googlenet/bvlc_googlenet.caffemodel";
    string protxt = "./data/models/googlenet/bvlc_googlenet.prototxt";
    string label_txt_file = "./data/models/googlenet/classification_classes_ILSVRC2012.txt";
    vector<string> labels = readClassNames(label_txt_file);

    Mat inputMat = imread("./data/images/flower.png");
    Net net = dnn::readNet(model, protxt);
    net.setPreferableBackend(DNN_BACKEND_OPENCV);
    net.setPreferableTarget(DNN_TARGET_CPU);
//    readNetFromCaffe();
//    readNetFromTensorflow();
//    readNetFromDarknet();
//    readNetFromTorch();

    Mat inputBlob = blobFromImage(inputMat, 1.0, Size(224, 224), Scalar(104, 117, 123));

    net.setInput(inputBlob);
    Mat prob = net.forward();
    cout << prob.size() << endl;
    double classProb;
    Point classLoc;
    minMaxLoc(prob, NULL, &classProb, NULL, &classLoc);
    printf("\n current image classification : %s, possible : %.2f", labels.at(classLoc.x).c_str(), classProb);


}

void testSSD(){
    string model = "./data/models/ssd/MobileNetSSD_deploy.caffemodel";
    string model_text = "./data/models/ssd/MobileNetSSD_deploy.prototxt";
    string model_label = "./data/models/ssd/labelmap_det.txt";
    string objNames[] = { "background",
                          "aeroplane", "bicycle", "bird", "boat",
                          "bottle", "bus", "car", "cat", "chair",
                          "cow", "diningtable", "dog", "horse",
                          "motorbike", "person", "pottedplant",
                          "sheep", "sofa", "train", "tvmonitor" };
    Mat frame = imread("./data/images/dog.jpg");
    Mat blobImage = blobFromImage(frame, 0.007843, Size(300, 300), Scalar(127.5, 127.5, 127.5), true, false);

    //返回对象都是一个四维的Mat对象-按照顺序分别为NCHW 其组织方式详解如下：
    //N表示多张图像
    //C表示接受输入图像的通道数目
    //H表示接受输入图像的高度
    //W表示接受输入图像的宽度
//    返回对象都是一个四维的Mat对象-按照顺序分别为NCHW 其组织方式详解如下：
//    N表示多张图像
//            C表示接受输入图像的通道数目
//    H表示接受输入图像的高度
//            W表示接受输入图像的宽度
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
            putText(frame, format(" confidence %.2f, %s", confidence, objNames[objIndex].c_str()), Point(tl_x - 10, tl_y - 5), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(255, 0, 0), 2, 8);
        }
    }
    imwrite("ssd.jpg", frame);
}

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

void testface(){

    //day 126
    string model = "./data/models/face_detector/opencv_face_detector_uint8.pb";
    string model_text = "./data/models/face_detector/opencv_face_detector.pbtxt";
    Net net = readNetFromTensorflow(model, model_text);
    Mat frame = imread("./data/images/face_01.png");
    Mat blobImages = blobFromImage(frame, 1.0, Size(300, 300), Scalar(104.0, 177.0, 123.0),
                                   false, false);
    net.setInput(blobImages, "data");
    Mat detection = net.forward();
    Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());
    cout << detection.size[2] << endl;
    float confidence_threshold = 0.1;
    for (int i = 0; i < detectionMat.rows; i++) {
        float confidence = detectionMat.at<float>(i, 2);
        if (confidence > confidence_threshold) {
            size_t objIndex = (size_t) (detectionMat.at<float>(i, 1));
            float tl_x = detectionMat.at<float>(i, 3) * frame.cols;
            float tl_y = detectionMat.at<float>(i, 4) * frame.rows;
            float br_x = detectionMat.at<float>(i, 5) * frame.cols;
            float br_y = detectionMat.at<float>(i, 6) * frame.rows;

            Rect object_box((int) tl_x, (int) tl_y, (int) (br_x - tl_x), (int) (br_y - tl_y));
            rectangle(frame, object_box, Scalar(0, 0, 255), 2, 8, 0);
            putText(frame, format(" confidence %.2f, %s", confidence),
                    Point(tl_x - 10, tl_y - 5), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(255, 0, 0), 1, 8);
        }
    }
    imwrite("face.jpg", frame);
}

vector<string> classes;
vector<Vec3b> colors;
void colorizeSegmentation(const Mat &score, Mat &segm);

void testSegNet(){
    //day 134
    string model = "./data/models/enet/model-best.net";
    Mat frame = imread("./data/models/enet/cityscapes_test.jpg");
    Net net = readNetFromTorch(model);
    Mat blob = blobFromImage(frame, 0.000392, Size(1024, 512), Scalar(0, 0, 0), true, false);
    net.setInput(blob);
    Mat score = net.forward();
    Mat segm;
    colorizeSegmentation(score, segm);

}

void colorizeSegmentation(const Mat &score, Mat &segm)
{
    const int chns = score.size[1];
    const int rows = score.size[2];
    const int cols = score.size[3];

    colors.push_back(Vec3b());
    if (colors.empty()) {
        for (int i = 1; i < chns; ++i) {
            Vec3b color;
            for (int j = 0; j < 3; ++j) {
                color[j] = (colors[i - 1][j] + rand() % 256) / 2;
            }
            colors.push_back(color);
        }
    }

    Mat maxCL = Mat::zeros(rows, cols, CV_8UC1);
    Mat maxVal(rows, cols, CV_32FC1, score.data);
    for (int ch = 1; ch < chns; ++ch) {
        for (int row = 0; row < rows; ++row) {
            const float *ptrScore = score.ptr<float>(0, ch, row);
            uint8_t *ptrMaxCl = maxCL.ptr<uint8_t>(row);
            float *ptrMaxVal = maxVal.ptr<float>(row);
            for (int col = 0; col < cols; ++col) {
                if (ptrScore[col] > ptrMaxVal[col]) {
                    ptrMaxVal[col] = ptrScore[col];
                    ptrMaxCl[col] = (uchar) ch;
                }
            }
        }
    }

    segm.create(rows,cols, CV_8UC3);
    for (int row = 0; row < rows; ++row) {
        const uchar *ptrMaxCl = maxCL.ptr<uchar>(row);
        Vec3b *ptrSegm = segm.ptr<Vec3b>(row);
        for (int col = 0; col < cols; col++)
        {
            ptrSegm[col] = colors[ptrMaxCl[col]];
        }
    }
}

void testStyle(){
    string dir = "./data/models/fast_style/";
    String styles[9] = {"composition_vii.t7", "starry_night.t7", "la_muse.t7", "the_wave.t7",
                        "mosaic.t7", "the_scream.t7", "feathers.t7", "candy.t7", "udnie.t7"};
    int index = 0;
    Net net = readNetFromTorch(format("%s%s", dir.c_str(), styles[index].c_str()));
    Mat frame = imread("./data/images/flower.png");
    Mat blobMat = blobFromImage(frame, 1.0, Size(256, 256), Scalar(103.939, 116.779, 123.68), false, false);
    net.setInput(blobMat);
    Mat out = net.forward();
    int ch = out.size[1];
    int h = out.size[2];
    int w = out.size[3];
    Mat result = Mat::zeros(Size(h, w), CV_32FC3);
    float *data = out.ptr<float>();
    for (int c = 0; c < ch; c++) {
        for (int row = 0; row < h; row++) {
            for (int col = 0; col < w; col++) {
                result.at<Vec3f>(row, col)[c] = *data++;
            }
        }
    }
    add(result, Scalar(103.939, 116.779, 123.68), result);
    result /= 255.0;

    // 中值滤波
    medianBlur(result, result, 5);
    Mat dst;
    resize(result, dst, frame.size());
    imwrite("style.jpg", result);
}
int main() {
//    testMat();
//    testPix();
//   testImage();
  //  testBinary()
   // testContours();
    //testDNN();
    //testCaffe();
//    testSSD();
    //testface();
    //testStyle();
    Mat img = imread("./data/images/0001TP_008550.png");
    cout << img.channels() << endl;
    int height = img.rows;
    int weight = img.cols;
    int chanle = img.channels();
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < weight; ++j) {
            Vec3b bgr = img.at<Vec3b>(i, j);
            cout << (float)bgr[0] << (float)bgr[1] << (float)bgr[2] << endl;
        }
    }

    return 0;
}

