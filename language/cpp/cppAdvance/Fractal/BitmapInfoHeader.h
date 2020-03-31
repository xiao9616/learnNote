//
// Created by 560204 on 19-1-18.
//

#ifndef FRACTAL_BITMAPINFOHEADER_H
#define FRACTAL_BITMAPINFOHEADER_H

#include <cstdint>

using namespace std;

#pragma back(2)

struct BitmapInfoHeader {
    int32_t headerSize{40};
    int32_t width;
    int32_t height;
    int16_t planes{1};
    int16_t bitPerPixel{24};
    int32_t compression{0};
    int32_t dataSize{0};
    int32_t horizontaResolution{2400};
    int32_t verticalResolution{2400};
    int32_t colors{0};
    int32_t importanColor{0};
};
#endif //FRACTAL_BITMAPINFOHEADER_H
