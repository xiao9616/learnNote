//
// Created by user on 2020/7/9.
//

#ifndef FINGERVEIN_STRINGTEST_H
#define FINGERVEIN_STRINGTEST_H

#include <cppunit/TestCase.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TextTestResult.h>
#include <cppunit/TestRunner.h>


using namespace CppUnit;

class StringTest: public TestFixture {

public:
    void setUp() override;

    void tearDown() override;

    void testSwap();

    void testFind();
private:
    std::string     m_str1;
    std::string     m_str2;
};


#endif //FINGERVEIN_STRINGTEST_H
