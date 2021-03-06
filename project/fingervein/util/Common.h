//
// Created by user on 2020/6/13.
//

#ifndef FINGERVEIN_COMMON_H
#define FINGERVEIN_COMMON_H

#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/flann.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <iostream>
#include <bits/unique_ptr.h>
#include <unistd.h>
#include <dirent.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "IO.h"

//cppunit
#include <cppunit/TestCase.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TextTestResult.h>
#include <cppunit/TestRunner.h>
using namespace std;
using namespace cv;

#define IMAGE_TYPE CV_64F
#define DATA_TYPE double

#endif //FINGERVEIN_COMMON_H
