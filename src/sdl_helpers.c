#include <SDL2/SDL.h>
#include "./constants.h"
#include "./sdl_helpers.h"

int game_is_running;

SDL_Window *window;
SDL_Renderer *renderer;

int initialise_window(int window_height)
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
        window_height,
        SDL_WINDOW_BORDERLESS);

    printf("WINDOW HEIGHT %d \n", window_height);
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

void destroy_window()
{
    // Done in reverse order to init
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
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
    case SDL_MOUSEMOTION:
        // printf("(%d, %d)", event.motion.x, event.motion.y);
        break;
    }
}