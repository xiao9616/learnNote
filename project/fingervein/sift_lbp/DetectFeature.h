//
// Created by user on 2020/6/22.
//

#ifndef FINGERVEIN_DETECTFEATURE_H
#define FINGERVEIN_DETECTFEATURE_H

#include "../util/Common.h"

#define gabor_ksize  31
#define gabor_sigma  3.3
#define gabor_lambd  18.3
#define gabor_gamma  4.5
#define gabor_psi  0.89


class DetectFeature {

private:

    Mat image1, image2;

    String image1_str, image2_str;

    vector<KeyPoint> keyPoint1, keyPoint2;

    Mat desp1, desp2;

    vector<DMatch> matchs;
public:
    vector<DMatch> good_matches;

    Mat keyPointImage1, keyPointImage2, imageOut;

public:

    virtual ~DetectFeature();

    DetectFeature();

    void clear();
    DetectFeature(const Mat &image1, const Mat &image2);

    DetectFeature(const String &image1_str, const String &image2_str);

    void compare(const String &featureMethod);

    void compare(const String &image1_str, const String &image2_str,const String &featureMethod);

    void surf();

    void showResult();

    float nearDistance(Point2f &point1, Point2f &point2);

    Mat gabor(Mat &im);

    void save();

};


#endif //FINGERVEIN_DETECTFEATURE_H
