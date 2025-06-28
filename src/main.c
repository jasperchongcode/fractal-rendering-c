#include "constants.h"
#include "sdl_helpers.h"
#include "handlers.h"
#include "render.h"
#include "colour.h"
#include "math.h"

void setup(void)
{
	window_is_running = initialise_window();
	initialise_offsets();
	initialise_colour_map();
	render_fractal();
}

void update(void)
{
	if (!run_animation)
	{
		return;
	}

	double radius = 1.1;
	static double angle = 0.0;
	double angle_step = 0.01;
	// Update the position in a circle
	angle += angle_step;
	C.re = radius * cos(angle);
	C.im = radius * sin(angle);
	render_fractal();
	// printf("Change C (%f, %f)\n", C.im, C.re);
}

int main()
{
	setup();

	printf("Keybinds:\n");
	printf(" * esc - close the program\n");
	printf(" * s - take a high quality screenshot\n");
	printf(" * t - toggle the colour theme.\n");
	printf(" * f - toggle the 'in the set colour' between black and the natural progression (black is sometimes poor for photos)\n");
	printf(" * m - toggle using the mouse to change the fractal.\n");
	printf(" * i - zoom in to mouse location by ZOOM_FACTOR and reset mouse to centre (this also disables using mouse to change fractal).\n");
	printf(" * o - same as above but zooms out instead.\n");
	printf(" * I/O - same as above but zooms by larger factor.\n");
	printf(" * n - cycle to next fractal.\n");
	printf(" * 1 - switch to julia set.\n");
	printf(" * 2 - switch to mandelbrot set.\n");
	printf(" * 3 - switch to burning ship set.\n");
	printf(" * , and . - decrease and increase exponential colour bias respectively\n"); // write a readme explaining what this does
	printf(" * < and > decrease and increase the maximum calculated escape steps respectively\n");
	printf(" * [mouse down] - centre view on mouse.\n");
	printf(" * a - toggle animation (julia set).\n");
	printf(" * g - get details about the window location and points and log to terminal.\n");
	// suggested workflow
	// if too dark / too light change exp bias
	// if run into black (or in set) blobs increase max escape steps
	// move the mouse in the julia set to find a nice one then use m to lock it
	// zoom in to find a nice photo then adjust settings nad colout settings then take a screenshot
	// unlock m and swap between julia and mandelbrot to see how inside the mandelbrot is a filled julia

	while (window_is_running)
	{
		process_input();
		update(); // Uncomment to have animation option
	}

	destroy_window();
	return 0;
}