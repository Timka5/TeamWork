#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  int len_haystack = s21_strlen(haystack);
  int len_needle = s21_strlen(needle);

  for (int i = 0; i <= len_haystack - len_needle; ++i) {
    int j;
    for (j = 0; j < len_needle; ++j) {
      if (haystack[i + j] != needle[j]) {
        break;
      }
    }
    if (j == len_needle) {
      return (char *)&haystack[i];
    }
  }

  return s21_NULL;
}
