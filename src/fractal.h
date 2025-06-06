#ifndef FRACTAL_H
#define FRACTAL_H

#define NUM_FRACTALS 2
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

extern int fractal_index;

// EscapeResult verify_in_mandelbrot(Complex point);

// EscapeResult verify_in_julia(Complex point, Complex c);
EscapeResult verify_in_fractal(Complex point, Complex c);

#endif
