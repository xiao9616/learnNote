//
// Created by user on 2020/7/3.
//

#ifndef FINGERVEIN_TESTMAXCURVATURE_H
#define FINGERVEIN_TESTMAXCURVATURE_H

#include "testInterface.h"
#include "../curvature/MaxCurvatures.h"

class testMaxCurvature : public testInterface {
public:

    float getPassPrecent() override;

    void run() override;

};


#endif //FINGERVEIN_TESTMAXCURVATURE_H
