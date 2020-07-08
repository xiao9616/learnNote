#include <opencv2/imgproc/imgproc_c.h>
#include "Common.h"

using namespace cv;

Mat extractFingerRegion(Mat);

Mat extractFingerVeinsMaxCurvature(Mat, int);

Mat filterAndCalculateCurvatures(Mat, Mat, int);

Mat trackVeinsCentres(Mat, Size);

Mat extractVeinsFromCentres(Mat, Mat);

void cvShowManyImages(char *title, int nArgs, ...);

int main(int argc, char **argv) {
    Mat image;
    image = imread("finger.png", CV_LOAD_IMAGE_GRAYSCALE);   // Read the file
    double scale = (double) 1 / 255;
    equalizeHist(image, image);
    Mat temp;
    image.convertTo(temp, -1, 0.65, 0);
    cv::GaussianBlur(temp, temp, cv::Size(0, 0), 3);
    cv::addWeighted(image, 1.5, temp, -1.10, 0, temp);
    image = temp;
    image.convertTo(image, IMAGE_TYPE, scale);
    resize(image, image, cv::Size(390, image.size().height / 2));

    if (!image.data)                              // Check for invalid input
    {
        std::cout << "Could not open or find the image" << std::endl;
        return -1;
    }

    auto sigma = 3;

    auto veins = extractFingerVeinsMaxCurvature(image, sigma);

    for (auto i = 0; i < veins.rows; i++)
        for (auto j = 0; j < veins.cols; j++) {
            auto val = veins.at<DATA_TYPE>(i, j);
            if (val >= DATA_TYPE(0.01))
                veins.at<DATA_TYPE>(i, j) = DATA_TYPE(1);
            else if (val < DATA_TYPE(0))
                veins.at<DATA_TYPE>(i, j) = DATA_TYPE(0);
        }

    namedWindow("extracted veins", WINDOW_AUTOSIZE);    // Create a window for display.
    imshow("extracted veins", veins);                   // Show our image inside it.
    namedWindow("initial image", WINDOW_AUTOSIZE);
    imshow("initial image", image);

    Mat matlabResult;
    matlabResult = imread("matlab_result.png", CV_LOAD_IMAGE_GRAYSCALE);
    matlabResult.convertTo(matlabResult, IMAGE_TYPE, scale);

    int cw = 80, ch = 30;

    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}

Mat extractFingerVeinsMaxCurvature(Mat originalImage, int sigma) {
    auto fingerRegion = extractFingerRegion(originalImage);

    namedWindow("finger region", WINDOW_AUTOSIZE);
    imshow("finger region", fingerRegion);

    auto curvatures = filterAndCalculateCurvatures(originalImage, fingerRegion, sigma);

    auto trackedVeins = trackVeinsCentres(curvatures, originalImage.size());

    namedWindow("tracked veins", WINDOW_AUTOSIZE);
    imshow("tracked veins", trackedVeins);

    return extractVeinsFromCentres(trackedVeins, fingerRegion);
}
