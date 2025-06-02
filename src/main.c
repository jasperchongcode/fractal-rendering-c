#include <SDL2/SDL.h>
#include "constants.h"
#include "mandelbrot.h"
#include "colour.h"
#include "sdl_helpers.h"

void render_fractal()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black background
	SDL_RenderClear(renderer);

	float pixel_width = (X_MAX - X_MIN) / WINDOW_WIDTH;
	float pixel_height = (Y_MAX - Y_MIN) / WINDOW_HEIGHT;
	// for each pixel, take a representative point in the "top left"

	for (int r = 0; r < WINDOW_HEIGHT; r++)
	{
		for (int c = 0; c < WINDOW_WIDTH; c++)
		{
			// pixel representativ coords (x,y) = (x_min + c*pixel_width, y_min+r*pixel_height)
			float re = X_MIN + c * pixel_width;
			float im = Y_MIN + r * pixel_height;

			// make the representative point the middle of the pixel
			re += pixel_width / 2;
			im += pixel_height / 2;

			EscapeResult escapeResult = verify_in_mandelbrot(re, im);
			ColourRGBA pixel_colour = get_pixel_colour(escapeResult);
			// printf("ESCAPE STEPS: %d, PIXEL COLOUR: %d\n", escapeResult.steps, pixel_colour.r);
			SDL_SetRenderDrawColor(renderer, pixel_colour.r, pixel_colour.g, pixel_colour.b, pixel_colour.a);
			SDL_RenderDrawPoint(renderer, c, r);
		}
	}

	SDL_RenderPresent(renderer); // swap buffers
}

int main()
{
	game_is_running = initialise_window(WINDOW_HEIGHT);

	initialise_colour_map();
	render_fractal();

	while (game_is_running)
	{
		process_input();
		// update();
		// render();
	}

	destroy_window();

	return 0;
}