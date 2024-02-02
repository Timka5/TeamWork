#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  int end_dest = s21_strlen(dest);
  s21_size_t src_ind = 0;

  while (src[src_ind] != '\0' && src_ind != n) {
    dest[end_dest] = src[src_ind];
    ++end_dest;
    ++src_ind;
  }
  dest[end_dest] = '\0';
  return dest;
}