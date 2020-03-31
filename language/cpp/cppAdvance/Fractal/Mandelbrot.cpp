//
// Created by 轩 on 2019/1/19.
//

#include "Mandelbrot.h"

Mandelbrot::Mandelbrot() {}

Mandelbrot::~Mandelbrot() {

}

int Mandelbrot::getIterations(double x, double y) {
    complex<double> z=0;
    complex<double> c(x, y);

    int iteration=0;
    while (iteration < MAX_ITERATIONS) {
        z = z * z + c;
        if (abs(z) > 2) {
            break;
        }
        iteration++;

    }
    return iteration;
}
