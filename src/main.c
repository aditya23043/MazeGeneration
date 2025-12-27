#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>

typedef Uint32 u32;

typedef struct
{
    SDL_Window *win;
    SDL_Renderer *ren;
} _GAME;

typedef struct
{
    int x;
    int y;
    int visited; // bool
    int wall_left; // bool
    int wall_right; // bool
    int wall_up; // bool
    int wall_down; // bool
    int start; // bool
} CELL;

#define WIDTH 800
#define HEIGHT 800
#define NUM_ROWS 16
#define NUM_COLS 16

#define COL_WHITE 50, 50, 50, 255
#define COL_START 0, 255, 255, 255
#define COL_CURRENT 255, 0, 0, 255
#define COL_VISITED_BG 80, 80, 80, 255
#define COL_VISITED_FG 0, 0, 0, 255

#define BORDER(padding) &(SDL_Rect){ \
    (grid[i].x * cell_width) + padding, \
    (grid[i].y * cell_height) + padding, \
    cell_width - (2*padding), \
    cell_height - (2*padding), \
}


CELL grid[NUM_COLS*NUM_ROWS];

int main(int argc, char **argv)
{

    srand(time(NULL));

    _GAME game = {0};

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Error in SDL INIT: %s\n", SDL_GetError());
    }

    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &game.win, &game.ren);
    /* https://wiki.libsdl.org/SDL2/SDL_WindowFlags */

    /* GRID INIT */
    for(int i = 0; i < NUM_ROWS; i++)
    {
        for(int j = 0; j < NUM_COLS; j++)
        {
            CELL cell = {i, j, 0, 1, 1, 1, 1, 0};
            grid[i*NUM_COLS+j] = cell;
        }
    }
    int start_node = rand() % (NUM_COLS*NUM_ROWS);
    grid[start_node].start = 1;

    int running = 1;
    SDL_Event ev = {0};

    int cell_width = WIDTH/NUM_COLS;
    int cell_height = HEIGHT/NUM_ROWS;

    int current_node = start_node;

    /* MAIN LOOP */
    int move = 0;
    while (running)
    {
        /* 1. HANDLE EVENTS <<< */
        while (SDL_PollEvent(&ev))
        {
            if (ev.type == SDL_QUIT)
            {
                running = 0;
            }
            else if(ev.type == SDL_KEYDOWN)
            {
                switch(ev.key.keysym.sym)
                {
                    case SDLK_q:
                        running = 0;
                        break;

                    case SDLK_w:
                        move = 0;
                        break;
                    case SDLK_a:
                        move = 2;
                        break;
                    case SDLK_s:
                        move = 1;
                        break;
                    case SDLK_d:
                        move = 3;
                        break;
                }
            }
        }/* >>> */

        /* 2. UPDATE BUFFER */

        /* base grid <<< */
        SDL_SetRenderDrawColor(game.ren, 0, 0, 0, 255);
        SDL_RenderClear(game.ren);

        SDL_SetRenderDrawColor(game.ren, COL_WHITE);

        for(int i = 0; i < NUM_ROWS * NUM_COLS; i++)
        {
            SDL_Rect temp = {
                grid[i].x * cell_width,
                grid[i].y * cell_height,
                cell_width,
                cell_height,
            };

            if(grid[i].start)
            {
                SDL_SetRenderDrawColor(game.ren, COL_START);
                SDL_RenderDrawRect(game.ren, BORDER(0));
                SDL_RenderDrawRect(game.ren, BORDER(1));
                SDL_RenderDrawRect(game.ren, BORDER(2));
                continue;
            }
            else if(i == current_node)
            {
                SDL_SetRenderDrawColor(game.ren, COL_CURRENT);
                SDL_RenderDrawRect(game.ren, BORDER(0));
                SDL_RenderDrawRect(game.ren, BORDER(1));
                SDL_RenderDrawRect(game.ren, BORDER(2));
                continue;
            }
            else if(grid[i].visited)
            {
                SDL_SetRenderDrawColor(game.ren, COL_VISITED_BG);
                SDL_RenderFillRect(game.ren, &temp);
                SDL_SetRenderDrawColor(game.ren, COL_VISITED_FG);
                SDL_RenderDrawRect(game.ren, &temp);
            } 
            else
            {
                SDL_SetRenderDrawColor(game.ren, COL_WHITE);
                SDL_RenderDrawRect(game.ren, &temp);
            }
        }/* >>> */

        /* find new node <<< */
        move = rand() % 4;
        switch(move)
        {
            case 0: // up
                if(current_node % NUM_ROWS != 0)
                    current_node--;
                break;

            case 1: // down
                if((current_node+1) % NUM_ROWS != 0)
                    current_node++;
                break;

            case 2: // left
                if(current_node > NUM_ROWS)
                    current_node -= NUM_COLS;
                break;

            case 3: // right
                if(current_node < ((NUM_ROWS-1)*NUM_COLS))
                    current_node += NUM_COLS;
                break;
        }/* >>> */

        grid[current_node].visited = 1;
        
        /* 3. DISPLAY */
        SDL_RenderPresent(game.ren);

        SDL_Delay(300);
    }

    return 0;
}
