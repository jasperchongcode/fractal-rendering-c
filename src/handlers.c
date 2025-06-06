#include "constants.h"
#include "fractal.h"
#include "render.h"
#include "colour.h"
#include <SDL2/SDL.h>
#include "sdl_helpers.h"

float ZOOM_FACTOR = 2;

uint8_t change_fractal_with_mouse = 1;

int mouse_x = 0;
int mouse_y = 0;

Complex get_point_from_mouse(int x, int y)
{
    float normalised_x = ((float)x) / WINDOW_WIDTH;
    float normalised_y = ((float)y) / WINDOW_HEIGHT;

    Complex new_c;
    new_c.re = normalised_x * x_max + (1 - normalised_x) * x_min;
    new_c.im = normalised_y * y_max + (1 - normalised_y) * y_min;

    return new_c;
}

// function for setting the view bounds to default
void handle_reset_view(void)
{

    // Make it so the fractal is locked when zooming by default
    change_fractal_with_mouse = 0;

    x_max = DEFAULT_X_MAX;
    x_min = DEFAULT_X_MIN;
    y_max = DEFAULT_Y_MAX;
    y_min = DEFAULT_Y_MIN;

    render_fractal();
}

void handle_zoom(int zoom_in)
{
    // Make it so the fractal is locked when zooming by default
    change_fractal_with_mouse = 0;

    Complex point = get_point_from_mouse(mouse_x, mouse_y);

    // Set the proper scaling factor depending on if its zooming in or out
    float scaling_factor = ZOOM_FACTOR;
    if (zoom_in)
    {
        scaling_factor = 1 / ZOOM_FACTOR;
    }

    float temp_x_min = x_min;
    float temp_x_max = x_max;
    float temp_y_min = y_min;
    float temp_y_max = y_max;

    // "shift" the main window to the origin by subtracting the centre point (move the centre point of existing window to origin)
    // First find the centre of the existing window
    float centre_x = (x_max + x_min) / 2;
    float centre_y = (y_max + y_min) / 2;
    // Then shift the existing window to the centre
    temp_x_max -= centre_x;
    temp_x_min -= centre_x;
    temp_y_max -= centre_y;
    temp_y_min -= centre_y;
    // Scale the size of the existing window
    temp_x_max *= scaling_factor;
    temp_x_min *= scaling_factor;
    temp_y_max *= scaling_factor;
    temp_y_min *= scaling_factor;
    // Move the scaled window to the mouse x and y position
    temp_x_max += point.re;
    temp_x_min += point.re;
    temp_y_max += point.im;
    temp_y_min += point.im;

    // Reassign the variables
    x_min = temp_x_min;
    x_max = temp_x_max;
    y_min = temp_y_min;
    y_max = temp_y_max;

    render_fractal();
}

void handle_toggle_change_fractal_with_mouse(void)
{
    change_fractal_with_mouse = !change_fractal_with_mouse;
}

void handle_mouse_move(int x, int y)
{
    // // need to get the centreed coords with 0,0 as centre
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