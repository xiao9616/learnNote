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
#include "./test/GmsTest.h"

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

    TestResult result;
    TestResultCollector resultCollector;
    result.addListener(&resultCollector);


    GmsTest simpleTest;
    simpleTest.run(&result);
    TextOutputter outputter(&resultCollector, cout);\
    outputter.write();
}