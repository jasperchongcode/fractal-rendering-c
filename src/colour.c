#include <math.h>
#include <SDL2/SDL.h>
#include "./constants.h"
#include "./colour.h"

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

ColourRGBA get_pixel_colour(int escape_steps)
{
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