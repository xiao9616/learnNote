#include <iostream>
#include "util/Common.h"
#include "sift_lbp/DetectFeature.h"
#include "util/IO.h"
#include "test/testAllImage.h"
#include "pre_treatment/FFT.h"
#include "test/testInterface.h"
#include "test/testMaxCurvature.h"
#include "test/SimpleTest.h"
#include "test/StringTest.h"
#include <cuda.h>
#define image1 "./1.png"
#define image2 "./2.png"

void test() {
    Mat image = imread(image1, IMREAD_GRAYSCALE);
    namedWindow("image");
    imshow("image", image);
    Mat hist;
    equalizeHist(image, hist);
    namedWindow("hist");
    imshow("hist", hist);
    Mat threshold;
    adaptiveThreshold(hist, threshold, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 17, 11);
    namedWindow("threshold");
    imshow("threshold", threshold);
    Mat gaussImage;
    GaussianBlur(threshold, gaussImage, Size(15, 15), 0);
    GaussianBlur(gaussImage, gaussImage, Size(7, 7), 0);
    namedWindow("gauss");
    imshow("gauss", gaussImage);

    Mat kernel_dilate = getStructuringElement(MORPH_RECT, Size(5, 5));
    Mat kernel_erode = getStructuringElement(MORPH_RECT, Size(3, 3));

    Mat dilateImage;
    dilate(gaussImage, dilateImage, kernel_dilate);
    namedWindow("dilate");
    imshow("dilate", dilateImage);
    Mat erodeImage;
    erode(dilateImage, erodeImage, kernel_erode);
    erode(erodeImage, erodeImage, kernel_erode);
    namedWindow("erode");
    imshow("erode", erodeImage);

    Mat thresholdresult;
    equalizeHist(erodeImage, thresholdresult);
    namedWindow("thresholdresult");
    imshow("thresholdresult", thresholdresult);
    waitKey(0);

}

int main() {
/*    testInterface *test = new testMaxCurvature();
    test->setDataBase("/home/user/learnNote/project/fingervein/cmake-build-debug/dataset/malai/");
    test->setInput("/home/user/learnNote/project/fingervein/cmake-build-debug/dataset/malai/");
    test->run();
    TestResult result;
    TestResultCollector resultCollector;
    result.addListener(&resultCollector);


    SimpleTest simpleTest;
    simpleTest.run(&result);
    TextOutputter outputter(&resultCollector, cout);\
    outputter.write();

    TestRunner runner;
    runner.addTest(new TestCaller<StringTest>("testSwap", &StringTest::testSwap));
    runner.addTest(new CppUnit::TestCaller<StringTest>("testFind", &StringTest::testFind));
    runner.run(result); // 运行测试

    CppUnit::TextOutputter o(&resultCollector, std::cout);
    o.write();


    FFT *fft = new FFT("/home/user/learnNote/project/fingervein/cmake-build-debug/dataset/malai/vein005_1/02.jpg");
    fft->process();
    return 0;*/


}