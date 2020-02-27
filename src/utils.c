#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "utils.h"

void move_cursor_up(int v)
{
    printf("\033[%dA", v);
}

void move_cursor_down(int v)
{
    printf("\033[%dB", v);
}

void sleep_ms(int milliseconds)
{
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}
