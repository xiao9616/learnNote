//
// Created by user on 2020/7/3.
//

#include "MaxCurvatures.h"

MaxCurvatures::MaxCurvatures(const String &image_input) {
    this->image = imread(image_input, IMREAD_GRAYSCALE);
    cout << image_input << endl;
}

MaxCurvatures::MaxCurvatures(const Mat &image) : image(image) {}

void MaxCurvatures::meshgrid(const Mat &xgv, const Mat &ygv, Mat &X, Mat &Y) {
    cv::repeat(xgv.reshape(1, 1), ygv.total(), 1, X);
    cv::repeat(ygv.reshape(1, 1).t(), 1, xgv.total(), Y);
}

void MaxCurvatures::meshgridFromRange(Range &xgv, Range &ygv, Mat &X, Mat &Y) {
    std::vector<int> t_x, t_y;
    for (int i = xgv.start; i <= xgv.end; i++) t_x.push_back(i);
    for (int i = ygv.start; i <= ygv.end; i++) t_y.push_back(i);
    meshgrid(cv::Mat(t_x), cv::Mat(t_y), X, Y);
}

Mat MaxCurvatures::generateFilter0(Mat X, Mat Y, int sigma) {
    Mat xSqr, ySqr;
    pow(X, 2, xSqr);
    pow(Y, 2, ySqr);

    auto factor1 = 1 / (2 * M_PI * sigma * sigma);
    auto factor2 = 2 * sigma * sigma;

    Mat xy = xSqr + ySqr;
    Mat negated = -xy;
    Mat divided = negated / factor2;
    Mat exponent = divided;
    exp(divided, exponent);
    Mat result = exponent * factor1;

    return result;
}

Mat MaxCurvatures::generateFilter1(Mat X, Mat hMat, int sigma) {
    Mat copy = X.clone();
    copy = -copy;
    copy = copy / (sigma * sigma);
    Mat result(copy.size(), copy.type());
    multiply(copy, hMat, result);
    return result;
}

Mat MaxCurvatures::generateFilter2(Mat X, Mat hMat, int sigma) {
    Mat xSqr;
    pow(X, 2, xSqr);
    xSqr = xSqr - (sigma * sigma);
    xSqr = xSqr / (sigma * sigma * sigma * sigma);
    Mat result(xSqr.size(), xSqr.type());
    multiply(xSqr, hMat, result);
    return result;
}

Mat MaxCurvatures::generateFilter5(Mat X, Mat Y, Mat hMat, int sigma) {
    Mat result;
    multiply(X, Y, result);

    result = result / (sigma * sigma * sigma * sigma);

    multiply(result, hMat, result);
    return result;
}

Mat MaxCurvatures::extractFingerRegion(Mat originalImage) {
    auto maskHeight = 24;
    auto maskWidth = 32;

    auto imgHeigth = originalImage.size().height;
    auto imgWidth = originalImage.size().width;

    auto halfImgHeight = 0;

    if (imgHeigth % 2 == 0)
        halfImgHeight = (imgHeigth / 2) + 1;
    else
        halfImgHeight = ceil(imgHeigth / 2);

    Mat mask(maskHeight, maskWidth, originalImage.type(), DATA_TYPE(0));

    for (auto i = 0; i < mask.cols; i++) {
        for (auto j = 0; j < mask.rows; j++) {
            if (j < maskHeight / 2)
                mask.at<DATA_TYPE>(j, i) = -1;
            else
                mask.at<DATA_TYPE>(j, i) = 1;
        }
    }

    Mat filteredImage;
    auto anchor = Point(-1, -1);
    auto delta = 0;

    cv::filter2D(originalImage, filteredImage, originalImage.type(), mask, anchor, delta, BORDER_REPLICATE);

    Mat imgFiltUp(floor(imgHeigth / 2), imgWidth, originalImage.type(), DATA_TYPE(0));
    Mat imgFiltLow(halfImgHeight, imgWidth, originalImage.type(), DATA_TYPE(0));

    auto yUp = std::vector<int>();
    for (auto i = 0; i < imgFiltUp.cols; i++) {
        auto currentMax = std::numeric_limits<DATA_TYPE>::min();
        auto currentMaxIndex = -1;
        for (auto j = 0; j < imgFiltUp.rows; j++) {
            auto val = filteredImage.at<DATA_TYPE>(j, i);
            if (val > currentMax) {
                currentMax = val;
                currentMaxIndex = j;
            }
        }
        yUp.push_back(currentMaxIndex);
    }

    auto yLow = std::vector<int>();
    for (auto i = 0; i < imgFiltLow.cols; i++) {
        auto currentMin = std::numeric_limits<DATA_TYPE>::max();
        auto currentMinIndex = -1;
        for (auto j = 0; j < imgFiltLow.rows; j++) {
            auto val = filteredImage.at<DATA_TYPE>(j, i);
            if (val < currentMin) {
                currentMin = val;
                currentMinIndex = j;
            }
        }
        yLow.push_back(currentMinIndex);
    }

    Mat region(originalImage.size(), originalImage.type(), DATA_TYPE(0));

    for (auto i = 0; i < region.cols; i++) {
        for (auto j = 0; j < region.rows; j++) {
            if (j >= yUp[i] && j <= (yLow[i] + imgFiltLow.size().height - 1))
                region.at<DATA_TYPE>(j, i) = 1;
            else
                region.at<DATA_TYPE>(j, i) = 0;
        }
    }
    return region;
}

Mat MaxCurvatures::trackVeinsCentres(Mat curvatures, cv::Size imageSize) {
    Mat centers(imageSize, curvatures.type());
    int wr = 0;
    DATA_TYPE scr = 0;

    for (auto x = 0; x < imageSize.height; x++) {
        for (auto y = 0; y < imageSize.width; y++) {
            if (curvatures.at<DATA_TYPE>(x, y, 0) > 0)
                wr++;

            if (wr > 0 &&
                (y == imageSize.width - 1 || (curvatures.at<DATA_TYPE>(x, y, 0) <= 0))) {
                int pos_end;
                if (y == imageSize.width - 1)
                    pos_end = y;
                else
                    pos_end = y - 1;

                int pos_start = pos_end - wr + 1;

                int index = 0;
                DATA_TYPE maxValue = std::numeric_limits<DATA_TYPE>::min();

                for (auto i = pos_start; i <= pos_end; i++) {
                    auto currentValue = curvatures.at<DATA_TYPE>(x, i, 0);
                    if (currentValue > maxValue) {
                        maxValue = currentValue;
                        index = i - pos_start;
                    }
                }

                int pos_max = pos_start + index - 1;
                scr = curvatures.at<DATA_TYPE>(x, pos_max, 0) * wr;
                centers.at<DATA_TYPE>(x, pos_max) += scr;
                wr = 0;
            }
        }
    }

    for (auto y = 0; y < imageSize.width; y++) {
        for (auto x = 0; x < imageSize.height; x++) {
            if (curvatures.at<DATA_TYPE>(x, y, 1) > 0)
                wr++;

            if (wr > 0 &&
                (x == imageSize.height - 1 || (curvatures.at<DATA_TYPE>(x, y, 1) <= 0))) {
                int pos_end;
                if (x == imageSize.height - 1)
                    pos_end = x;
                else
                    pos_end = x - 1;

                int pos_start = pos_end - wr + 1;

                int index = 0;
                DATA_TYPE maxValue = std::numeric_limits<DATA_TYPE>::min();

                for (auto i = pos_start; i <= pos_end; i++) {
                    auto currentValue = curvatures.at<DATA_TYPE>(i, y, 1);
                    if (currentValue > maxValue) {
                        maxValue = currentValue;
                        index = i - pos_start;
                    }
                }

                int pos_max = pos_start + index - 1;
                scr = curvatures.at<DATA_TYPE>(pos_max, y, 1) * wr;
                centers.at<DATA_TYPE>(pos_max, y) += scr;
                wr = 0;
            }
        }
    }

    for (auto start = 0; start < imageSize.height + imageSize.width - 1; start++) {
        int x, y;

        if (start < imageSize.width) {
            x = start;
            y = 0;
        } else {
            x = 0;
            y = start - imageSize.width + 1;
        }

        while (true) {
            if (curvatures.at<DATA_TYPE>(y, x, 2) > 0)
                wr++;

            if (wr > 0 &&
                (y == imageSize.height - 1 || x == imageSize.width - 1 ||
                 curvatures.at<DATA_TYPE>(y, x, 2) <= 0)) {
                int pos_x_end, pos_y_end;
                if (y == imageSize.height - 1 || x == imageSize.width - 1) {
                    pos_x_end = x;
                    pos_y_end = y;
                } else {
                    pos_x_end = x - 1;
                    pos_y_end = x - 1;
                }
                int pos_x_start = pos_x_end - wr + 1;
                int pos_y_start = pos_y_end - wr + 1;

                int index = 0;
                DATA_TYPE maxValue = std::numeric_limits<DATA_TYPE>::min();

                for (int i = pos_y_start, j = pos_x_start;
                     i <= pos_y_end && j <= pos_x_end; i++, j++) {
                    auto currentValue = curvatures.at<DATA_TYPE>(i, j, 2);
                    if (currentValue > maxValue) {
                        maxValue = currentValue;
                        index = i - pos_y_start;
                    }
                }

                int pos_x_max = pos_x_start + index - 1;
                int pos_y_max = pos_y_start + index - 1;
                scr = curvatures.at<DATA_TYPE>(pos_y_max, pos_x_max, 2) * wr;
                centers.at<DATA_TYPE>(pos_y_max, pos_x_max) += scr;
                wr = 0;
            }


            if ((x == imageSize.width - 1) || (y == imageSize.height - 1)) {
                break;
            } else {
                x++;
                y++;
            }
        }

    }

    for (auto start = 0; start < imageSize.height + imageSize.width - 1; start++) {
        int x, y;

        if (start < imageSize.width) {
            x = start;
            y = imageSize.height;
        } else {
            x = 0;
            y = imageSize.width + imageSize.height - start;
        }

        while (true) {
            if (curvatures.at<DATA_TYPE>(y, x, 3) > 0)
                wr++;

            if (wr > 0 &&
                (y == 0 || (x == imageSize.width - 1) ||
                 (curvatures.at<DATA_TYPE>(y, x, 3) <= 0))) {
                int pos_x_end, pos_y_end;
                if (y == 0 || x == imageSize.width - 1) {
                    pos_x_end = x;
                    pos_y_end = y;
                } else {
                    pos_x_end = x - 1;
                    pos_y_end = y + 1;
                }
                int pos_x_start = pos_x_end - wr + 1;
                int pos_y_start = pos_y_end + wr - 1;

                int index = 0;
                DATA_TYPE maxValue = std::numeric_limits<DATA_TYPE>::min();

                assert(pos_y_start >= pos_y_end);
                assert(pos_x_end >= pos_x_start);

                for (int i = pos_y_end, j = pos_x_start;
                     i <= pos_y_start && j <= pos_x_end; i++, j++) {
                    auto currentValue = curvatures.at<DATA_TYPE>(i, j, 3);
                    if (currentValue > maxValue) {
                        maxValue = currentValue;
                        index = i - pos_y_end;
                    }
                }

                int pos_x_max = pos_x_start + index - 1;
                int pos_y_max = pos_y_start - index + 1;
                scr = curvatures.at<DATA_TYPE>(pos_y_max, pos_x_max, 3) * wr;
                centers.at<DATA_TYPE>(pos_y_max, pos_x_max) += scr;
                wr = 0;
            }

            assert(x < imageSize.width);
            assert(y >= 0);

            if ((x == imageSize.width - 1) || (y == 0)) {
                break;
            } else {
                x++;
                y--;
            }
        }
    }

    return centers;
}

Mat MaxCurvatures::extractVeinsFromCentres(Mat veinsCenters, Mat fingerRegion) {
    Size imageSize = veinsCenters.size();
    Mat veins = Mat::zeros(imageSize, veinsCenters.type());

    for (auto x = 2; x < imageSize.width - 2; x++) {
        for (auto y = 2; y < imageSize.height - 2; y++) {
            auto c1 = min(max(veinsCenters.at<DATA_TYPE>(y, x + 1), veinsCenters.at<DATA_TYPE>(y, x + 2)),
                          max(veinsCenters.at<DATA_TYPE>(y, x - 1), veinsCenters.at<DATA_TYPE>(y, x - 2)));
            auto c2 = min(max(veinsCenters.at<DATA_TYPE>(y + 1, x), veinsCenters.at<DATA_TYPE>(y + 2, x)),
                          max(veinsCenters.at<DATA_TYPE>(y - 1, x), veinsCenters.at<DATA_TYPE>(y - 2, x)));
            auto c3 = min(max(veinsCenters.at<DATA_TYPE>(y - 1, x - 1), veinsCenters.at<DATA_TYPE>(y - 2, x - 2)),
                          max(veinsCenters.at<DATA_TYPE>(y + 1, x + 1), veinsCenters.at<DATA_TYPE>(y + 2, x + 2)));
            auto c4 = min(max(veinsCenters.at<DATA_TYPE>(y + 1, x - 1), veinsCenters.at<DATA_TYPE>(y + 2, x - 2)),
                          max(veinsCenters.at<DATA_TYPE>(y - 1, x + 1), veinsCenters.at<DATA_TYPE>(y - 2, x + 2)));

            veins.at<DATA_TYPE>(y, x) = max(max(c1, c2), max(c3, c4));
        }
    }

    for (auto x = 0; x < imageSize.width; x++) {
        for (auto y = 0; y < imageSize.height; y++) {
            if (abs(fingerRegion.at<DATA_TYPE>(y, x)) == 0)
                veins.at<DATA_TYPE>(y, x) = DATA_TYPE(0);
        }
    }

    return veins;
}

Mat MaxCurvatures::extractFingerVeinsMaxCurvature(Mat originalImage, int sigma) {
    fingerRegion = extractFingerRegion(originalImage);
    curvatures = filterAndCalculateCurvatures(originalImage, fingerRegion, sigma);
    trackedVeins = trackVeinsCentres(curvatures, originalImage.size());
    return extractVeinsFromCentres(trackedVeins, fingerRegion);
}

void MaxCurvatures::show() {
    namedWindow("finger region", WINDOW_AUTOSIZE);
    imshow("finger region", fingerRegion);
    namedWindow("tracked veins", WINDOW_AUTOSIZE);
    imshow("tracked veins", trackedVeins);
    namedWindow("extracted veins", WINDOW_AUTOSIZE);    // Create a window for display.
    imshow("extracted veins", veins);                   // Show our image inside it.
    namedWindow("initial image", WINDOW_AUTOSIZE);
    imshow("initial image", image);
    waitKey(0);
}

void MaxCurvatures::clear() {
    image.release();
    veins.release();
    fingerRegion.release();
    veinsCenters.release();
    curvatures.release();
    trackedVeins.release();
}

void MaxCurvatures::detectFeature() {
    double scale = (double) 1 / 255;
    equalizeHist(image, image);
//    Ptr<CLAHE> clahe = createCLAHE(2.0);
//    clahe->apply(image, image);

    Mat temp;
    image.convertTo(temp, -1, 0.65, 0);
    cv::GaussianBlur(temp, temp, cv::Size(0, 0), 3);
    cv::addWeighted(image, 1.5, temp, -1.10, 0, temp);
    image = temp;
    image.convertTo(image, IMAGE_TYPE, scale);
//    resize(image, image, cv::Size(390, image.size().height / 2));

    auto sigma = 3;
    veins = extractFingerVeinsMaxCurvature(image, sigma);
    for (auto i = 0; i < veins.rows; i++) {
        for (auto j = 0; j < veins.cols; j++) {
            auto val = veins.at<DATA_TYPE>(i, j);
            if (val >= DATA_TYPE(0.01))
                veins.at<DATA_TYPE>(i, j) = DATA_TYPE(1);
            else if (val < DATA_TYPE(0))
                veins.at<DATA_TYPE>(i, j) = DATA_TYPE(0);
        }
    }
    namedWindow("veins");
    imshow("veins", veins);
    waitKey(0);
}

Mat MaxCurvatures::filterAndCalculateCurvatures(Mat originalImage, Mat fingerRegion, int sigma) {
    auto winsize = ceil(4 * sigma);
    Mat X, Y;
    Range range1 = Range(-winsize, winsize);
    Range range2 = Range(-winsize, winsize);
    meshgridFromRange(range1, range2, X, Y);

    X.convertTo(X, originalImage.type());
    Y.convertTo(Y, originalImage.type());

    auto hMat = generateFilter0(X, Y, sigma);

    auto hxMat = generateFilter1(X, hMat, sigma);

    auto hxxMat = generateFilter2(X, hMat, sigma);

    Mat hyMat, hyyMat;

    transpose(hxMat, hyMat);
    transpose(hxxMat, hyyMat);

    auto hxyMat = generateFilter5(X, Y, hMat, sigma);

    //Actual filtering

    Mat fx, fxx, fy, fyy, fxy;
    auto anchor = Point(-1, -1);
    auto delta = 0;

    cv::filter2D(originalImage, fx, originalImage.type(), hxMat, anchor, delta, BORDER_REPLICATE);
    cv::filter2D(originalImage, fxx, originalImage.type(), hxxMat, anchor, delta, BORDER_REPLICATE);
    cv::filter2D(originalImage, fy, originalImage.type(), hyMat, anchor, delta, BORDER_REPLICATE);
    cv::filter2D(originalImage, fyy, originalImage.type(), hyyMat, anchor, delta, BORDER_REPLICATE);
    cv::filter2D(originalImage, fxy, originalImage.type(), hxyMat, anchor, delta, BORDER_REPLICATE);

    Mat f1 = 0.5 * sqrt(2) * (fx + fy);
    Mat f2 = 0.5 * sqrt(2) * (fx - fy);
    Mat f11 = 0.5 * fxx + fxy + 0.5 * fyy;
    Mat f22 = 0.5 * fxx - fxy + 0.5 * fyy;

    int sizes[] = {originalImage.rows, originalImage.cols, 4};

    Mat k(3, sizes, originalImage.type(), Scalar(DATA_TYPE(0)));

    Mat fxSqr, k1result;
    pow(fx, 2, fxSqr);
    fxSqr = fxSqr + 1;
    pow(fxSqr, DATA_TYPE(3 / 2), fxSqr);
    divide(fxx, fxSqr, k1result);
    multiply(k1result, fingerRegion, k1result);

    for (auto i = 0; i < originalImage.rows; i++) {
        for (auto j = 0; j < originalImage.cols; j++) {
            k.at<DATA_TYPE>(i, j, 0) = k1result.at<DATA_TYPE>(i, j);
        }
    }

    Mat fySqr, k2result;
    pow(fy, 2, fySqr);
    fySqr = fySqr + 1;
    pow(fySqr, DATA_TYPE(3 / 2), fySqr);
    divide(fyy, fySqr, k2result);
    multiply(k2result, fingerRegion, k2result);

    for (auto i = 0; i < originalImage.rows; i++) {
        for (auto j = 0; j < originalImage.cols; j++) {
            k.at<DATA_TYPE>(i, j, 1) = k2result.at<DATA_TYPE>(i, j);
        }
    }

    Mat f1Sqr, k3result;
    pow(f1, 2, f1Sqr);
    f1Sqr = f1Sqr + 1;
    pow(f1Sqr, DATA_TYPE(3 / 2), f1Sqr);
    divide(f11, f1Sqr, k3result);
    multiply(k3result, fingerRegion, k3result);

    for (auto i = 0; i < originalImage.rows; i++) {
        for (auto j = 0; j < originalImage.cols; j++) {
            k.at<DATA_TYPE>(i, j, 2) = k3result.at<DATA_TYPE>(i, j);
        }
    }

    Mat f2Sqr, k4result;
    pow(f2, 2, f2Sqr);
    f2Sqr = f2Sqr + 1;
    pow(f2Sqr, DATA_TYPE(3 / 2), f2Sqr);
    divide(f22, f2Sqr, k4result);
    multiply(k4result, fingerRegion, k4result);

    for (auto i = 0; i < originalImage.rows; i++) {
        for (auto j = 0; j < originalImage.cols; j++) {
            k.at<DATA_TYPE>(i, j, 3) = k4result.at<DATA_TYPE>(i, j);
        }
    }

    return k;
}
