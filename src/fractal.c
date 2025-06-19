#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "fractal.h"
#include "constants.h"

int fractal_index = 0;
int max_steps = DEFAULT_MAX_STEPS;

/**
 * returns renormalised count to prevent bands, return -1 if never escapes
 */
EscapeResult verify_in_mandelbrot(Complex point)
{
    // Defined to escape if at any point it leaves a circle of radius 2

    double z_re = 0;
    double z_im = 0;

    for (int i = 0; i < max_steps; i++)
    {
        double z_re_squared = z_re * z_re;
        double z_im_squared = z_im * z_im;

        if ((z_re_squared + z_im_squared) >= 4)
        {
            EscapeResult output;
            output.steps = i;
            output.z_re = z_re;
            output.z_im = z_im;
            // printf("Escaped at %d steps for point (%f, %f)\n", i, re, im);
            return output;
            // return i;
        }
        // Otherwise iterate re and im
        // (a+bi)^2 = a^2 +2abi -b^2k
        // double z_re_prev = z_re;
        z_im = 2 * z_re * z_im + point.im;             // 2*re(z)*im(z) + im(c)
        z_re = z_re_squared - z_im_squared + point.re; // re(z)^2 -im(z)^2 + re(c)
    }
    // printf("MADE TO END %d \n", 2);
    EscapeResult output;
    output.steps = max_steps;
    output.z_re = z_re;
    output.z_im = z_im;
    return output;
}

EscapeResult verify_in_julia(Complex point, Complex c)
{
    // Defined to escape if at any point it leaves a circle of radius 2

    double z_re = point.re;
    double z_im = point.im;

    for (int i = 0; i < max_steps; i++)
    {
        double z_re_squared = z_re * z_re;
        double z_im_squared = z_im * z_im;

        if ((z_re_squared + z_im_squared) >= 4)
        {
            EscapeResult output;
            output.steps = i;
            output.z_re = z_re;
            output.z_im = z_im;
            // printf("Escaped at %d steps for point (%f, %f)\n", i, re, im);
            return output;
            // return i;
        }
        // Otherwise iterate re and im
        // (a+bi)^2 = a^2 +2abi -b^2k
        z_im = 2 * z_re * z_im + c.im;             // 2*re(z)*im(z) + im(c)
        z_re = z_re_squared - z_im_squared + c.re; // re(z)^2 -im(z)^2 + re(c)
    }
    // printf("MADE TO END %d \n", 2);
    EscapeResult output;
    output.steps = max_steps;
    output.z_re = z_re;
    output.z_im = z_im;
    return output;
}

EscapeResult verify_in_burning_ship(Complex point)
{
    // The burning ship fractal

    double z_re = point.re;
    double z_im = point.im;

    for (int i = 0; i < max_steps; i++)
    {
        double z_re_squared = z_re * z_re;
        double z_im_squared = z_im * z_im;
        // if escaped
        if ((z_re_squared + z_im_squared) >= 4)
        {
            EscapeResult output;
            output.steps = i;
            output.z_re = z_re;
            output.z_im = z_im;
            return output;
        }

        z_im = fabs(2 * z_re * z_im) + point.im;       // add initial im component
        z_re = z_re_squared - z_im_squared + point.re; // add initial re
    }

    EscapeResult output;
    output.steps = max_steps;
    output.z_re = z_re;
    output.z_im = z_im;
    return output;
}

EscapeResult verify_in_fractal(Complex point, Complex C)
{
    switch (fractal_index)
    {
    case 0:
        return verify_in_julia(point, C);
    case 1:
        return verify_in_mandelbrot(point);
    case 2:
        return verify_in_burning_ship(point);
    }
    printf("Invalid fractal_index");
    return (EscapeResult){0, 0, 0};
}