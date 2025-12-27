
#include "main.h"

int main(int argc, char **argv)
{

	GAME game = {0};
	setup(&game);

	while (game.isRunning)
	{
		handle_events( &game );
		draw_base_grid( &game );
		find_new_node( &game );

		SDL_RenderPresent(game.ren);
		SDL_Delay(300);
	}

	return 0;
}

void handle_events(GAME* game)// <<<
{
	while (SDL_PollEvent(&game->ev))
	{
		if (game->ev.type == SDL_QUIT)
		{
			game->isRunning = 0;
		}
		else if(game->ev.type == SDL_KEYDOWN)
		{
			switch(game->ev.key.keysym.sym)
			{
				case SDLK_q:
					game->isRunning = 0;
					break;
			}
		}
	}
}// >>>

void draw_base_grid(GAME* game) /* <<< */
{
	SDL_SetRenderDrawColor(game->ren, 0, 0, 0, 255);
	SDL_RenderClear(game->ren);

	SDL_SetRenderDrawColor(game->ren, COL_WHITE);

	for(int i = 0; i < NUM_ROWS * NUM_COLS; i++)
	{
		SDL_Rect temp = {
			game->grid[i].x * cell_width,
			game->grid[i].y * cell_height,
			cell_width,
			cell_height,
		};

		if(game->grid[i].start)
		{
			SDL_SetRenderDrawColor(game->ren, COL_START);
			SDL_RenderDrawRect(game->ren, BORDER(0));
			SDL_RenderDrawRect(game->ren, BORDER(1));
			SDL_RenderDrawRect(game->ren, BORDER(2));
			continue;
		}
		else if(i == game->current_node)
		{
			SDL_SetRenderDrawColor(game->ren, COL_CURRENT);
			SDL_RenderDrawRect(game->ren, BORDER(0));
			SDL_RenderDrawRect(game->ren, BORDER(1));
			SDL_RenderDrawRect(game->ren, BORDER(2));
			continue;
		}
		else if(game->grid[i].visited)
		{
			SDL_SetRenderDrawColor(game->ren, COL_VISITED_BG);
			SDL_RenderFillRect(game->ren, &temp);
			SDL_SetRenderDrawColor(game->ren, COL_VISITED_FG);
			SDL_RenderDrawRect(game->ren, &temp);
		} 
		else
		{
			SDL_SetRenderDrawColor(game->ren, COL_WHITE);
			SDL_RenderDrawRect(game->ren, &temp);
		}
	}
} /* >>> */

void find_new_node(GAME* game) /* <<< */
{
	game->move = rand() % 4;
	switch(game->move)
	{
		case 0: // up
			if(game->current_node % NUM_ROWS != 0)
				game->current_node = game->current_node - 1;
			break;

		case 1: // down
			if((game->current_node+1) % NUM_ROWS != 0)
				game->current_node = game->current_node + 1;
			break;

		case 2: // left
			if(game->current_node > NUM_ROWS)
				game->current_node = game->current_node - NUM_COLS;
			break;

		case 3: // right
			if(game->current_node < ((NUM_ROWS-1)*NUM_COLS))
				game->current_node = game->current_node +  NUM_COLS;
			break;
	}

	game->grid[game->current_node].visited = 1;
} /* >>> */

void setup(GAME* game)// <<<
{
	srand(time(NULL));

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("Error in SDL INIT: %s\n", SDL_GetError());
	}

	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &game->win, &game->ren);
	/* https://wiki.libsdl.org/SDL2/SDL_WindowFlags */

	/* GRID INIT */
	for(int i = 0; i < NUM_ROWS; i++)
	{
		for(int j = 0; j < NUM_COLS; j++)
		{
			CELL cell = {i, j, 0, 1, 1, 1, 1, 0};
			game->grid[i*NUM_COLS+j] = cell;
		}
	}

	/* choose start node */
	game->start_node = rand() % (NUM_COLS*NUM_ROWS);
	game->grid[game->start_node].start = 1;
}// >>>
