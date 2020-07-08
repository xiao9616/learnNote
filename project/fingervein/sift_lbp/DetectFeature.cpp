//
// Created by user on 2020/6/22.
//

#include "DetectFeature.h"

DetectFeature::DetectFeature(const Mat &image1, const Mat &image2) : image1(image1), image2(image2) {}

DetectFeature::DetectFeature(const String &image1_str, const String &image2_str) : image1_str(image1_str),
                                                                                   image2_str(image2_str) {
    this->image1 = imread(image1_str, IMREAD_GRAYSCALE);
    this->image2 = imread(image2_str, IMREAD_GRAYSCALE);
}

void DetectFeature::compare(const String &featureMethod) {

    if (featureMethod == "surf") {
        surf();
    } else {
        cerr << "can not find " << featureMethod << " method" << endl;
        return;
    }
}

void DetectFeature::surf() {
    Ptr<xfeatures2d::SURF> surf = xfeatures2d::SURF::create();
//    surf->detect(image1, keyPoint1);
//    surf->detect(image2, keyPoint2);

    surf->detectAndCompute(image1, Mat(), keyPoint1, desp1);
    surf->detectAndCompute(image2, Mat(), keyPoint2, desp2);
    if (desp1.type() != CV_32F || desp2.type() != CV_32F) {
        desp1.convertTo(desp1, CV_32F);
        desp2.convertTo(desp2, CV_32F);
    }
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce");
    matcher->match(desp1, desp2, matchs);

    //计算特征点距离的最大值
    double maxDist = 0;
    for (int i = 0; i < desp1.rows; ++i) {
        double dist = matchs[i].distance;
//        cout << matchs[i].queryIdx << " ";
//        cout << matchs[i].trainIdx << " ";
//        cout << matchs[i].distance << endl;
        if (dist > maxDist) {
            maxDist = dist;
        }
    }

    int index1, index2;
    Point2f point1, point2;

    //挑选好的匹配点
    for (int i = 0; i < desp1.rows; ++i) {

        if (matchs[i].distance <= 0.3) {

            index1 = matchs[i].queryIdx;
            index2 = matchs[i].trainIdx;

            point1 = Point2f(keyPoint1[index1].pt.x, keyPoint1[index1].pt.y);
            point2 = Point2f(keyPoint2[index2].pt.x, keyPoint2[index2].pt.y);

            float position = this->nearDistance(point1, point2);
            if (position < 30) {
//                cout << point1.x << " " << point1.y << " " << point2.x << " " << point2.y << " " << position << endl;
                good_matches.push_back(matchs[i]);
            }
        }
    }

    drawKeypoints(image1, keyPoint1, keyPointImage1, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    drawKeypoints(image2, keyPoint2, keyPointImage2, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    drawMatches(image1, keyPoint1, image2, keyPoint2, good_matches, imageOut);
}

void DetectFeature::showResult() {
    namedWindow("key point of image1", WINDOW_FREERATIO);
    namedWindow("key point of image2", WINDOW_FREERATIO);
    namedWindow("picture of matching", WINDOW_FREERATIO);

    imshow("key point of image1", keyPointImage1);
    imshow("key point of image2", keyPointImage2);
    imshow("picture of matching", imageOut);
    waitKey(0);
    return;
}

void DetectFeature::save() {
    imwrite(image1_str, keyPointImage1);
    imwrite(image2_str, keyPointImage2);
    imwrite("./match_result", imageOut);
}

DetectFeature::DetectFeature() {

}

DetectFeature::~DetectFeature() {

}

void DetectFeature::compare(const String &image1_str, const String &image2_str, const String &featureMethod) {
    this->image1 = imread(image1_str, IMREAD_GRAYSCALE);
    this->image2 = imread(image2_str, IMREAD_GRAYSCALE);
    this->image1=this->gabor(this->image1);
    this->image2=this->gabor(this->image2);

    equalizeHist(this->image1, this->image1);
    equalizeHist(this->image2, this->image2);
    this->compare(featureMethod);
}

void DetectFeature::clear() {
    this->good_matches.clear();
}

float DetectFeature::nearDistance(Point2f &point1, Point2f &point2) {

    return sqrtf(powf((point1.x - point2.x), 2) + powf((point1.y - point2.y), 2));
}

Mat DetectFeature::gabor(Mat &im) {
    int theta = 0;
    Mat acc(im.rows, im.cols, CV_8UC1, Scalar(0));
    Mat dist;
    while (theta < 180) {
        Mat kernel = getGaborKernel(Size(gabor_ksize, gabor_ksize), gabor_sigma, theta, gabor_lambd, gabor_gamma,
                                    gabor_psi, CV_32F);
        Mat gabordst;
        float kernelsum = 0;
        for (int i = 0; i < kernel.rows; i++) {
            for (int j = 0; j < kernel.cols; j++) {
                kernelsum += kernel.at<Vec<float, 1>>(i, j)[0];
            }
        }
        kernel /= 1.5 * kernelsum;
        filter2D(im, gabordst, im.depth(), kernel);
        acc = max(acc, gabordst);
        theta += 45;
    }

    Ptr<CLAHE> clahe = createCLAHE(2.0);
    clahe->apply(acc, dist);
    return dist;
}




