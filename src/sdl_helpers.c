#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> // for saving image to file
#include "constants.h"
#include "render.h"
#include "sdl_helpers.h"
#include "fractal.h"
#include "colour.h"
#include "handlers.h"

int window_is_running;

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;

int initialise_window()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "Error initialising SDL.\n");
        return FALSE;
    }
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == 0)
    {
        fprintf(stderr, "Error initialising IMG.\n");
        return FALSE;
    }

    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS);

    printf("WINDOW HEIGHT %d \n", WINDOW_HEIGHT);
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
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!texture)
    {
        fprintf(stderr, "Error creating SDL Texture.\n");
        return FALSE;
    }
    return TRUE;
}

void destroy_window()
{
    // Done in reverse order to init
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

void move_mouse_centre(void)
{
    SDL_WarpMouseInWindow(window, (int)(WINDOW_WIDTH / 2), (int)(WINDOW_HEIGHT / 2));
}

void process_input(void)
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        window_is_running = FALSE;
        break;
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            window_is_running = FALSE;
            break;
        case SDLK_s:
            handle_save_image();
            break;
        case SDLK_f:
            handle_toggle_fill_colour();
            break;
        case SDLK_t:
            // handle toggling colour themese
            handle_change_colour_theme();
            break;
        case SDLK_m:
            // toggle using mouse to change the julia fractal
            handle_toggle_change_fractal_with_mouse();
            break;
        case SDLK_i:
            // Handle zoom in
            handle_zoom(1);
            move_mouse_centre();
            break;
        case SDLK_o:
            // handle zoom out
            handle_zoom(0);
            move_mouse_centre();
            break;
        case SDLK_r:
            // Handle reset view window
            handle_reset_view();
            break;
        }

        break;
    case SDL_MOUSEMOTION:
        // printf("(%d, %d)", event.motion.x, event.motion.y);
        handle_mouse_move(event.motion.x, event.motion.y);
        break;
    }
}