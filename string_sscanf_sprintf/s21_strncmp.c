#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
  for (s21_size_t i = 0;
       i < n && (*((char *)str1 + i) != '\0' || *((char *)str2 + i) != '\0');
       ++i) {
    if (*((char *)str1 + i) != *((char *)str2 + i)) {
      result = *((char *)str1 + i) - *((char *)str2 + i);
      break;
    }
  }
  return result;
}