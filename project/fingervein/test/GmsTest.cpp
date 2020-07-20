//
// Created by user on 2020/7/13.
//

#include "GmsTest.h"

void GmsTest::runTest() {
    IO *io = new IO();
    vector<string> dataBase;
    io->getFiles("/home/user/learnNote/project/fingervein/cmake-build-debug/dataset/malai/", dataBase, 1, 0);
    GMS *gms = new GMS("/home/user/learnNote/project/fingervein/cmake-build-debug/123.jpeg","/home/user/learnNote/project/fingervein/cmake-build-debug/456.jpeg");
    gms->detection(SIFT_FEATURE);
}
