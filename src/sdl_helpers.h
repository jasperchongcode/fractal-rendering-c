#ifndef SDL_HELPERS_H
#define SDL_HELPERS_H

#include <SDL2/SDL.h>

// extern const int WINDOW_HEIGHT;
extern int game_is_running;

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *texture;

int initialise_window(void);

void destroy_window(void);

void process_input(void);

#endif