#ifndef COLOUR_H
#define COLOUR_H

#include <stdint.h>    // for uint8_t
#include "constants.h" // for COLOUR_MAP_SIZE

/**
 * RGBA colour struct.
 * We’ll store each channel in a single-byte (0..255).
 */
typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} ColourRGBA;

extern ColourRGBA COLOUR_MAP[1000];

void initialise_colour_map(void);

ColourRGBA get_pixel_colour(int escape_steps);

#endif