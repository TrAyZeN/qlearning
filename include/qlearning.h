#ifndef QLEARNING_H_
#define QLEARNING_H_

#include "qtable.h"

typedef struct hyperParameters {
    int max_episodes;
    int max_step_per_episode;
    double epsilon;             // exploration rate
    double epsilon_rate;        // update rate for the epsilon
    double alpha;               // learning rate
    double gamma;               // discount rate
} HyperParameters;

ACTION choose_random_action(const QTable *qtable);
ACTION choose_best_action(const QTable *qtable, STATE s);

void udpate_qtable(QTable *qtable, STATE s, ACTION a, STATE new_s, HyperParameters *hp, double reward);

#endif
