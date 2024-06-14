#ifndef ENTITIES
#define ENTITIES

#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>

struct Vector2D {
    int x;
    int y;
};

struct Image {
    SDL_Surface* handle;
    struct Vector2D size;
};

#endif