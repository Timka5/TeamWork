#ifndef STRUCT_CAT
#define STRUCT_CAT
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>

static struct option long_options[] = {
    {"number-nonblank", no_argument, NULL, 'b'},
    {"number", no_argument, NULL, 'n'},
    {"squeeze-blank", no_argument, NULL, 's'},
    {NULL, 0, NULL, 0} // Конец массива
};

typedef struct{
    char flag;
    int priority;
    bool availability;
}Flag;

Flag flags[] = {
    {'s', 1, false},
    {'n', 2, false},
    {'b', 3, false},
    {'e', 4, false},
    {'t', 5, false},
    {'v', 6, false},
};

#endif