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

	while (window_is_running)
	{
		process_input();
	}

	destroy_window();
	return 0;
}