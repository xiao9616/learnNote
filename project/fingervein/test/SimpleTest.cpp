//
// Created by user on 2020/7/9.
//

#include "SimpleTest.h"

void SimpleTest::runTest() {
    {
        int i = 1;
        CPPUNIT_ASSERT_EQUAL(1, i);
    }
}
