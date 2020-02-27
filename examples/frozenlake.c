#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "frozenlake.h"

#define COLOR_RESET "\033[0m"
#define BACKGROUND_RED "\033[0;41m"


unsigned int to_index(const State *s)
{
	return s->x + s->y * GRID_WIDTH;
}

bool is_action_valid(const State *s, Action a)
{
	return (s->x != 0 || a != LEFT) && (s->x != GRID_WIDTH-1 || a != RIGHT)
	    && (s->y != 0 || a != UP) && (s->y != GRID_HEIGHT-1 || a != DOWN);
}

State get_next_state(const State *s, Action a)
{
	State new_state = *s;

	switch (a)
	{
		case LEFT:
			new_state.x--;
			break;
		case RIGHT:
			new_state.x++;
			break;
		case UP:
			new_state.y--;
			break;
		case DOWN:
			new_state.y++;
			break;
		default:
			fprintf(stderr, "Error : can't take invalid action\n");
			exit(EXIT_FAILURE);
	}

	return new_state;
}

double get_reward(const State *s)
{
	switch (grid[s->y][s->x])
	{
		case S:
			return 0;
		case F:
			return 0;
		case H:
			return -1;
		case G:
			return 1;
		default:
			fprintf(stderr, "Error : Invalid grid state");
			exit(EXIT_FAILURE);
	}
}

void display_environment(const State *s)
{
	int x, y;

	for (y = 0; y < GRID_HEIGHT; y++)
	{
		for (x = 0; x < GRID_WIDTH; x++)
		{
			if (s->x == x && s->y == y)
				printf("%s%c%s ", BACKGROUND_RED, grid[y][x], COLOR_RESET);
			else
				printf("%c ", grid[y][x]);
		}
		printf("\n");
	}
}
