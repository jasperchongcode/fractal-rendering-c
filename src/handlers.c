#include "constants.h"
#include "fractal.h"
#include "render.h"
#include "colour.h"
#include <SDL2/SDL.h>
#include "sdl_helpers.h"

uint8_t change_fractal_with_mouse = 1;

int mouse_x = 0;
int mouse_y = 0;

void handle_zoom(int zoom_in)
{
    // todo define some global zoom factor
    float ZOOM_FACTOR = 2;

    if (zoom_in)
    {
    }
    // render_fractal();
}

void handle_toggle_change_fractal_with_mouse(void)
{
    change_fractal_with_mouse = !change_fractal_with_mouse;
}

Complex get_point_from_mouse(int x, int y)
{
    float normalised_x = ((float)x) / WINDOW_WIDTH;
    float normalised_y = ((float)y) / WINDOW_HEIGHT;

    Complex new_c;
    new_c.re = normalised_x * x_max + (1 - normalised_x) * x_min;
    new_c.im = normalised_y * y_max + (1 - normalised_y) * y_min;

    return new_c;
}
void handle_mouse_move(int x, int y)
{
    // // need to get the centered coords with 0,0 as centre
    // x -= WINDOW_WIDTH / 2;
    // y -= WINDOW_HEIGHT / 2;
    // dont handle the movement
    // this is for
    mouse_x = x;
    mouse_y = y;

    if (!change_fractal_with_mouse)
        return;

    C = get_point_from_mouse(x, y);
    // printf("HANLDING MOUSE MOVE (%f, %f)\n", new_c.re, new_c.im);

    render_fractal();
}

void handle_save_image(void)
{
    // Calculate proportional image height (or could hard code it if wanted)
    int image_height = (int)(((DEFAULT_Y_MAX - DEFAULT_Y_MIN) / (DEFAULT_X_MAX - DEFAULT_X_MIN)) * IMAGE_WIDTH);
    render_save_fractal("./output/screenshot.png", IMAGE_WIDTH, image_height);
}

void handle_change_colour_theme(void)
{

    // Change the colour theme
    colour_theme_index = (colour_theme_index + 1) % NUM_COLOUR_THEMES;
    initialise_colour_map();

    render_fractal();
}

void handle_toggle_fill_colour(void)
{
    toggle_fill_colour();
    render_fractal();
}