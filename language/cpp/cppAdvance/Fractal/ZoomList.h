//
// Created by 560204 on 19-1-21.
//

#ifndef FRACTAL_ZOOMLIST_H
#define FRACTAL_ZOOMLIST_H

#include "Zoom.h"
#include <iostream>
#include <vector>

using namespace std;

class ZoomList {
private:
    double m_xCenter{0};
    double m_yCenter{0};
    double m_scaler{1.0};

    int m_width{0};
    int m_height{0};
    vector<Zoom> zooms;
public:
    ZoomList(int m_width, int m_height);

    void add(const Zoom &zoom);

    pair<double ,double> doZoom(int x, int y);
};


#endif //FRACTAL_ZOOMLIST_H
