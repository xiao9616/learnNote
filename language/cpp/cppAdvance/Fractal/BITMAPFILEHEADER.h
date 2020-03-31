//
// Created by 560204 on 19-1-18.
//
#ifndef FRACTAL_BITMAPFILEHEADER_H
#define FRACTAL_BITMAPFILEHEADER_H

#include <cstdint>

using namespace std;

#pragma pack(2)

struct BitmapFileHeader {
    char header[2]{'B', 'M'};
    int32_t fileSize;
    int32_t reserved{0};
    int32_t dataOffset;
};
#endif //FRACTAL_BITMAPFILEHEADER_H
