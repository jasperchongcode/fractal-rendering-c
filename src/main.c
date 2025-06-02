#include <stdio.h>
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

void update()
{
	// Waste some time until next frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), last_frame_time + FRAME_TARGET_TIME))
		;
	// Logic to keep a fixed timestamp

	last_frame_time = SDL_GetTicks();
	ball.x++;
	ball.y++;
}

void render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// Draw a rectangle
	SDL_Rect ball_rect = {(int)ball.x, (int)ball.y, (int)ball.width, (int)ball.height};

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &ball_rect);

	SDL_RenderPresent(renderer); // Swap the buffers
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

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	for (int r = 0; r < WINDOW_HEIGHT; r++)
	{
		for (int c = 0; c < WINDOW_WIDTH; c++)
		{
			// pixel representativ coords (x,y) = (x_min + c*pixel_width, y_min+r*pixel_height)
			// todo make some draw pixel function
			if (x_min + c * pixel_width >= 0)
			{
				SDL_RenderDrawPoint(renderer, c, r);
			}
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
