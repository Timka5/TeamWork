#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  for (s21_size_t i = 0; i < n && src[i] != '\0'; ++i) {
    ((char *)dest)[i] = ((char *)src)[i];
  }
  return dest;
}