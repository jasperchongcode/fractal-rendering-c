#include <math.h>
#include <SDL2/SDL.h>
#include "constants.h"
#include "colour.h"
#include "fractal.h"

ColourRGBA COLOUR_MAP[COLOUR_MAP_LENGTH];
ColourRGBA fill_colour = {0, 0, 0, 255};
uint8_t use_fill_colour = 1; // boolean
uint8_t colour_theme_index = 0;

void initialise_colour_map()
{

    for (int i = 0; i < COLOUR_MAP_LENGTH; i++)
    {

        float t = (float)i / (COLOUR_MAP_LENGTH - 1); // normalized 0..1

        float brightness = logf(1 + 9 * t) / logf(10); // nonlinear log

        // start with all 0
        Uint8 green = 0;
        Uint8 blue = 0;
        Uint8 red = 0;

        // Handle different colour themes
        switch (colour_theme_index)
        {
        case 0:
            green = (Uint8)(brightness * 255); // green increases
            break;
        case 1:
            blue = (Uint8)(brightness * 255);
            break;
        case 2:
            red = (Uint8)(brightness * 255);
            break;
        case 3: // Yellow
            red = green = (Uint8)(brightness * 255);
            // green = (Uint8)(brightness * 255);
            break;
        case 4: // pink
            red = blue = (Uint8)(brightness * 255);
            // blue = (Uint8)(brightness * 255);
            break;
        case 5: // cyan
            green = blue = (Uint8)(brightness * 255);
            // blue = (Uint8)(brightness * 255);
            break;
        case 6: // black -> white
            red = green = blue = (Uint8)(brightness * 255);
            // green = (Uint8)(brightness * 255);
            // blue = (Uint8)(brightness * 255);
            break;
        case 7: // amber
            brightness = brightness / 3;
            red = (Uint8)(2 * brightness * 255);
            green = (Uint8)(brightness * 255);
            break;
        case 8: // white -> black
            red = green = blue = (Uint8)((1.0f - brightness) * 255);
            // for some reason this is breaking
            break;
        }
        COLOUR_MAP[i].r = red;
        COLOUR_MAP[i].g = green;
        COLOUR_MAP[i].b = blue;
        COLOUR_MAP[i].a = 255;
    }
}

float get_renormalised_count(int steps, double final_z_re, double final_z_im)
{
    return (float)(steps) + 1 - (logf((0.5) * logf(final_z_re * final_z_re + final_z_im * final_z_im)) / logf(2));
}

double average(float *arr, int length)
{
    if (length == 0)
        return 0.0; // Avoid division by zero

    double sum = 0; // Use long long to avoid overflow for large sums
    for (int i = 0; i < length; i++)
    {
        sum += arr[i];
    }

    return (double)sum / length;
}

void toggle_fill_colour(void)
{
    use_fill_colour = !use_fill_colour;
}

ColourRGBA get_pixel_colour(EscapeResult *escapeResults, int num_results)

{

    float *smoothed = malloc(num_results * sizeof(float));
    // Always check if malloc was successful
    if (smoothed == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for smoothed array\n");
        // Return a default/error colour, e.g., black
        return (ColourRGBA){0, 0, 0, 255};
    }

    for (int i = 0; i < num_results; i++)
    {
        if (escapeResults[i].steps == MAX_STEPS)
        {
            smoothed[i] = 1;
        }
        else
        {
            smoothed[i] = get_renormalised_count(escapeResults[i].steps, escapeResults[i].z_re, escapeResults[i].z_im) / MAX_STEPS; // between 0 and 1
        }
    }

    int index = (int)(average(smoothed, num_results) * COLOUR_MAP_LENGTH);
    free(smoothed);
    if (index >= COLOUR_MAP_LENGTH)
    {
        // if it is fully in the set
        if (use_fill_colour)
        {
            return fill_colour;
        }
        else
        {
            return COLOUR_MAP[COLOUR_MAP_LENGTH - 1];
        }
    }
    else
    {
        return COLOUR_MAP[index];
    }
}