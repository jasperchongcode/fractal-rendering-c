#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "./constants.h"

SDL_Window *window;
SDL_Renderer *renderer;
int game_is_running;
int last_frame_time = 0;

struct ball
{
	float x;
	float y;
	float width;
	float height;
} ball;

int initialize_window(void)
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
	ball.x = 20;
	ball.y = 20;
	ball.width = 15;
	ball.height = 15;
}

void destroy_window()
{
	// Done in reverse order to init
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

float get_distance_origin(float re, float im)
{
	return sqrt(re * re + im * im);
}

/**
 * @brief  Returns steps until escapes (or max steps)
 *
 * @param x
 * @param y
 * @return int
 */
int verify_in_mandelbrot(float re, float im)
{
	// Defined to escape if at any point it leaves a circle of radius 2

	float z_re = 0;
	float z_im = 0;

	for (int i = 0; i < MAX_STEPS; i++)
	{
		if (get_distance_origin(z_re, z_im) >= 2)
		{
			return i;
		}
		// Otherwise iterate re and im
		// (a+bi)^2 = a^2 +2abi -b^2k
		float z_re_prev = z_re;
		z_re = z_re * z_re - z_im * z_im + re; // re(z)^2 -im(z)^2 + re(c)
		z_im = 2 * z_re_prev * z_im + im;	   // 2*re(z)*im(z) + im(c)
	}

	return MAX_STEPS;
}

void render_fractal()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black background
	SDL_RenderClear(renderer);

	float x_min = -2;
	float x_max = 1;
	float y_min = -1;
	float y_max = 1;

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
			int pixel_colour = (int)((escape_steps / (float)MAX_STEPS) * 255.0f); // get the pixel colour between 0 and 255
			SDL_SetRenderDrawColor(renderer, pixel_colour, pixel_colour, pixel_colour, 255);
			SDL_RenderDrawPoint(renderer, c, r);
		}
	}

	SDL_RenderPresent(renderer); // swap buffers
}

int main()
{
	game_is_running = initialize_window();

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
