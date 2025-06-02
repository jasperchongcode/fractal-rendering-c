#ifndef COLOUR_H
#define COLOUR_H

#include "fractal.h"
typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} ColourRGBA;

#define COLOUR_MAP_LENGTH 1000

extern ColourRGBA COLOUR_MAP[COLOUR_MAP_LENGTH];

void initialise_colour_map(void);

ColourRGBA get_pixel_colour(EscapeResult *escapeResult, int length);

#endif