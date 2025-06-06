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

	printf("Keybinds:\n");
	printf(" * esc - close the program\n");
	printf(" * s - take a high quality screenshot\n");
	printf(" * f - toggle the 'in the set colour' between black and the natural progression (black is sometimes poor for photos)\n");
	printf(" * m - toggle using the mouse to change the fractal");

	while (window_is_running)
	{
		process_input();
	}

	destroy_window();
	return 0;
}