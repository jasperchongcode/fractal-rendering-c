#ifndef FRACTAL_H
#define FRACTAL_H

typedef struct
{
    int steps;
    float z_re;
    float z_im;
} EscapeResult;

typedef struct
{
    float re;
    float im;
} Complex;

EscapeResult verify_in_mandelbrot(Complex point);

EscapeResult verify_in_julia(Complex point, Complex c);

#endif
