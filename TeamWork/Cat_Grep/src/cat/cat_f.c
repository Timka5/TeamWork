#include "cat_f.h"

arguments argument_parser(arguments arg, char* arg_v) {
  if (arg_v[1] == '-') {
    if (!strcmp(arg_v, "--number-nonblank")) {
      arg.b = 1;
      return arg;
    } else if (!strcmp(arg_v, "--squeeze-blank")) {
      arg.s = 1;
      return arg;
    } else if (!strcmp(arg_v, "--number")) {
      arg.n = 1;
      return arg;
    }
  }
  for (size_t j = 1; j < strlen(arg_v); j++) {
    switch (arg_v[j]) {
      case 'b':
        arg.b = 1;
        arg.n = 0;
        break;
      case 'e':
        arg.e = 1;
        arg.v = 1;
        break;
      case 'n':
        if (!arg.b) {
          arg.n = 1;
        }
        break;
      case 's':
        arg.s = 1;
        break;
      case 't':
        arg.t = 1;
        arg.v = 1;
        break;
      case 'E':
        arg.e = 1;
        break;
      case 'T':
        arg.t = 1;
        break;
      case 'v':
        arg.v = 1;
        break;
      default:
        fprintf(stderr, "Error flag\n");
        exit(EXIT_FAILURE);
        break;
    }
  }
  return arg;
}
arguments arguments_parser(arguments* arg, int arg_c, char** arg_v) {
  for (int i = 1; i < arg_c; i++) {
    if (arg_v[i][0] == '-') {
      *arg = argument_parser(*arg, arg_v[i]);
    } else {
      strcpy(arg->filename[arg->count], arg_v[i]);
      arg->count++;
    }
  }
  return *arg;
}

char v_output(char s) {
  if (s == '\n' || s == '\t') return s;
  if (s < 0) {
    printf("M-");
    s = s & 0x7F;
  }
  if (s <= 31) {
    putchar('^');
    s += 64;
  } else if (s == 127) {
    putchar('^');
    s = '?';
  }
  return s;
}

void out_line(char* stroka, int n, arguments* arg) {
  for (int i = 0; i < n; i++) {
    if (arg->t && stroka[i] == '\t') printf("^I");
    if (arg->e && stroka[i] == '\n') putchar('$');
    if (arg->v) stroka[i] = v_output(stroka[i]);
    putchar(stroka[i]);
  }
}

void out_file(arguments* arg) {
  // for (int i = 0; i < arg->count; i++) {
  //   printf("%d\t%s\n", i, arg->filename[i]);
  // }
  int n_counter = 1, b_counter = 1, empty = 0;
  char ch_last = ' ';
  for (int i = 0; i < arg->count; i++) {
    FILE* f = fopen(arg->filename[i], "r");
    if (f == NULL) {
      fprintf(stderr, "cat: %s: No such file or directory\n", arg->filename[i]);
      continue;
    }
    char* stroka = NULL;
    size_t mem_line = 0;
    int read = 0;
    read = getline(&stroka, &mem_line, f);
    if (ch_last != '\n' && i != 0) {
      out_line(stroka, read, arg);
      read = getline(&stroka, &mem_line, f);
    }

    while (read != -1) {
      if (stroka[0] == '\n') ++empty;
      if (stroka[0] == '\n' && empty > 1 && arg->s) {
        read = getline(&stroka, &mem_line, f);
        continue;
      }
      if (stroka[0] != '\n' && empty > 0 && arg->s) empty = 0;
      if (arg->b && stroka[0] != '\n') {
        printf("%6d\t", b_counter);
        out_line(stroka, read, arg);
        ++b_counter;
        empty = 0;
      } else if (arg->b) {
        out_line(stroka, read, arg);
      } else if (arg->n) {
        printf("%6d\t", n_counter);
        out_line(stroka, read, arg);
        ++n_counter;
      } else
        out_line(stroka, read, arg);
      ch_last = stroka[strlen(stroka) - 1];
      read = getline(&stroka, &mem_line, f);
    }
    fclose(f);
    free(stroka);
  }
}