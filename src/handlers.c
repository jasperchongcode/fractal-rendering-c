#include "constants.h"
#include "fractal.h"
#include "render.h"
#include "colour.h"
#include <SDL2/SDL.h>
#include "sdl_helpers.h"

void handle_mouse_move(int x, int y)
{
    // // need to get the centered coords with 0,0 as centre
    // x -= WINDOW_WIDTH / 2;
    // y -= WINDOW_HEIGHT / 2;

    float normalised_x = ((float)x) / WINDOW_WIDTH;
    float normalised_y = ((float)y) / WINDOW_HEIGHT;

    Complex new_c;
    new_c.re = normalised_x * X_MAX + (1 - normalised_x) * X_MIN;
    new_c.im = normalised_y * Y_MAX + (1 - normalised_y) * Y_MIN;

    C = new_c;
    // printf("HANLDING MOUSE MOVE (%f, %f)\n", new_c.re, new_c.im);

    render_fractal();
}

void handle_save_image(void)
{
    // Calculate proportional image height (or could hard code it if wanted)
    int image_height = (int)(((Y_MAX - Y_MIN) / (X_MAX - X_MIN)) * IMAGE_WIDTH);
    render_save_fractal("./output/screenshot.png", IMAGE_WIDTH, image_height);
}

void handle_change_colour_theme(void)
{

    // Change the colour theme
    colour_theme_index = (colour_theme_index + 1) % NUM_COLOUR_THEMES;
    initialise_colour_map();
}