//
// Created by user on 2020/7/9.
//

#include "StringTest.h"

void StringTest::setUp() {
    m_str1 = "Hello, world";
    m_str2 = "Hi, cppunit";
}

void StringTest::tearDown() {
    TestFixture::tearDown();
}

void StringTest::testSwap() {
    std::string str1 = m_str1;
    std::string str2 = m_str2;
    m_str1.swap(m_str2);

    CPPUNIT_ASSERT(m_str1 == str2);
    CPPUNIT_ASSERT(m_str2 == str1);

}

void StringTest::testFind() {
    int pos1 = m_str1.find(',');
    int pos2 = m_str2.rfind(',');

    CPPUNIT_ASSERT_EQUAL(5, pos1);
    CPPUNIT_ASSERT_EQUAL(2, pos2);
}
