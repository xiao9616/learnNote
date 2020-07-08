//
// Created by user on 2020/6/24.
//

#ifndef FINGERVEIN_TESTALLIMAGE_H
#define FINGERVEIN_TESTALLIMAGE_H

#include "../util/Common.h"
#include "../sift_lbp/DetectFeature.h"
#include "../util/IO.h"

class testAllImage {
private:

    vector<int> y1;
    vector<int> y2;

    vector<string> dataBase;
    vector<string> input;
    float result;
public:
    void run();

    void getROC();

    testAllImage();

    void setDataBase(const String &path);

    void setInput(const String &inputPath);

    float getPassPrecent();

    virtual ~testAllImage();

};


#endif //FINGERVEIN_TESTALLIMAGE_H
