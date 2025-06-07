#ifndef COLOUR_H
#define COLOUR_H

#include "fractal.h"
#include <stdint.h>
typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} ColourRGBA;

#define COLOUR_MAP_LENGTH 1000
#define NUM_COLOUR_THEMES 9
#define DEFAULT_EXPONENTIAL_BIAS 1.0f // Renormalised escape values are raised to this power, > 1 => darker bias < 1 => lighter bias (generally)

extern ColourRGBA COLOUR_MAP[COLOUR_MAP_LENGTH];

extern uint8_t colour_theme_index;

extern float exponential_bias;

void toggle_fill_colour(void);

void initialise_colour_map(void);

ColourRGBA get_pixel_colour(double normalised_escape_step, double min_normalised_escape_step);

double get_normalised_escape_step(EscapeResult *escapeResults, int num_results);

#endif