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
        case SDLK_a:
            toggle_run_animation();
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
            if (event.key.keysym.mod & KMOD_SHIFT)
            {
                handle_zoom(-ZOOM_INCREASE_FACTOR * ZOOM_FACTOR);
            }
            else
            {
                handle_zoom(-ZOOM_FACTOR);
            }
            move_mouse_centre();
            break;
        case SDLK_o:
            // handle zoom out
            if (event.key.keysym.mod & KMOD_SHIFT)
            {
                handle_zoom(ZOOM_INCREASE_FACTOR * ZOOM_FACTOR);
            }
            else
            {
                handle_zoom(ZOOM_FACTOR);
            }
            move_mouse_centre();
            break;
        case SDLK_r:
            // Handle reset view window
            handle_reset_view();
            break;
        case SDLK_g:
            // Log the current window range and point locations
            print_complex_location();
            break;
        case SDLK_n:
            // cycle to next fractal
            handle_toggle_fractal(-1);
            break;
        case SDLK_1:
            handle_toggle_fractal(0);
            break;
        case SDLK_2:
            handle_toggle_fractal(1);
            break;
        case SDLK_3:
            handle_toggle_fractal(2);
            break;
        case SDLK_COMMA:
            // for decreasing escape steps if "<"
            if (event.key.keysym.mod & KMOD_SHIFT)
            {
                // printf("decrease escape steps and rerender\n");
                handle_change_max_steps(-50);
            }
            else
            {
                // printf("decrease exp bias and rerender");
                handle_change_exponential_bias(-0.1f);
            }
            break;
        case SDLK_PERIOD:
            // for increase escape steps if ">"
            if (event.key.keysym.mod & KMOD_SHIFT)
            {
                // printf("increase escape steps and rerender");
                handle_change_max_steps(50); // todo consider making this a multiply e.g. double or half
            }
            else
            {
                // printf("increase exp bias and rerender");
                handle_change_exponential_bias(0.1f);
            }
            break;
        }

        break;
    case SDL_MOUSEMOTION:
        // printf("(%d, %d)", event.motion.x, event.motion.y);
        handle_mouse_move(event.motion.x, event.motion.y);
        break;
    case SDL_MOUSEBUTTONDOWN:
        centre_view(event.motion.x, event.motion.y);
        move_mouse_centre();
        break;
    }
}