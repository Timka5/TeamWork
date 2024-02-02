#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  int len_str1 = s21_strlen(str1);
  int len_str2 = s21_strlen(str2);
  for (int i = 0; i < len_str1; ++i) {
    for (int j = 0; j < len_str2; ++j) {
      if (str1[i] == str2[j]) {
        return (char *)&str1[i];
      }
    }
  }
  return s21_NULL;
}