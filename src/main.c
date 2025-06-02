#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "./constants.h"
#include "./mandelbrot.h"
#include "./colour.h"

const int WINDOW_HEIGHT = (int)((y_max - y_min) / (x_max - x_min) * WINDOW_WIDTH);

SDL_Window *window;
SDL_Renderer *renderer;
int game_is_running;
int last_frame_time = 0;

int initialise_window(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Error initialising SDL.\n");
		return FALSE;
	}
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_BORDERLESS);
	if (!window)
	{
		fprintf(stderr, "Error creating SDL.\n");
		return FALSE;
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		fprintf(stderr, "Error creating SDL Renderer.\n");
		return FALSE;
	}
	return TRUE;
}

void process_input(void)
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		game_is_running = FALSE;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			game_is_running = FALSE;
		}
		break;
	}
}

void setup()
{
	initialise_colour_map();
}

void destroy_window()
{
	// Done in reverse order to init
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void render_fractal()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black background
	SDL_RenderClear(renderer);

	float pixel_width = (x_max - x_min) / WINDOW_WIDTH;
	float pixel_height = (y_max - y_min) / WINDOW_HEIGHT;
	// for each pixel, take a representative point in the "top left"

	for (int r = 0; r < WINDOW_HEIGHT; r++)
	{
		for (int c = 0; c < WINDOW_WIDTH; c++)
		{
			// pixel representativ coords (x,y) = (x_min + c*pixel_width, y_min+r*pixel_height)
			float re = x_min + c * pixel_width;
			float im = y_min + r * pixel_height;
			// todo make some draw pixel function
			int escape_steps = verify_in_mandelbrot(re, im);
			ColourRGBA pixel_colour = get_pixel_colour(escape_steps);
			// printf("ESCAPE STEPS: %d, PIXEL COLOUR: %d\n", escape_steps, pixel_colour);
			SDL_SetRenderDrawColor(renderer, pixel_colour.r, pixel_colour.g, pixel_colour.b, pixel_colour.a);
			SDL_RenderDrawPoint(renderer, c, r);
		}
	}

	SDL_RenderPresent(renderer); // swap buffers
}

int main()
{
	game_is_running = initialise_window();

	setup();
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
