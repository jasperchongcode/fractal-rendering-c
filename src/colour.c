#include <math.h>
#include <SDL2/SDL.h>
#include "constants.h"
#include "colour.h"
#include "mandelbrot.h"

ColourRGBA COLOUR_MAP[COLOUR_MAP_LENGTH];

void initialise_colour_map()
{
    for (int i = 0; i < COLOUR_MAP_LENGTH; i++)
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
    ColourRGBA colour;

    if (escapeResult.steps == MAX_STEPS)
    {
        colour.r = 0;
        colour.g = 0;
        colour.b = 0;
        colour.a = 255;
        return colour;
    }
    float smoothed = get_renormalised_count(escapeResult.steps, escapeResult.z_re, escapeResult.z_im) / MAX_STEPS; // between 0 and 1

    // todo make it interpolate between the nearest two counts
    return COLOUR_MAP[(int)(smoothed * COLOUR_MAP_LENGTH)];
    // return COLOUR_MAP[(int)(((float)escapeResult.steps / MAX_STEPS) * COLOUR_MAP_LENGTH)];

    // int escape_steps = escapeResult.steps;

    // Linear from 0 to 255
    // Uint8 val = (Uint8)((escape_steps / (float)MAX_STEPS) * 255);
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

    // colour.r = val;
    // colour.g = val;
    // colour.b = val;
    // colour.a = 255;

    // return colour;
}