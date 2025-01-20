#include <stdio.h>
#include <SDL2/SDL.h>

#define WINDOW_NAME "Conway's Game of Life"
#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600

#define CELL_SIZE 30
#define COLUMNS (WINDOW_WIDTH / CELL_SIZE)
#define ROWS (WINDOW_HEIGHT / CELL_SIZE)

#define GRID_COLOR 0x97225142
#define CELL_COLOR 0x17498153

void draw_grid(SDL_Surface* surface)
{
    for (int row = 0; row < ROWS; row++)
    {
        SDL_Rect row_line = {0, row * CELL_SIZE, WINDOW_WIDTH, 1};
        SDL_FillRect(surface, &row_line, GRID_COLOR);
        for (int col = 0; col < COLUMNS; col++)
        {
            SDL_Rect col_line = {col * CELL_SIZE, row * CELL_SIZE, 1, CELL_SIZE};
            SDL_FillRect(surface, &col_line, GRID_COLOR);
        }
    }
}

void fill_cell(SDL_Surface* surface, int x, int y)
{
    SDL_Rect rect = {x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE};
    SDL_FillRect(surface, &rect, CELL_COLOR);
}

int main(void)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,WINDOW_HEIGHT, 0);
    SDL_Surface* surface = SDL_GetWindowSurface(window);

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
        draw_grid(surface);
        fill_cell(surface, 10, 10);
        SDL_UpdateWindowSurface(window);
        SDL_Delay(100);
    }
}
