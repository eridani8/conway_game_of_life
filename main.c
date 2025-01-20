#include <stdio.h>
#include <SDL2/SDL.h>

#define WINDOW_NAME "Conway's Game of Life"
#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600

#define CELL_COLOR 0xff882469

int main(void)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,WINDOW_HEIGHT, 0);
    SDL_Surface* surface = SDL_GetWindowSurface(window);

    SDL_Rect rect = {10, 10, 10, 10};
    SDL_FillRect(surface, &rect, CELL_COLOR);
    SDL_UpdateWindowSurface(window);

    SDL_Event event;
    bool game = true;
    while (game)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT || event.type == SDL_APP_TERMINATING)
            {
                game = false;
            }
        }

        SDL_UpdateWindowSurface(window);

        SDL_Delay(100);
    }
}
