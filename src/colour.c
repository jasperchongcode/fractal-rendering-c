#include <math.h>
#include <SDL2/SDL.h>
#include "constants.h"
#include "colour.h"
#include "fractal.h"

ColourRGBA COLOUR_MAP[COLOUR_MAP_LENGTH];
ColourRGBA fill_colour = {0, 0, 0, 255};
uint8_t use_fill_colour = 1; // boolean
uint8_t colour_theme_index = 7;

// void initialise_colour_map()
// {
//     for (int i = 0; i < COLOUR_MAP_LENGTH; i++)
//     {
//         COLOUR_MAP[i].r = i % 256;
//         COLOUR_MAP[i].g = (i * 2) % 256;
//         COLOUR_MAP[i].b = (i * 4) % 256;
//         COLOUR_MAP[i].a = 255;
//     }
// }
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
            red = (Uint8)(brightness * 255);
            green = (Uint8)(brightness * 255);
            break;
        case 4: // pink
            red = (Uint8)(brightness * 255);
            blue = (Uint8)(brightness * 255);
            break;
        case 5: // cyan
            green = (Uint8)(brightness * 255);
            blue = (Uint8)(brightness * 255);
            break;
        case 6: // black -> white
            red = (Uint8)(brightness * 255);
            green = (Uint8)(brightness * 255);
            blue = (Uint8)(brightness * 255);
            break;
        case 7: // amber
            brightness = brightness / 3;
            red = (Uint8)(2 * brightness * 255);
            green = (Uint8)(brightness * 255);
            break;
            // case 7: // white -> black
            //         // float inverted = 1.0f - brightness;
            //         // red = green = blue = (Uint8)(inverted * 255);
            //         // for some reason this is breaking
            //     break;
        }
        COLOUR_MAP[i].r = red;
        COLOUR_MAP[i].g = green;
        COLOUR_MAP[i].b = blue;
        COLOUR_MAP[i].a = 255;
    }
}

float get_renormalised_count(int steps, float final_z_re, float final_z_im)
{
    return (float)(steps) + 1 - (logf((0.5) * logf(final_z_re * final_z_re + final_z_im * final_z_im)) / logf(2));
}

double average(float *arr, int length)
{
    if (length == 0)
        return 0.0; // Avoid division by zero

    float sum = 0; // Use long long to avoid overflow for large sums
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
    float smoothed[num_results];
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

    if (index >= COLOUR_MAP_LENGTH)
    {
        // if it is fully in the set, return black:
        // ColourRGBA colour;
        // colour.r = 0;
        // colour.g = 255;
        // colour.b = 0;
        // colour.a = 255;
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