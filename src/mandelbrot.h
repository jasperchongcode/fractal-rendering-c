#ifndef MANDELBROT_H
#define MANDELBROT_H

typedef struct
{
    int steps;
    float z_re;
    float z_im;
} EscapeResult;

EscapeResult verify_in_mandelbrot(float re, float im);

#endif
