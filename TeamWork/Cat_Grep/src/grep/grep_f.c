#include "grep_f.h"

void open_patterns_file(char* filename, arguments* arg) {
  FILE* f = fopen(arg->filename, "r");
  if (f == NULL) {
    fprintf("grep: %s: No such file or directory", filename);
    return;
  }
  char* stroka = NULL;
  size_t mem_line = 0;
  int read = 0;
  read = getline(&stroka, &mem_line, f);
  while (read != -1) {
    if (stroka[0] == '\n') {
      arg->empty_pattern = 1;
      continue;
    }
    strcpy(arg->patterns[arg->count_p], stroka);
    ++arg->count_p;
    read = getline(&stroka, &mem_line, f);
  }
  fclose(f);
  free(stroka);
}

void arg_par(char** argi, arguments* arg, int* i) {
  for (int j = 0; j < strlen(argi); j++) {
    /* code */
  }
  {
    switch (argi[*i][1]) {
      case 'e':
        ++i;
        strcpy(arg->patterns[arg->count_p], argi[*i]);
        ++arg->count_p;
        break;
      case 'f':
        ++i;
        open_patterns_file(argi[*i], arg);
        break;
      case 'i':
        arg->i = 1;
        break;
      case 'v':
        arg->v = 1;
        break;
      case 'c':
        arg->v = 1;
        break;
      case 'l':
        arg->l = 1;
        break;
      case 'n':
        arg->n = 1;
        break;
      case 'h':
        arg->h = 1;
        break;
      case 's':
        arg->s = 1;
        break;
      case 'o':
        arg->o = 1;
        break;
      default:
        break;
    }
  }
}

arguments args_pars(int arg_c, char** arg_v, arguments* arg) {
  for (int i = 1; i < arg_c; i++) {
    if (arg_v[i][0] == '-') {
      arg_par(arg_v, arg, &i);
    }
  }
  return *arg;
}

char* grep(char* file, arguments* arg) {
  char* line = NULL;
  FILE* f = fopen(file, "r");
  if (f == NULL) {
    fprintf("grep: %s: No such file or directory", file);
    return line;
  }

  return line;
}