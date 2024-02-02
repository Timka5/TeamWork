#include "s21_string.h"

char *s21_strchr(char *str, int c) {
  int str_len = s21_strlen(str);
  char *result = "";
  for (int i = 0; i < str_len; i++) {
    if (str[i] == (char)c) {
      result = &str[i];
      break;
    }
  }
  return result;
}