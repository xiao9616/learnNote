//
// Created by 560204 on 19-1-18.
//
#include <fstream>
#include "Bitmap.h"
#include "BITMAPFILEHEADER.h"
#include "BitmapInfoHeader.h"

using namespace std;

Bitmap::Bitmap(int m_width, int m_height) : m_width(m_width), m_height(m_height),
                                            m_pPixel(new uint8_t[m_width * m_height * 3]{0}) {}

Bitmap::~Bitmap() {

}

bool Bitmap::write(string filename) {
    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;
    fileHeader.fileSize = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + m_width * m_height * 3;
    fileHeader.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

    infoHeader.width = m_width;
    infoHeader.height = m_height;

    ofstream file;
    file.open(filename, ios::out | ios::binary);
    if (!file) {
        return false;
    }

    file.write((char *) &fileHeader, sizeof(fileHeader));
    file.write((char *) &infoHeader, sizeof(infoHeader));
    file.write((char *) m_pPixel.get(), m_width * m_height * 3);

    file.close();
    if (!file) {
        return false;
    }
    return true;
}

void Bitmap::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue) {
    uint8_t *pPixel = m_pPixel.get();
    pPixel += (y * 3) * m_width + (x * 3);
    pPixel[0] = blue;
    pPixel[1] = green;
    pPixel[2] = red;
}


