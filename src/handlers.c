#include "constants.h"
#include "fractal.h"
#include "render.h"
#include "colour.h"
#include <SDL2/SDL.h>
#include "sdl_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// float ZOOM_FACTOR = 2;

uint8_t change_fractal_with_mouse = 1;
uint8_t run_animation = 0;

int mouse_x = 0;
int mouse_y = 0;

void toggle_run_animation(void)
{
    run_animation = !run_animation;
    change_fractal_with_mouse = 0;
}

void print_complex_location(void)
{
    printf("----RANGE----\n");
    printf("Top Left: (%.17f, %.17f)\n", x_min, y_max);
    printf("Bottom Right: (%.17f, %.17f)\n", x_max, y_min);
    printf("----POINTS----\n");
    printf("Centre Point: (%.17f, %.17f)\n", x_min + ((x_max - x_min) / 2), y_min + ((y_max - y_min) / 2));
    printf("C (For Julia): (%.17f, %.17f)\n", C.re, C.im);
}

Complex get_point_from_mouse(int x, int y)
{
    double normalised_x = ((double)x) / WINDOW_WIDTH;
    double normalised_y = ((double)y) / WINDOW_HEIGHT;

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

void handle_zoom(float zoom_factor)
{
    // Make it so the fractal is locked when zooming by default
    change_fractal_with_mouse = 0;

    Complex point = get_point_from_mouse(mouse_x, mouse_y);

    // Set the proper scaling factor depending on if its zooming in or out
    float scaling_factor = zoom_factor;
    if (zoom_factor < 0)
    {
        scaling_factor = 1 / -zoom_factor;
    }

    double temp_x_min = x_min;
    double temp_x_max = x_max;
    double temp_y_min = y_min;
    double temp_y_max = y_max;

    // "shift" the main window to the origin by subtracting the centre point (move the centre point of existing window to origin)
    // First find the centre of the existing window
    double centre_x = (x_max + x_min) / 2;
    double centre_y = (y_max + y_min) / 2;
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

void centre_view(int x, int y)
{
    // Make it so the fractal is locked when moving by default
    change_fractal_with_mouse = 0;

    Complex point = get_point_from_mouse(mouse_x, mouse_y);

    // Shift window center to origin, then move to (point.re, point.im)
    double dx = point.re - (x_max + x_min) / 2;
    double dy = point.im - (y_max + y_min) / 2;

    x_min += dx;
    x_max += dx;
    y_min += dy;
    y_max += dy;

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
// index is optional
void handle_toggle_fractal(int index)
{
    // dont let fractal change
    // change_fractal_with_mouse = 0;
    if (index < 0)
    {
        fractal_index = (fractal_index + 1) % NUM_FRACTALS;
    }
    else
    {
        fractal_index = index;
    }

    render_fractal();
}

void handle_change_exponential_bias(float change)
{
    if (exponential_bias + change < 0)
    {
        exponential_bias = 0;
    }
    else
    {

        exponential_bias += change;
    }
    printf("Exponential Bias: %f\n", exponential_bias);
    render_fractal();
}

void handle_change_max_steps(int change)
{

    if (max_steps + change <= 0)
    {
        max_steps = 1;
    }
    else
    {
        max_steps += change;
    }
    printf("Max Escape Steps: %d\n", max_steps);

    render_fractal();
}

int string_state_length = 1 + 6 * 24 + 4 + 4 + 2 + 9 + 1;

char *
get_string_location()
{

    // save in form fractal_index|x_min|x_max|y_min|y_max|C_re|C_im|max_steps|exponential_bias|colour_theme_index
    // assume 1 char for fractal number, 4 chars for escape steps, 4 chars exp bias (sign+num+.+after), assume two char colour themee
    // 1. get length of string

    char *str = malloc(string_state_length);
    // 2.
    // todo use malloc free
    snprintf(str, string_state_length, "%d|%.17f|%.17f|%.17f|%.17f|%.17f|%.17f|%d|%.1f|%d", fractal_index, x_min, x_max, y_min, y_max, C.re, C.im, max_steps, exponential_bias, colour_theme_index);
    return str;
}

void handle_log_state()
{
    printf("Current state:\n");
    char *current_state_str = get_string_location();
    printf("%s\n", current_state_str);
    free(current_state_str);
}

void handle_load_state()
{
    char *input_str = malloc(string_state_length);
    printf("Enter state input:\n");

    scanf("%s", input_str);

    // if its of size 1 or 0 then skip
    if (strlen(input_str) <= 1)
    {
        printf("Null input detected");
        return;
    }

    char *token = strtok(input_str, "|");
    int i = 0;

    while (token != NULL)
    {
        switch (i)
        {
        case 0:
            fractal_index = atoi(token);
            break;
        case 1:
            x_min = strtod(token, NULL);
            break;
        case 2:
            x_max = strtod(token, NULL);
            break;
        case 3:
            y_min = strtod(token, NULL);
            break;
        case 4:
            y_max = strtod(token, NULL);
            break;
        case 5:
            C.re = strtod(token, NULL);
            break;
        case 6:
            C.im = strtod(token, NULL);
            break;
        case 7:
            max_steps = atoi(token);
            break;
        case 8:
            exponential_bias = strtof(token, NULL);
            break;
        case 9:
            colour_theme_index = atoi(token);
            break;
        }
        // printf("%s, %d\n", token, i);
        token = strtok(NULL, "|");
        i++;
    }
    initialise_colour_map();
    render_fractal();
    change_fractal_with_mouse = 0;
    free(input_str);
    printf("Finished loading.\n");
}