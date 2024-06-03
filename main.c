#include "extra.h"

int main(int argc, char *argv[]) {
    if (EXT_initialize(960, 540, "Snake but Good") == 1) {
        printf("Error: failed to initialize SDL");
        return 0;
    }
    
    // Running
    game_state = 1;

    while (game_state == 1) {
        SDL_PollEvent(&events);
        
        if (events.type == SDL_QUIT) {
            game_state = 0;
        }

        SDL_UpdateWindowSurface(main_window);
    }
    
    SDL_DestroyWindow(main_window);
    SDL_Quit();

    return 0;
}