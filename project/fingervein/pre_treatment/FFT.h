//
// Created by user on 2020/7/2.
//

#ifndef FINGERVEIN_FFT_H
#define FINGERVEIN_FFT_H

#include "../util/Common.h"

class FFT {
    Mat image_input;
    Mat image_output;
public:
    FFT(const String &imageInput);

    void process();

    void show();
};


#endif //FINGERVEIN_FFT_H
