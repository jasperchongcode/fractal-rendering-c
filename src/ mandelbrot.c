#include <math.h>
#include "mandelbrot.h"
#include "constants.h"

float get_distance_origin(float re, float im)
{
    return sqrt(re * re + im * im);
}

/**
 * @brief  Returns steps until escapes (or max steps)
 *
 * @param x
 * @param y
 * @return int
 */
int verify_in_mandelbrot(float re, float im)
{
    // Defined to escape if at any point it leaves a circle of radius 2

    float z_re = 0;
    float z_im = 0;

    for (int i = 0; i < MAX_STEPS; i++)
    {
        if (get_distance_origin(z_re, z_im) >= 2)
        {
            return i;
        }
        // Otherwise iterate re and im
        // (a+bi)^2 = a^2 +2abi -b^2k
        float z_re_prev = z_re;
        z_re = z_re * z_re - z_im * z_im + re; // re(z)^2 -im(z)^2 + re(c)
        z_im = 2 * z_re_prev * z_im + im;      // 2*re(z)*im(z) + im(c)
    }

    return MAX_STEPS;
}
