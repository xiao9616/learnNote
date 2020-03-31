//
// Created by 560204 on 19-1-21.
//

#include "FractalCreator.h"

FractalCreator::~FractalCreator() {

}

FractalCreator::FractalCreator(int m_width, int m_height) : m_width(m_width), m_height(m_height),
                                                            m_histogram(new int[Mandelbrot::MAX_ITERATIONS]{0}),
                                                            m_fractal(new int[Mandelbrot::MAX_ITERATIONS]{0}),
                                                            m_bitmap(m_width,m_height),
                                                            m_zoomList(m_width,m_height){
    cout<<"123"<<endl;
}

void FractalCreator::addZoom(const Zoom &zoom) {
    m_zoomList.add(zoom);
    cout<<"123"<<endl;
}

void FractalCreator::calculateIteration() {
    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            pair<double, double> coords = m_zoomList.doZoom(x, y);

            int iteration = Mandelbrot::getIterations(coords.first, coords.second);

            m_fractal[y * m_width + x] = iteration;

            if (iteration != Mandelbrot::MAX_ITERATIONS) {
                m_histogram[iteration]++;

            }

        }
    }

}

void FractalCreator::drawFractal() {
    int total = 0;

    for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; ++i) {
        total += m_histogram[i];
        cout << m_histogram[i] << endl;
    }

    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {

            uint8_t red=0;
            uint8_t green = 0;
            uint8_t blue = 0;

            int iteration = m_fractal[y * m_width + x];
            if (iteration != Mandelbrot::MAX_ITERATIONS) {
                double hue = 0.0;
                for (int i = 0; i <= iteration; ++i) {
                    hue+=((double)m_histogram[i])/total;
                }
                green = pow(255, hue);
            }

            m_bitmap.setPixel(x, y, red, green, blue);

        }
    }
}

void FractalCreator::writeBitmap(string name) {
    m_bitmap.write(name);
}
