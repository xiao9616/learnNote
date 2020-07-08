//
// Created by user on 2020/7/2.
//

#include "fft.h"

fft::fft(const String &imageInput) {
    image_input = imread(imageInput, IMREAD_GRAYSCALE);
}

void fft::show() {
    namedWindow("idft");
    imshow("idft", this->image_output);
}

void fft::process() {
    if (image_input.empty()) {
        cerr << "read image error" << endl;
    }
    int m = getOptimalDFTSize(image_input.rows);
    int n = getOptimalDFTSize(image_input.cols);

    Mat padded;
    copyMakeBorder(this->image_input, padded, 0, m - image_input.rows, 0,n - image_input.cols, BORDER_CONSTANT,
                   Scalar::all(0));

}
