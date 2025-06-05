#include "constants.h"
#include "sdl_helpers.h"
#include "render.h"
#include "colour.h"

void setup(void)
{
	window_is_running = initialise_window();
	initialise_offsets();
	initialise_colour_map();
	render_fractal();
}

int main()
{
	setup();

	printf("Welcome to the Fractal Renderer!\n");
	printf("Keybinds:\n * esc - close the program\n * s - take a high quality screenshot\n * f - toggle the 'in the set colour' between black and the natural progression (black is sometimes poor for photos)\n");
	while (window_is_running)
	{
		process_input();
	}

	destroy_window();
	return 0;
}