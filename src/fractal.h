#ifndef FRACTAL_H
#define FRACTAL_H

#define NUM_FRACTALS 3
typedef struct
{
    int steps;
    double z_re;
    double z_im;
} EscapeResult;

typedef struct
{
    double re;
    double im;
} Complex;

extern int fractal_index;
extern int max_steps;

// EscapeResult verify_in_mandelbrot(Complex point);

// EscapeResult verify_in_julia(Complex point, Complex c);
EscapeResult verify_in_fractal(Complex point, Complex c);

#endif
