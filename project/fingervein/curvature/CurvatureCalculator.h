//
// Created by user on 2020/6/13.
//

#ifndef FINGERVEIN_CURVATURECALCULATOR_H
#define FINGERVEIN_CURVATURECALCULATOR_H

#include "../util/Common.h"

class CurvatureCalculator {
    static void meshgrid(const Mat &xgv, const Mat &ygv, Mat &X, Mat &Y);

    static void meshgridFromRange(Range &xgv, Range &ygv, Mat &X, Mat &Y);

    Mat generateFilter0(Mat X, Mat Y, int sigma);

    Mat generateFilter1(Mat X, Mat hMat, int sigma);

    Mat generateFilter2(Mat X, Mat hMat, int sigma);

    Mat generateFilter5(Mat X, Mat Y, Mat hMat, int sigma);

    Mat filterAndCalculateCurvatures(Mat originalImage, Mat fingerRegion, int sigma);


};


#endif //FINGERVEIN_CURVATURECALCULATOR_H
