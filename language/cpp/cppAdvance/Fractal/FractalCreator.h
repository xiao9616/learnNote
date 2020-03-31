//
// Created by 560204 on 19-1-21.
//

#ifndef FRACTAL_FRACTALCREATOR_H
#define FRACTAL_FRACTALCREATOR_H

#include <iostream>
#include <string>
#include "Zoom.h"
#include <bits/unique_ptr.h>
#include "Mandelbrot.h"
#include "Bitmap.h"
#include "ZoomList.h"

using namespace std;

class FractalCreator {
public:
    int m_width;
    int m_height;
    unique_ptr<int[]> m_histogram;
    unique_ptr<int[]> m_fractal;
    Bitmap m_bitmap;
    ZoomList m_zoomList;

public:
    FractalCreator(int m_width, int m_height);

    virtual ~FractalCreator();

    void calculateIteration();
    void drawFractal();
    void addZoom(const Zoom &zoom);
    void writeBitmap(string name);
};


#endif //FRACTAL_FRACTALCREATOR_H
