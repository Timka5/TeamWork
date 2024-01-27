#ifndef GREP_F_H
#define GREP_F_H
#define MAX 256

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arguments {
  int i, v, c, l, n, h, s, o, count_p, count_f, empty_pattern;
  char patterns[MAX][MAX];
  char filename[MAX][50];
} arguments;

arguments args_pars(int arg_c, char** arg_v, arguments* arg);

void open_patterns_file(char* filename, arguments* arg);

#endif