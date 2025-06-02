#ifndef COLOUR_H
#define COLOUR_H

#include "mandelbrot.h"
typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} ColourRGBA;

extern ColourRGBA COLOUR_MAP[1000];

void initialise_colour_map(void);

ColourRGBA get_pixel_colour(EscapeResult escapeResult);

#endif