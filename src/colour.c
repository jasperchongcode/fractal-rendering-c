#include <math.h>
#include <SDL2/SDL.h>
#include "constants.h"
#include "colour.h"
#include "mandelbrot.h"

ColourRGBA COLOUR_MAP[1000];

void initialise_colour_map()
{
    for (int i = 0; i < 1000; i++)
    {
        COLOUR_MAP[i].r = i % 256;
        COLOUR_MAP[i].g = (i * 2) % 256;
        COLOUR_MAP[i].b = (i * 4) % 256;
        COLOUR_MAP[i].a = 255;
    }
}

float get_renormalised_count(int steps, float final_z_re, float final_z_im)
{
    return (float)(steps) + 1 - (logf((0.5) * logf(final_z_re * final_z_re + final_z_im * final_z_im)) / logf(2));
}

ColourRGBA get_pixel_colour(EscapeResult escapeResult)
{
    int escape_steps = escapeResult.steps;
    ColourRGBA colour;

    // Linear from 0 to 255
    Uint8 val = (Uint8)((escape_steps / (float)MAX_STEPS) * 255);
    // attempt to use log
    // Uint8 val;
    // if (escape_steps == 0)
    // {
    // 	val = 0;
    // }
    // else
    // {
    // 	val = (Uint8)((logf((float)escape_steps) / logf((float)MAX_STEPS)) * 255.0f);
    // }

    colour.r = val;
    colour.g = val;
    colour.b = val;
    colour.a = 255;

    return colour;
}