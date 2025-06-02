#include <SDL2/SDL.h>
#include "constants.h"
#include "fractal.h"
#include "colour.h"
#include "sdl_helpers.h"
#include "main.h"

Complex C = {1, 1};

void render_fractal(void)
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
			Complex point;
			// pixel representativ coords (x,y) = (x_min + c*pixel_width, y_min+r*pixel_height)
			point.re = X_MIN + c * pixel_width;
			point.im = Y_MIN + r * pixel_height;

			// make the representative point the middle of the pixel
			point.re += pixel_width / 2;
			point.im += pixel_height / 2;

			EscapeResult escapeResult = verify_in_julia(point, C); // using julia instea dof mandelbrot
			// EscapeResult escapeResult = verify_in_mandelbrot(point);
			ColourRGBA pixel_colour = get_pixel_colour(escapeResult);
			// printf("ESCAPE STEPS: %d, PIXEL COLOUR: %d\n", escapeResult.steps, pixel_colour.r);
			SDL_SetRenderDrawColor(renderer, pixel_colour.r, pixel_colour.g, pixel_colour.b, pixel_colour.a);
			SDL_RenderDrawPoint(renderer, c, r);
		}
	}

	SDL_RenderPresent(renderer); // swap buffers
	printf("RENDERED NEW FRACTAL\n");
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