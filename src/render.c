
#include <SDL2/SDL.h>
#include "constants.h"
#include "fractal.h"
#include "colour.h"
#include "sdl_helpers.h"
#include <omp.h>

Complex C = {1, 1};
// memory buffer

uint32_t pixels[WINDOW_WIDTH * WINDOW_HEIGHT]; //! this is assuming window size stays constant

// offsets for multisampling
float offsets_x[SAMPLE_GRID_WIDTH];
float offsets_y[SAMPLE_GRID_WIDTH];

int samples_per_pixel = SAMPLE_GRID_WIDTH * SAMPLE_GRID_WIDTH;

void initialise_offsets(void)
{
    // initialise the offsets
    int index = 0;
    for (int y = 0; y < SAMPLE_GRID_WIDTH; y++)
    {
        for (int x = 0; x < SAMPLE_GRID_WIDTH; x++)
        {
            offsets_x[index] = (x + 0.5f) / SAMPLE_GRID_WIDTH;
            offsets_y[index] = (y + 0.5f) / SAMPLE_GRID_WIDTH;
            index++;
        }
    }
}

void render_fractal(void)
{
    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black background
    SDL_RenderClear(renderer);

    float pixel_width = (X_MAX - X_MIN) / WINDOW_WIDTH;
    float pixel_height = (Y_MAX - Y_MIN) / WINDOW_HEIGHT;

#pragma omp parallel for schedule(dynamic, 1)
    for (int r = 0; r < WINDOW_HEIGHT; r++)
    {
        for (int c = 0; c < WINDOW_WIDTH; c++)
        {
            // Number of samples per pixel, e.g., 4 (2x2 grid)

            EscapeResult escapeResults[samples_per_pixel];

            // Sample positions within the pixel, offsets normalized between 0 and 1

            for (int s = 0; s < samples_per_pixel; s++)
            {
                Complex point;
                // Base coordinates for this pixel (top-left corner)
                float base_re = X_MIN + c * pixel_width;
                float base_im = Y_MIN + r * pixel_height;

                // Add sample offsets scaled by pixel dimensions
                point.re = base_re + offsets_x[s] * pixel_width;
                point.im = base_im + offsets_y[s] * pixel_height;

                escapeResults[s] = verify_in_julia(point, C);
            }

            ColourRGBA pixel_colour = get_pixel_colour(escapeResults, samples_per_pixel);

            uint32_t flat_colour = (pixel_colour.r << 24) | (pixel_colour.g << 16) | (pixel_colour.b << 8) | (pixel_colour.a);
            pixels[r * WINDOW_WIDTH + c] = flat_colour;
        }
    }

    // swap to buffer
    SDL_UpdateTexture(texture, NULL, pixels, WINDOW_WIDTH * sizeof(uint32_t));
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer); // swap buffers
    printf("RENDERED NEW FRACTAL\n");
}
