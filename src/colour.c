#include <math.h>
#include <SDL2/SDL.h>
#include "constants.h"
#include "colour.h"
#include "fractal.h"

ColourRGBA COLOUR_MAP[COLOUR_MAP_LENGTH];
// ColourRGBA fill_colour = {0, 0, 0, 255};
uint8_t use_fill_colour = 1; // boolean
uint8_t colour_theme_index = 0;
float exponential_bias = DEFAULT_EXPONENTIAL_BIAS;

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

        float scale = 3.0f * M_PI; // 1 full cycle
        float stagger = 0.0f;      // optional per-pixel randomness

        // Handle different colour themes
        switch (colour_theme_index)
        {
        case 9:
            // cyclical rainbow theme
            red = (Uint8)((0.5f + 0.5f * sinf(t * scale + 0.0f + stagger)) * 255.0f);
            green = (Uint8)((0.5f + 0.5f * sinf(t * scale + 2.0944f + stagger)) * 255.0f); // +120°
            blue = (Uint8)((0.5f + 0.5f * sinf(t * scale + 4.1888f + stagger)) * 255.0f);  // +240°
            break;
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

double get_renormalised_count(int steps, double final_z_re, double final_z_im)
{
    return (double)(steps) + 1 - (logf((0.5) * logf(final_z_re * final_z_re + final_z_im * final_z_im)) / logf(2));
}

double average(double *arr, int length)
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

// returns a colourrgba object after shifting the normalised escape step by min
ColourRGBA get_pixel_colour(double normalised_escape_step, double min_normalised_escape_step)
{
    if (min_normalised_escape_step == 1 || normalised_escape_step == 1)
    {
        if (use_fill_colour)
        {
            return COLOUR_MAP[0];
        }
        else
        {
            return COLOUR_MAP[COLOUR_MAP_LENGTH - 1];
        }
    }
    // linear transform from min value and then apply power
    double linear_normalised_index = ((normalised_escape_step - min_normalised_escape_step) / (1 - min_normalised_escape_step)); // * COLOUR_MAP_LENGTH
    // unrounded_index = pow(unrounded_index, exponential_bias) * COLOUR_MAP_LENGTH;                                        // Bias it a little darker before returning index                                                   // smoothstep function
    // unrounded_index = pow(unrounded_index, 0.5);
    int index = (int)(pow(linear_normalised_index, exponential_bias) * COLOUR_MAP_LENGTH);

    return COLOUR_MAP[index];
}

// gets the non-discrete average escape step from all of provided escapeResults
double get_normalised_escape_step(EscapeResult *escapeResults, int num_results)
{
    double *smoothed = malloc(num_results * sizeof(double));
    // Always check if malloc was successful
    if (smoothed == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for smoothed array\n");
        // Return a default/error colour, e.g., black
        return 1.0f;
    }

    for (int i = 0; i < num_results; i++)
    {
        if (escapeResults[i].steps == max_steps)
        {
            smoothed[i] = 1;
        }
        else
        {
            smoothed[i] = get_renormalised_count(escapeResults[i].steps, escapeResults[i].z_re, escapeResults[i].z_im) / max_steps; // between 0 and 1
        }
    }

    double normalised_escape_step = average(smoothed, num_results);
    free(smoothed);

    if (normalised_escape_step > 1)
    {
        return 1.0f;
    }
    return normalised_escape_step;
}