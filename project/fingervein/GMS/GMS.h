//
// Created by user on 2020/7/11.
//

#ifndef FINGERVEIN_GMS_H
#define FINGERVEIN_GMS_H


#include "../util/Common.h"

enum KeyPointFeature {
    ORB_FEATURE,
    SURF_FEATURE,
    SIFT_FEATURE
};

class GMS {
private:
    Mat image1;
    Mat image2;
public:
    GMS(const Mat &image1, const Mat &image2);

    GMS(const String &image1_path, const String &image2_path);

    void detection(KeyPointFeature method);

    Mat anisotropy(Mat &image, float k, float lambda);

    void preProcess();
};


#endif //FINGERVEIN_GMS_H
