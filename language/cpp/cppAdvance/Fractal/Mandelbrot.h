//
// Created by 轩 on 2019/1/19.
//

#ifndef FRACTAL_MANDELBROT_H
#define FRACTAL_MANDELBROT_H

#include <complex>

using namespace std;

class Mandelbrot {
public:
    Mandelbrot();

    virtual ~Mandelbrot();

    static int getIterations(double x, double y);

public:
    static const int MAX_ITERATIONS = 1000;

};


#endif //FRACTAL_MANDELBROT_H
