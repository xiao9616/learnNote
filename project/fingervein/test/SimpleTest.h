//
// Created by user on 2020/7/9.
//

#ifndef FINGERVEIN_SIMPLETEST_H
#define FINGERVEIN_SIMPLETEST_H

#include <cppunit/TestCase.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TextOutputter.h>

using namespace CppUnit;

class SimpleTest :public TestCase {
public:
    void runTest() override;

};


#endif //FINGERVEIN_SIMPLETEST_H
