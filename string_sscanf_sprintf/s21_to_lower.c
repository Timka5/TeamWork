#include "s21_string.h"

void *s21_to_lower(char *str) {
  char *result = str;
  for (int i = 0; result[i] != '\0'; ++i) {
    if (result[i] >= 'A' && result[i] <= 'Z') {
      result[i] = result[i] - 'A' + 'a'; // Преобразуем в верхний регистр
    }
  }
  return result;
}