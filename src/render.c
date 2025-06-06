
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "constants.h"
#include "fractal.h"
#include "colour.h"
#include "sdl_helpers.h"
#include <omp.h>

Complex C = {1, 1};
double x_min = DEFAULT_X_MIN;
double x_max = DEFAULT_X_MAX;
double y_min = DEFAULT_Y_MIN;
double y_max = DEFAULT_Y_MAX;

uint32_t pixels[WINDOW_WIDTH * WINDOW_HEIGHT]; //! this is assuming window size stays constant
// Store the mutlisample escape steps per pixel (normalised 0-1)
// todo could be good to change this to double eventually
double normalised_escape_step_buffer[WINDOW_WIDTH * WINDOW_HEIGHT];

int samples_per_pixel = SAMPLE_GRID_WIDTH * SAMPLE_GRID_WIDTH;

// offsets for multisampling
double offsets_x[SAMPLE_GRID_WIDTH * SAMPLE_GRID_WIDTH];
double offsets_y[SAMPLE_GRID_WIDTH * SAMPLE_GRID_WIDTH];

void initialise_offsets(void)
{
    // initialise the offsets
    int index = 0;
    for (int y = 0; y < SAMPLE_GRID_WIDTH; y++)
    {
        for (int x = 0; x < SAMPLE_GRID_WIDTH; x++)
        {
            offsets_x[index] = (x + 0.5) / SAMPLE_GRID_WIDTH;
            offsets_y[index] = (y + 0.5) / SAMPLE_GRID_WIDTH;
            index++;
        }
    }
}

void render_fractal(void)
{
    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black background
    SDL_RenderClear(renderer);

    double pixel_width = (x_max - x_min) / WINDOW_WIDTH;
    double pixel_height = (y_max - y_min) / WINDOW_HEIGHT;

#pragma omp parallel
    {
        // allocate memory for escapeResults for each thread
        EscapeResult *escapeResults = malloc(samples_per_pixel * sizeof(EscapeResult));
        if (!escapeResults)
        {
            printf("Error allocating memory for escapeResults");
            exit(1);
        }

#pragma omp for schedule(dynamic, 1)
        for (int r = 0; r < WINDOW_HEIGHT; r++)
        {
            for (int c = 0; c < WINDOW_WIDTH; c++)
            {
                // Number of samples per pixel, e.g., 4 (2x2 grid)

                // EscapeResult escapeResults[samples_per_pixel];

                // Sample positions within the pixel, offsets normalized between 0 and 1

                for (int s = 0; s < samples_per_pixel; s++)
                {
                    Complex point;
                    // Base coordinates for this pixel (top-left corner)
                    double base_re = x_min + c * pixel_width;
                    double base_im = y_min + r * pixel_height;

                    // Add sample offsets scaled by pixel dimensions
                    point.re = base_re + offsets_x[s] * pixel_width;
                    point.im = base_im + offsets_y[s] * pixel_height;

                    escapeResults[s] = verify_in_fractal(point, C);
                }

                double normalised_escape_step = get_normalised_escape_step(escapeResults, samples_per_pixel);

                normalised_escape_step_buffer[r * WINDOW_WIDTH + c] = normalised_escape_step;
            }
        }
        free(escapeResults);
    }

    // Strategy 1, find the min and then adjust the min
    double min_normalised_escape_step = normalised_escape_step_buffer[0];

    for (int i = 1; i < WINDOW_WIDTH * WINDOW_HEIGHT; i++)
    {
        if (normalised_escape_step_buffer[i] < min_normalised_escape_step)
        {
            min_normalised_escape_step = normalised_escape_step_buffer[i]; // Update min if a smaller element is found
        }
    }
    printf("NORMALISED\n");
    printf("%f\n.", min_normalised_escape_step);

#pragma omp parallel for schedule(dynamic, 1)
    for (int r = 0; r < WINDOW_HEIGHT; r++)
    {
        for (int c = 0; c < WINDOW_WIDTH; c++)
        {
            ColourRGBA pixel_colour = get_pixel_colour(normalised_escape_step_buffer[r * WINDOW_WIDTH + c], min_normalised_escape_step);

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

void render_save_fractal(char *filename, int window_width, int window_height)
{
    // Allocate the pixel buffer
    uint32_t *pixel_buffer = malloc(window_width * window_height * sizeof(uint32_t));
    if (!pixel_buffer)
    {
        fprintf(stderr, "Memory Allocation for Image Rendering failed. \n");
        return;
    }
    double *image_normalised_escape_step_buffer = malloc(window_width * window_height * sizeof(double));
    if (!image_normalised_escape_step_buffer)
    {
        fprintf(stderr, "Memory Allocation for normalised_escape_step_buffer Image Rendering failed. \n");
        return;
    }

    // Constants required for multisampling
    int image_samples_per_pixel = IMAGE_SAMPLE_GRID_WIDTH * IMAGE_SAMPLE_GRID_WIDTH;

    // offsets for multisampling
    double image_offsets_x[image_samples_per_pixel];
    double image_offsets_y[image_samples_per_pixel];

    // initialise the offsets
    int index = 0;
    for (int y = 0; y < IMAGE_SAMPLE_GRID_WIDTH; y++)
    {
        for (int x = 0; x < IMAGE_SAMPLE_GRID_WIDTH; x++)
        {
            image_offsets_x[index] = (x + 0.5) / IMAGE_SAMPLE_GRID_WIDTH;
            image_offsets_y[index] = (y + 0.5) / IMAGE_SAMPLE_GRID_WIDTH;
            index++;
        }
    }
    // Constants for finding representative points
    double pixel_width = (x_max - x_min) / window_width;
    double pixel_height = (y_max - y_min) / window_height;

#pragma omp parallel
    {
        // allocate for each thread
        EscapeResult *escapeResults = malloc(image_samples_per_pixel * sizeof(EscapeResult));
        if (!escapeResults)
        {
            printf("Error allocating image escapeResults");
            exit(1);
        }

#pragma omp for schedule(dynamic, 1)
        for (int r = 0; r < window_height; r++)
        {
            for (int c = 0; c < window_width; c++)
            {
                // List of results to average for multisampling
                // EscapeResult escapeResults[image_samples_per_pixel];

                for (int s = 0; s < image_samples_per_pixel; s++)
                {
                    // Get the complex coords of this point
                    Complex point;
                    // Base coordinates for this pixel (top-left corner)
                    double base_re = x_min + c * pixel_width;
                    double base_im = y_min + r * pixel_height;

                    // Add sample offsets scaled by pixel dimensions
                    point.re = base_re + image_offsets_x[s] * pixel_width;
                    point.im = base_im + image_offsets_y[s] * pixel_height;
                    // Calculate escape results
                    escapeResults[s] = verify_in_fractal(point, C);
                }
                // // get the pixel colour from the average of the multisampling
                // ColourRGBA pixel_colour = get_pixel_colour(escapeResults, image_samples_per_pixel);
                // // store in pixel buffer as uint32_t
                // uint32_t flat_colour = (pixel_colour.r << 24) | (pixel_colour.g << 16) | (pixel_colour.b << 8) | (pixel_colour.a);
                // pixel_buffer[r * window_width + c] = flat_colour;

                double normalised_escape_step = get_normalised_escape_step(escapeResults, samples_per_pixel);

                image_normalised_escape_step_buffer[r * window_width + c] = normalised_escape_step;
            }
        }
        free(escapeResults);
    }

    // Strategy 1, find the min and then adjust the min
    double min_normalised_escape_step = image_normalised_escape_step_buffer[0];

    for (int i = 1; i < window_width * window_height; i++)
    {
        if (image_normalised_escape_step_buffer[i] < min_normalised_escape_step)
        {
            min_normalised_escape_step = image_normalised_escape_step_buffer[i]; // Update min if a smaller element is found
        }
    }
    // printf("NORMALISED\n");
    // printf("%f\n.", min_normalised_escape_step);

#pragma omp parallel for schedule(dynamic, 1)
    for (int r = 0; r < window_height; r++)
    {
        for (int c = 0; c < window_width; c++)
        {
            ColourRGBA pixel_colour = get_pixel_colour(image_normalised_escape_step_buffer[r * window_width + c], min_normalised_escape_step);

            uint32_t flat_colour = (pixel_colour.r << 24) | (pixel_colour.g << 16) | (pixel_colour.b << 8) | (pixel_colour.a);
            pixel_buffer[r * window_width + c] = flat_colour;
        }
    }

    // Create a surface for image creation
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormatFrom(
        pixel_buffer, // pointer to our RGBA8888 data
        window_width,
        window_height,
        32,                              // bits per pixel
        window_width * sizeof(uint32_t), // length of each row (in bytes)
        SDL_PIXELFORMAT_RGBA8888);

    if (!surface)
    {
        fprintf(stderr, "SDL_CreateRGBSurfaceWithFormatFrom failed\n");
        free(pixel_buffer);
        return;
    }
    // attempt to save the image
    if (IMG_SavePNG(surface, filename) != 0)
    {
        fprintf(stderr, "IMG_SavePNG failed\n");
    }
    else
    {
        printf("Saved fractal to '%s'\n", filename);
    }

    // clean up
    SDL_FreeSurface(surface);
    free(pixel_buffer);

    return;
}
