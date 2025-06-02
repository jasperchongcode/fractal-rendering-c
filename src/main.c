#include "constants.h"
#include "sdl_helpers.h"
#include "render.h"
#include "colour.h"

int main()
{
	game_is_running = initialise_window();
	initialise_offsets();
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