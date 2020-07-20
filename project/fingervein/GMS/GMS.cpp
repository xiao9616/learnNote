//
// Created by user on 2020/7/11.
//

#include "GMS.h"

int N = 20;

void GMS::detection(KeyPointFeature method) {

    bool withRotation = false;
    bool withScale = false;
    bool drawSimple = true;
    Ptr<DescriptorMatcher> matcher;
    vector<KeyPoint> image1_keypoint, image2_keypoint;
    Mat image1_desc, image2_desc;

    if (method == ORB_FEATURE) {
        Ptr<Feature2D> orb = ORB::create(1000);
        orb.dynamicCast<ORB>()->setFastThreshold(20);
        matcher = DescriptorMatcher::create("BruteForce-Hamming");
        orb->detectAndCompute(image1, noArray(), image1_keypoint, image1_desc);
        orb->detectAndCompute(image2, noArray(), image2_keypoint, image2_desc);
    } else if (method == SURF_FEATURE) {
        Ptr<xfeatures2d::SURF> surf = xfeatures2d::SURF::create();
        surf->detectAndCompute(image1, Mat(), image1_keypoint, image1_desc);
        surf->detectAndCompute(image2, Mat(), image2_keypoint, image2_desc);
        matcher = DescriptorMatcher::create("BruteForce");
    } else if (method == SIFT_FEATURE) {
        Ptr<SIFT> surf = SIFT::create();
        surf->detectAndCompute(image1, Mat(), image1_keypoint, image1_desc);
        surf->detectAndCompute(image2, Mat(), image2_keypoint, image2_desc);
        matcher = DescriptorMatcher::create("BruteForce");
    }


    vector<DMatch> matchAll, matchGms;
    matcher->match(image1_desc, image2_desc, matchAll);
    xfeatures2d::matchGMS(image1.size(), image2.size(), image1_keypoint, image1_keypoint, matchAll, matchGms,
                          withRotation, withScale, 3.5);
    std::cout << "matchesGMS: " << matchGms.size() << std::endl;
    Mat frameMatch;
    drawMatches(image1, image1_keypoint, image2, image2_keypoint, matchGms, frameMatch);
    namedWindow("matches GMS", WINDOW_FREERATIO);
    imshow("matches GMS", frameMatch);
    waitKey(0);
}

GMS::GMS(const Mat &image1, const Mat &image2) : image1(image1), image2(image2) {}

GMS::GMS(const String &image1_path, const String &image2_path) {
    image1 = imread(image1_path);
    image2 = imread(image2_path);
}

Mat GMS::anisotropy(Mat &image, float k, float lambda) {
    int width = image.cols;
    int height = image.rows;
    // 四邻域梯度
    float n = 0, s = 0, e = 0, w = 0;
    // 四邻域系数
    float nc = 0, sc = 0, ec = 0, wc = 0;
    float k2 = k * k;
    Mat result = Mat::zeros(image.size(), CV_32F);
    for (int row = 1; row < height - 1; row++) {
        for (int col = 1; col < width - 1; col++) {
            // gradient
            n = image.at<float>(row - 1, col) - image.at<float>(row, col);
            s = image.at<float>(row + 1, col) - image.at<float>(row, col);
            e = image.at<float>(row, col - 1) - image.at<float>(row, col);
            w = image.at<float>(row, col + 1) - image.at<float>(row, col);
            nc = exp(-n * n / k2);
            sc = exp(-s * s / k2);
            ec = exp(-e * e / k2);
            wc = exp(-w * w / k2);
            float value = image.at<float>(row, col) + lambda * (n * nc + s * sc + e * ec + w * wc);
            result.at<float>(row, col) = value;
        }
    }
    return result;
}

void GMS::preProcess() {

    Mat image1_src = this->image1;
    Mat image2_src = this->image2;

    Mat image1_before = Mat::zeros(image1_src.size(), CV_32F);
    Mat image2_before = Mat::zeros(image2_src.size(), CV_32F);
    image1_src.convertTo(image1_before, CV_32F);
    image2_src.convertTo(image2_before, CV_32F);

    Mat image1_after = Mat::zeros(image1_src.size(), CV_32F);
    Mat image2_after = Mat::zeros(image2_src.size(), CV_32F);

    float k = 5;
    int N = 15;
    float lambda = 0.4;

    for (int i = 0; i < N; i++) {
        image1_after = this->anisotropy(image1_before, k, lambda);
        image2_after = this->anisotropy(image2_before, k, lambda);
        image1_after.copyTo(image1_before);
        image2_after.copyTo(image2_before);
    }

    normalize(image1_after, image1_after, 0, 255, NORM_MINMAX);
    normalize(image2_after, image2_after, 0, 255, NORM_MINMAX);
    image1_after.convertTo(image1_after, CV_8UC1);
    image2_after.convertTo(image2_after, CV_8UC1);
    Ptr<CLAHE> clahe = createCLAHE(2.0);
    clahe->apply(image1_after, image1_after);
    clahe->apply(image2_after, image2_after);
    this->image1 = image1_after;
    this->image2 = image2_after;
}
