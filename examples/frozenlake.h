#ifndef FROZENLAKE_H_
#define FROZENLAKE_H_

#include <stdbool.h>

#define GRID_WIDTH 8
#define GRID_HEIGHT 8

#define S 'S' // Starting point, safe
#define F 'F' // Frozen surface, safe
#define H 'H' // Hole, fall to your doom
#define G 'G' // Goal, where the frisbee is located

static const char grid[GRID_HEIGHT][GRID_WIDTH] = {
    {S, F, F, F, F, F, F, F},
    {F, F, F, F, F, F, F, F},
    {F, F, F, H, F, F, F, F},
    {F, F, F, F, F, H, F, F},
    {F, F, F, H, F, F, F, F},
    {F, H, H, F, F, F, H, F},
    {F, H, F, F, H, F, H, F},
    {F, F, F, H, F, F, F, G}
};

typedef struct state {
    int x;
    int y;
} State;

unsigned int to_index(const State *state);

#define INITIAL_STATE (State) { 0, 0 }

#define ACTION_NUMBER 4

typedef enum action {
    LEFT,
    RIGHT,
    UP,
    DOWN
} Action;

bool is_action_valid(const State *s, Action a);

State get_next_state(const State *s, Action a);
double get_reward(const State *s);

void display_environment(const State *s);

#endif
