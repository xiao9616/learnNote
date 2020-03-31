//
// Created by 560204 on 19-1-18.
//
#ifndef FRACTAL_BITMAP_H
#define FRACTAL_BITMAP_H

#include <string>
#include <cstdint>
#include <bits/unique_ptr.h>

using namespace std;

class Bitmap {
private:
    int m_width{0};
    int m_height{0};
    unique_ptr<uint8_t[]> m_pPixel{nullptr};
public:
    Bitmap(int m_width, int m_height);

    virtual ~Bitmap();

    bool write(string filename);

    void setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue);
};


#endif //FRACTAL_BITMAP_H
