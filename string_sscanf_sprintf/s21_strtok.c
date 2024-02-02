#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *ptr = s21_NULL;
  if (str != s21_NULL)
    ptr = str;

  if (ptr == s21_NULL || *ptr == '\0')
    return s21_NULL;

  char *token_start = ptr;
  char *token_end = s21_strpbrk(ptr, delim);

  if (token_end != s21_NULL) {
    *token_end = '\0';
    ptr = token_end + 1;
  } else {
    ptr = s21_NULL;
  }

  return token_start;
}