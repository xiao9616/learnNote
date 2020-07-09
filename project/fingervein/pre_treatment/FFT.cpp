//
// Created by user on 2020/7/2.
//

#include "FFT.h"

FFT::FFT(const String &imageInput) {
    image_input = imread(imageInput, IMREAD_GRAYSCALE);
}

void FFT::show() {
    namedWindow("idft");
    imshow("idft", this->image_output);
}

void FFT::process() {
    if (image_input.empty()) {
        cerr << "read image error" << endl;
    }
    int m = getOptimalDFTSize(image_input.rows);
    int n = getOptimalDFTSize(image_input.cols);

    Mat padded;
    copyMakeBorder(this->image_input, padded, 0, m - image_input.rows, 0, n - image_input.cols, BORDER_CONSTANT,
                   Scalar::all(0));
    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat planes_true = Mat_<float>(padded);

    Mat complexImg;
    merge(planes, 2, complexImg);
    dft(complexImg, complexImg);
    split(complexImg, planes);
    magnitude(planes[0], planes[1], planes_true);
    Mat A = planes[0];
    Mat B = planes[1];
    Mat mag = planes_true;
    mag += Scalar::all(1);
    log(mag, mag);
    for (int i = 0; i < mag.rows; ++i) {
        for (int j = 0; j < mag.cols; ++j) {
            float num = mag.at<float>(i, j);
//            if (num > 13.5) {
//                planes[0].at<float>(i, j) = 0;
//                planes[1].at<float>(i, j) = 0;
//            }
        }
    }
    merge(planes, 2, complexImg);
    //crop the spectrum, if it has an odd number of rows or columns
    //修剪频谱,如果图像的行或者列是奇数的话,那其频谱是不对称的,因此要修剪
    //这里为什么要用  &-2这个操作，我会在代码后面的 注2 说明
    //我们知道x&-2代表x与 - 2按位相与，而 - 2的二进制形式是2的二进制取反加一的结果（这是补码的问题）。2 的二进制结果是（假设
    //8位表示，实际整型是32位，但是描述方式是一样的，为便于描述，用8位表示）0000 0010，则 - 2的二进制形式为：1111 1110，
    //x与 - 2按位相与后，不管x是奇数还是偶数，最后x都会变成一个偶数。
    //就是说dft这个函数虽然对于输入mat的尺寸不做要求，但是如果其行数和列数可以分解为2、3、5的乘积，那么对于dft运算的速度会加快很多。
    mag = mag(Rect(0, 0, mag.cols & -2, mag.rows & -2));
    Mat _magI = mag.clone();
    //这一步的目的仍然是为了显示,但是幅度值仍然超过可显示范围[0,1],我们使用 normalize() 函数将幅度归一化到可显示范围。
    normalize(_magI, _magI, 0, 1, NORM_MINMAX);
    namedWindow("before rearrange", WINDOW_FREERATIO);
    imshow("before rearrange", _magI);

    int cx = mag.cols / 2;
    int cy = mag.rows / 2;

    //这里是以中心为标准，把mag图像分成四部分
    Mat tmp;
    Mat q0(mag, Rect(0, 0, cx, cy));   //Top-Left - Create a ROI per quadrant
    Mat q1(mag, Rect(cx, 0, cx, cy));  //Top-Right
    Mat q2(mag, Rect(0, cy, cx, cy));  //Bottom-Left
    Mat q3(mag, Rect(cx, cy, cx, cy)); //Bottom-Right

    //swap quadrants(Top-Left with Bottom-Right)，交换象限
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    // swap quadrant (Top-Rightwith Bottom-Left)，交换象限
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    normalize(mag, mag, 0, 1, NORM_MINMAX);
    namedWindow("Input Image", 0);
    namedWindow("spectrum magnitude", 0);
    imshow("Input Image", this->image_input);
    imshow("spectrum magnitude", mag);
    cv::waitKey(0);
}
