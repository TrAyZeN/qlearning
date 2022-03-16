#include <stdlib.h>
#include <stdio.h>

#include "qtable.h"

static void verify_state(const QTable *qtable, STATE s);
static void verify_action(const QTable *qtable, STATE a);

QTable *init_qtable(STATE state_number, ACTION action_number)
{
    STATE s;
    static QTable *qtable;
    qtable = (QTable *) malloc(sizeof(QTable));
    if (qtable == NULL)
    {
        fprintf(stderr, "Error : Failed to create qtable\n");
        exit(EXIT_FAILURE);
    }

    qtable->state_number = state_number;
    qtable->action_number = action_number;

    qtable->table = (double **) malloc(state_number * sizeof(double *));
    if (qtable->table == NULL)
    {
        fprintf(stderr, "Error : Failed to create table\n");
        exit(EXIT_FAILURE);
    }

    for (s = 0; s < state_number; s++)
    {
        qtable->table[s] = (double *) calloc(action_number, sizeof(double));
        if (qtable->table[s] == NULL)
        {
            fprintf(stderr, "Error : failed to create table row\n");
            exit(EXIT_FAILURE);
        }
    }

    return qtable;
}

void destroy_qtable(QTable *qtable)
{
    STATE s;

    for (s = 0; s < qtable->state_number; s++)
        free(qtable->table[s]);

    free(qtable->table);
    free(qtable);
}

double Q(const QTable *qtable, STATE s, ACTION a)
{
    verify_state(qtable, s);
    verify_action(qtable, a);

    return qtable->table[s][a];
}

double max_Q(const QTable *qtable, STATE s)
{
    verify_state(qtable, s);

    ACTION a;
    double max_q = qtable->table[s][0];

    for (a = 0; a < qtable->action_number; a++)
        if (qtable->table[s][a] > max_q)
            max_q = qtable->table[s][a];

    return max_q;
}

static void verify_state(const QTable *qtable, STATE s)
{
    if (s >= qtable->state_number)
    {
        fprintf(stderr, "Error : State %d is not valid", s);
        exit(EXIT_FAILURE);
    }
}

static void verify_action(const QTable *qtable, STATE a)
{
    if (a >= qtable->action_number)
    {
        fprintf(stderr, "Error : Action %d is not valid", a);
        exit(EXIT_FAILURE);
    }
}

void save_qtable(QTable *qtable, const char *file_path)
{
    STATE s;
    ACTION a;
    FILE *f;

    f = fopen(file_path, "w");
    if (f == NULL)
    {
        fprintf(stderr, "Error : Failed to open file %s", file_path);
        exit(EXIT_FAILURE);
    }

    fprintf(f, "%d %d\n", qtable->state_number, qtable->action_number);

    for (s = 0; s < qtable->state_number; s++)
    {
        fprintf(f, "%lf", qtable->table[s][0]);
        for (a = 1; a < qtable->action_number; a++)
            fprintf(f, " %lf", qtable->table[s][a]);
        fprintf(f, "\n");
    }

    fclose(f);
}

QTable *load_qtable(const char *file_path)
{
    STATE s;
    ACTION a;
    static QTable *qtable;
    FILE *f;

    f = fopen(file_path, "r");
    if (f == NULL)
    {
        fprintf(stderr, "Error : Failed to open file %s", file_path);
        exit(EXIT_FAILURE);
    }

    fscanf(f, "%d %d", &s, &a);
    qtable = init_qtable(s, a);

    for (s = 0; s < qtable->state_number; s++)
    {
        for (a = 0; a < qtable->action_number; a++)
            fscanf(f, "%lf", &qtable->table[s][a]);
    }

    fclose(f);
    return qtable;
}
