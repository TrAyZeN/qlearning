#ifndef QTABLE_H_
#define QTABLE_H_

#define STATE unsigned int
#define ACTION unsigned int

typedef struct qtable {
    double **table;
    STATE state_number;
    ACTION action_number;
} QTable;

QTable *init_qtable(STATE state_number, ACTION action_number);
void destroy_qtable(QTable *qtable);

double Q(const QTable *qtable, STATE s, ACTION a);
// #define Q(p_qtable, s, a) (p_qtable->table[s][a])
double max_Q(const QTable *qtable, STATE s);

void _verify_state(const QTable *qtable, STATE s);
void _verify_action(const QTable *qtable, STATE a);

void save_qtable(QTable *qtable, const char *filePath);
void load_qtable(const char *filePath);

#endif
