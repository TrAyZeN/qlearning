#include <stdlib.h>
#include <stdio.h>

#include "qlearning.h"
#include "qtable.h"

ACTION choose_random_action(const QTable *qtable)
{
    return rand() % qtable->action_number;
}

ACTION choose_best_action(const QTable *qtable, STATE s)
{
    ACTION best_action, a;
    double best_quality;

    best_action = 0;
    best_quality = 0.0;
    for (a = 0; a < qtable->action_number; a++)
    {
        if (Q(qtable, s, a) > best_quality)
        {
            best_action = a;
            best_quality = Q(qtable, s, a);
        }
    }

    return best_action;
}

void udpate_qtable(QTable *qtable, STATE s, ACTION a, STATE new_s,
                   const HyperParameters *hp, double reward)
{
    qtable->table[s][a] = qtable->table[s][a]
        + hp->alpha * (reward + hp->gamma * max_Q(qtable, new_s) - qtable->table[s][a]);
}
