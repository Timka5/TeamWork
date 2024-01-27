#ifndef CAT_F_H
#define CAT_F_H
#define MAX_NUM_STRINGS 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arguments {
  int b, e, n, s, t, v, count;
  char filename[MAX_NUM_STRINGS][50];
} arguments;

arguments argument_parser(arguments arg, char* arg_v);

arguments arguments_parser(arguments* arg, int arg_c, char** arg_v);

char v_output(char s);

void out_line(char* stroka, int n, arguments* arg);

void out_file(arguments* arg);

#endif