//
// Created by user on 2020/7/3.
//

#ifndef FINGERVEIN_MAXCURVATURES_H
#define FINGERVEIN_MAXCURVATURES_H

#include "../util/Common.h"

class MaxCurvatures {
    Mat image;
    Mat veins;
    Mat fingerRegion;
    Mat veinsCenters;
    Mat curvatures;
    Mat trackedVeins;
public:

    MaxCurvatures(const Mat &image);

    MaxCurvatures(const String &image_input);

    static void meshgrid(const Mat &xgv, const Mat &ygv, Mat &X, Mat &Y);

    static void meshgridFromRange(Range &xgv, Range &ygv, Mat &X, Mat &Y);

    Mat generateFilter0(Mat X, Mat Y, int sigma);

    Mat generateFilter1(Mat X, Mat hMat, int sigma);

    Mat generateFilter2(Mat X, Mat hMat, int sigma);

    Mat generateFilter5(Mat X, Mat Y, Mat hMat, int sigma);

    Mat extractFingerRegion(Mat originalImage);

    Mat trackVeinsCentres(Mat curvatures, cv::Size imageSize);

    Mat extractVeinsFromCentres(Mat veinsCenters, Mat fingerRegion);

public:
    Mat extractFingerVeinsMaxCurvature(Mat originalImage, int sigma);

    Mat filterAndCalculateCurvatures(Mat originalImage, Mat fingerRegion, int sigma);

    void show();

    void clear();

    void detectFeature();
};


#endif //FINGERVEIN_MAXCURVATURES_H
