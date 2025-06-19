#ifndef HANDLERS_H
#define HANDLERS_H

extern uint8_t run_animation;

void toggle_run_animation(void);

void handle_mouse_move(int x, int y);

void centre_view(int x, int y);

void handle_save_image(void);

void handle_change_colour_theme(void);

void handle_toggle_change_fractal_with_mouse(void);

void handle_toggle_fill_colour(void);

void handle_zoom(int zoom_in);

void handle_reset_view(void);

// can put -1 to cycle
void handle_toggle_fractal(int);

void handle_change_exponential_bias(float);

void handle_change_max_steps(int);

#endif