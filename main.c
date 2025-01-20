#include <stdio.h>
#include <SDL2/SDL.h>
#include <time.h>

#define WINDOW_NAME "Conway's Game of Life"
#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600

#define CELL_SIZE 20
#define ROWS (WINDOW_HEIGHT / CELL_SIZE)
#define COLUMNS (WINDOW_WIDTH / CELL_SIZE)

#define DEFAULT_COLOR 0x00000000
#define GRID_COLOR 0x97225142
#define CELL_COLOR_TYPE_0 0x17498153
#define CELL_COLOR_TYPE_1 0x13491357
#define CELL_COLOR_TYPE_2 0x17598781

typedef struct
{
    // int type;
    bool is_alive;
    int age;
} Cell;

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

void draw_cell(SDL_Surface* surface, const int x, const int y, const Cell cell)
{
    Uint32 color = DEFAULT_COLOR;
    if (cell.is_alive)
    {
        color = CELL_COLOR_TYPE_0;
        // if (cell.type == 0)
        // {
        //     color = CELL_COLOR_TYPE_0;
        // }
        // else if (cell.type == 1)
        // {
        //     color = CELL_COLOR_TYPE_1;
        // }
        // else if (cell.type == 2)
        // {
        //     color = CELL_COLOR_TYPE_2;
        // }
    }

    const SDL_Rect rect = {x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE};
    SDL_FillRect(surface, &rect, color);
}

void init_matrix(Cell matrix[ROWS][COLUMNS])
{
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLUMNS; col++)
        {
            matrix[row][col].is_alive = rand() % 2;
            matrix[row][col].age = 0;
            // matrix[row][col].type = 0;// rand() % 3;
        }
    }
}

void draw_matrix(SDL_Surface* surface, Cell matrix[ROWS][COLUMNS])
{
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLUMNS; col++)
        {
            const Cell cell = matrix[row][col];
            draw_cell(surface, col, row, cell);
        }
    }
}

int count_neighbors(const int row, const int col, Cell matrix[ROWS][COLUMNS])
{
    int neighbors = 0;
    for (int y = -1; y <= 1; y++)
    {
        for (int x = -1; x <= 1; x++)
        {
            if (y == 0 && x == 0) continue;

            const int newRow = row + y;
            const int newCol = col + x;

            if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLUMNS)
            {
                if (matrix[newRow][newCol].is_alive)
                {
                    neighbors++;
                }
            }
        }
    }

    return neighbors;
}

void simulation_step(Cell matrix[ROWS][COLUMNS])
{
    Cell temp_matrix[ROWS][COLUMNS];

    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLUMNS; col++)
        {
            const int neighbor_count = count_neighbors(row, col, matrix);

            if (matrix[row][col].is_alive)
            {
                if (neighbor_count < 2 || neighbor_count > 3)
                {
                    temp_matrix[row][col].is_alive = false;
                    temp_matrix[row][col].age = 0;
                }
                else
                {
                    temp_matrix[row][col].is_alive = true;
                    temp_matrix[row][col].age = matrix[row][col].age + 1;
                }
            }
            else
            {
                if (neighbor_count == 3)
                {
                    temp_matrix[row][col].is_alive = true;
                }
                else
                {
                    temp_matrix[row][col].is_alive = false;
                }
            }
        }
    }

    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLUMNS; col++)
        {
            matrix[row][col] = temp_matrix[row][col];
        }
    }
}

int main(void)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                                          WINDOW_HEIGHT, 0);
    SDL_Surface* surface = SDL_GetWindowSurface(window);

    SDL_Event event;
    bool run = true;
    Cell matrix[ROWS][COLUMNS];
    init_matrix(matrix);
    Uint32 lastUpdateTime = SDL_GetTicks();
    while (run)
    {
        constexpr Uint32 updateInterval = 500;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT || event.type == SDL_APP_TERMINATING)
            {
                run = false;
            }
            // if (event.type == SDL_MOUSEBUTTONDOWN)
            // {
            //     int mouseX, mouseY;
            //     SDL_GetMouseState(&mouseX, &mouseY);
            //     const int col = mouseX / CELL_SIZE;
            //     const int row = mouseY / CELL_SIZE;
            //     matrix[row][col].is_alive = !matrix[row][col].is_alive;
            // }
        }

        const Uint32 currentTime = SDL_GetTicks();

        if (currentTime - lastUpdateTime >= updateInterval)
        {
            simulation_step(matrix);
            draw_matrix(surface, matrix);
            draw_grid(surface);
            SDL_UpdateWindowSurface(window);

            lastUpdateTime = currentTime;
        }

        SDL_Delay(100);
    }
}
