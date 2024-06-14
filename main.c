#include "game.h"
#include "entities.h"

struct Grid {
    struct Vector2D size;
    Uint8 scale;
};

struct Snake {
    Uint16 size;

    // 0 = Right; 1 = Left; 2 = Up; 3 = Down;
    Uint8 direction;
    Uint8 move_buffer[32]; // List of directions

    struct Vector2D position_head;
    struct Vector2D position_body[31];
};

int main(int argc, char* argv[]) {
    /* === INITIALIZATION === */
    if (EXT_initialize(960, 540, "Snake but Good") == 1) {
        printf("Error: failed to initialize SDL");
        return 0;
    }
    
    // Running
    Uint8 game_state = 1;
    Uint64 game_delta = 17;
    Uint64 delta_timeout = 0;

    int tick_count = 0;
    int tick_limit = 60;

    struct Grid grid;
    grid.scale = 64;
    grid.size.x = 10;
    grid.size.y = 10;

    struct Snake snake;
    snake.size = 2;
    snake.direction = 0;
    snake.position_head.x = 5;
    snake.position_head.y = 5;

    Uint8 snake_previous_direction = 0;

    SDL_Rect drawing_rect;

    Uint32 color_darkgreen = SDL_MapRGB(main_surface->format, 0x00, 0x82, 0x00);

    delta_timeout = SDL_GetTicks64();
    /* === MAIN LOOP === */
    while (game_state == 1) {
        /* == LOGIC == */
        if (SDL_GetTicks64() >= delta_timeout) {
            delta_timeout = SDL_GetTicks64() + game_delta;

            /* == EVENTS == */
            SDL_PollEvent(&events);

            if (events.type == SDL_QUIT) {
                game_state = 0;
            }

            if (events.type == SDL_KEYUP) {
                switch (events.key.keysym.sym) {
                    case SDLK_w:
                        snake_previous_direction = snake.direction;
                        snake.direction = 3;
                        break;

                    case SDLK_a:
                        snake_previous_direction = snake.direction;
                        snake.direction = 1;
                        break;

                    case SDLK_s:
                        snake_previous_direction = snake.direction;
                        snake.direction = 2;
                        break;

                    case SDLK_d:
                        snake_previous_direction = snake.direction;
                        snake.direction = 0;
                        break;
                }
            }

            tick_count++;
            if (tick_count >= tick_limit) {
                tick_count = 0;
                
                if (snake.direction > 3) {
                    snake.direction = 3;
                }

                switch (snake.direction){
                    case 0:
                        snake.position_head.x++;
                        break;

                    case 1:
                        snake.position_head.x--;
                        break;

                    case 2:
                        snake.position_head.y++;
                        break;

                    case 3:
                        snake.position_head.y--;
                        break;
                }

                if (snake.size > 0) {
                    for (int i = snake.size;i > 1;i--) {
                        snake.move_buffer[i + 1] = snake.move_buffer[i];
                    }

                    snake.move_buffer[1] = snake.move_buffer[0];

                    if (snake.direction != snake_previous_direction) {
                        snake.move_buffer[0] = snake.direction;
                    }
                }
            }

        }

        /* == DRAWING == */
        SDL_FillRect(main_surface, NULL, base_colors[0]);

        drawing_rect.x = snake.position_head.x * grid.scale;
        drawing_rect.y = snake.position_head.y * grid.scale;
        drawing_rect.w = grid.scale;
        drawing_rect.h = grid.scale;
        SDL_FillRect(main_surface, &drawing_rect, color_darkgreen);

        if (snake.size > 1) {
            for (int i = 1; i < snake.size;i++) {
                switch (snake.move_buffer[i]) {
                    case 0:
                        drawing_rect.x = (snake.position_head.x + i) * grid.scale;
                        drawing_rect.y = snake.position_head.y * grid.scale;
                        break;

                    case 1:
                        drawing_rect.x = (snake.position_head.x - i) * grid.scale;
                        drawing_rect.y = snake.position_head.y * grid.scale;
                        break;

                    case 2:
                        drawing_rect.x = snake.position_head.x * grid.scale;
                        drawing_rect.y = (snake.position_head.y + i) * grid.scale;
                        break;

                    case 3:
                        drawing_rect.x = snake.position_head.x * grid.scale;
                        drawing_rect.y = (snake.position_head.y - i) * grid.scale;
                        break;
                }

                drawing_rect.w = grid.scale;
                drawing_rect.h = grid.scale;
                SDL_FillRect(main_surface, &drawing_rect, base_colors[2]);
                
            }
        }

        SDL_UpdateWindowSurface(main_window);
    }
    
    SDL_DestroyWindow(main_window);
    SDL_Quit();

    return 0;
}