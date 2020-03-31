//
// Created by 560204 on 19-1-21.
//

#include "ZoomList.h"

ZoomList::ZoomList(int m_width, int m_height) : m_width(m_width), m_height(m_height) {}

void ZoomList::add(const Zoom &zoom) {
    zooms.push_back(zoom);
    m_xCenter += (zoom.x - m_width / 2) * m_scaler;
    m_yCenter += (zoom.y - m_height / 2) * m_scaler;
    m_scaler *= zoom.scale;
}

pair<double, double> ZoomList::doZoom(int x, int y) {
    double xFractal = (x - m_width / 2) * m_scaler + m_xCenter;
    double yFractal = (y - m_height / 2) * m_scaler + m_yCenter;

    return pair<double, double>(xFractal, yFractal);
}
