#include <math.h>
#include <stdio.h>
#include "fractal.h"
#include "constants.h"

// float get_distance_origin(float re, float im)
// {
//     return sqrt(re * re + im * im);
// }

/**
 * returns renormalised count to prevent bands, return -1 if never escapes
 */
EscapeResult verify_in_mandelbrot(Complex point)
{
    // Defined to escape if at any point it leaves a circle of radius 2

    float z_re = 0;
    float z_im = 0;

    for (int i = 0; i < MAX_STEPS; i++)
    {
        if ((z_re * z_re + z_im * z_im) >= 4)
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
        float z_re_prev = z_re;
        z_re = z_re * z_re - z_im * z_im + point.re; // re(z)^2 -im(z)^2 + re(c)
        z_im = 2 * z_re_prev * z_im + point.im;      // 2*re(z)*im(z) + im(c)
    }
    // printf("MADE TO END %d \n", 2);
    EscapeResult output;
    output.steps = MAX_STEPS;
    output.z_re = z_re;
    output.z_im = z_im;
    return output;
}

EscapeResult verify_in_julia(Complex point, Complex c)
{
    // Defined to escape if at any point it leaves a circle of radius 2

    float z_re = point.re;
    float z_im = point.im;

    for (int i = 0; i < MAX_STEPS; i++)
    {
        if ((z_re * z_re + z_im * z_im) >= 4)
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
        float z_re_prev = z_re;
        z_re = z_re * z_re - z_im * z_im + c.re; // re(z)^2 -im(z)^2 + re(c)
        z_im = 2 * z_re_prev * z_im + c.im;      // 2*re(z)*im(z) + im(c)
    }
    // printf("MADE TO END %d \n", 2);
    EscapeResult output;
    output.steps = MAX_STEPS;
    output.z_re = z_re;
    output.z_im = z_im;
    return output;
}
