#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>

#include "util/stack.h"

typedef Uint32 u32;

#define WIDTH 800
#define HEIGHT 800
#define NUM_ROWS 16
#define NUM_COLS 16

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

typedef struct
{
	SDL_Window *win;
	SDL_Renderer *ren;
	CELL grid[NUM_COLS * NUM_ROWS];
	int start_node;
	int current_node;
	int isRunning;
	int move;
	SDL_Event ev;
	STACK bt_stack;
} GAME;

#define cell_width WIDTH/NUM_COLS
#define cell_height HEIGHT/NUM_ROWS

#define COL_WHITE 50, 50, 50, 255
#define COL_START 0, 255, 255, 255
#define COL_CURRENT 255, 0, 0, 255
#define COL_VISITED_BG 80, 80, 80, 255
#define COL_VISITED_FG 0, 0, 0, 255

#define BORDER(padding) &(SDL_Rect){ \
	(game->grid[i].x * cell_width) + padding, \
	(game->grid[i].y * cell_height) + padding, \
	cell_width - (2*padding), \
	cell_height - (2*padding), \
}

/* provide seed for random number generation, 
 * initialize SDL, 
 * create window and renderer, 
 * initialize grid, 
 * choose starting node, 
 */
void setup(GAME* game);
void handle_events(GAME* game);
void draw_base_grid(GAME* game);
void find_new_node(GAME* game);
