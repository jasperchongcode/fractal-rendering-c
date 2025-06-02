#ifndef SDL_HELPERS_H
#define SDL_HELPERS_H

#include <SDL2/SDL.h>

extern const int WINDOW_HEIGHT;

extern SDL_Window *window;
extern SDL_Renderer *renderer;

int initialise_window(void);

void destroy_window(void);

#endif