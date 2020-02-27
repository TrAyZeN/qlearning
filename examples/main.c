#include <stdlib.h>
#include <stdio.h>
#include "frozenlake.h"
#include "qlearning.h"
#include "utils.h"

int main()
{
	int episode, step;

	HyperParameters hp;
	hp.max_episodes = 100000;
	hp.max_step_per_episode = 30;
	hp.epsilon = 1.0;
	hp.epsilon_rate = 1.0 / 100000;
	hp.alpha = 0.1;
	hp.gamma = 0.1;

	QTable *qtable = init_qtable(GRID_WIDTH * GRID_HEIGHT, ACTION_NUMBER);
	State state, next_state;
	Action action;

	for (episode = 0; episode < hp.max_episodes; episode++)
	{
		state = INITIAL_STATE;

		for (step = 0; step < hp.max_step_per_episode; step++)
		{
			if (((double) rand() / RAND_MAX) <= hp.epsilon)	// exploration
				action = choose_random_action(qtable);
			else											// exploitation
				action = choose_best_action(qtable, to_index(&state));

			if (!is_action_valid(&state, action))
			{
				qtable->table[to_index(&state)][action] = -1;
				break;
			}

			next_state = get_next_state(&state, action);

			udpate_qtable(qtable, to_index(&state), action,
				to_index(&next_state), &hp, get_reward(&next_state));

			state = next_state;

			display_environment(&state);
			move_cursor_up(GRID_HEIGHT);
			// sleep_ms(10);
		}

		hp.epsilon -= hp.epsilon_rate;
	}

	move_cursor_down(GRID_WIDTH);
	save_qtable(qtable, "qtable");

	destroy_qtable(qtable);
	return 0;
}

