#include "cat_f.h"

int main(int arg_c, char* arg_v[]) {
  arguments flags = {0};
  for (int i = 0; i < MAX_NUM_STRINGS; i++) {
    strcpy(flags.filename[i], "");
  }
  flags = arguments_parser(&flags, arg_c, arg_v);
  out_file(&flags);
  return 0;
}