//
// Created by user on 2020/7/13.
//

#ifndef FINGERVEIN_GMSTEST_H
#define FINGERVEIN_GMSTEST_H

#include "../util/Common.h"
#include "../GMS/GMS.h"
#include "../util/IO.h"


using namespace CppUnit;

class GmsTest : public TestCase {
public:
    void runTest() override;
};


#endif //FINGERVEIN_GMSTEST_H
