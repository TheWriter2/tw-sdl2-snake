#ifndef EXTRA
#define EXTRA

#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>

SDL_Window *main_window = NULL;
SDL_Surface *main_surface = NULL;
SDL_Event events;

Uint32 base_colors[8];

int game_state;

int EXT_initialize(int window_x, int window_y, char *window_title) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        main_window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_x, window_y, SDL_WINDOW_SHOWN);
        main_surface = SDL_GetWindowSurface(main_window);

        // Black
        base_colors[0] = SDL_MapRGB(main_surface->format, 0x00, 0x00, 0x00);
        // Blue
        base_colors[1] = SDL_MapRGB(main_surface->format, 0x00, 0x00, 0xFF);
        // Green
        base_colors[2] = SDL_MapRGB(main_surface->format, 0x00, 0xFF, 0x00);
        // Cyan
        base_colors[3] = SDL_MapRGB(main_surface->format, 0x00, 0xFF, 0xFF);
        // Red
        base_colors[4] = SDL_MapRGB(main_surface->format, 0xFF, 0x00, 0x00);
        // Pink
        base_colors[5] = SDL_MapRGB(main_surface->format, 0xFF, 0x00, 0xFF);
        // Yellow
        base_colors[6] = SDL_MapRGB(main_surface->format, 0xFF, 0xFF, 0x00);
        // White
        base_colors[7] = SDL_MapRGB(main_surface->format, 0xFF, 0xFF, 0xFF);

        SDL_FillRect(main_surface, NULL, base_colors[7]);
        return 0;
    }

    return 1;
}

#endif