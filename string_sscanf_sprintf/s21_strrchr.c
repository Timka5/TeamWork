#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  int len_str = s21_strlen(str);
  for (int i = len_str; i >= 0; --i) {
    if (str[i] == c) {
      return (char *)&str[i];
    }
  }
  return NULL;
}
