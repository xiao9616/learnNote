//
// Created by user on 2020/7/3.
//

#include "testMaxCurvature.h"

float testMaxCurvature::getPassPrecent() {
    return 0;
}

void testMaxCurvature::run() {
    MaxCurvatures *maxCurvatures = new MaxCurvatures("./original.jpg");
    maxCurvatures->detectFeature();
}
