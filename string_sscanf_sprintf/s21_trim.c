#include "s21_string.h"

int is_trim_char(const char *trim_chars, char c) {
  while (*trim_chars != '\0') {
    if (*trim_chars == c) {
      return 1;
    }
    trim_chars++;
  }
  return 0;
}

char *s21_trim(const char *src, const char *trim_chars) {
  if (src == NULL || trim_chars == NULL) {
    return NULL;
  }

  // Находим длину строки src
  int src_len = 0;
  while (src[src_len] != '\0') {
    src_len++;
  }

  // Находим позицию первого символа, не являющегося trim_chars
  int start_index = 0;
  while (start_index < src_len && is_trim_char(trim_chars, src[start_index])) {
    start_index++;
  }

  // Находим позицию последнего символа, не являющегося trim_chars
  int end_index = src_len - 1;
  while (end_index > start_index && is_trim_char(trim_chars, src[end_index])) {
    end_index--;
  }

  // Определяем длину подстроки без начальных и конечных trim_chars
  int result_len = end_index - start_index + 1;

  // Выделяем память для результирующей строки
  char *result = (char *)malloc((result_len + 1) * sizeof(char));
  if (result == NULL) {
    return NULL;
  }

  // Копируем подстроку без начальных и конечных trim_chars в result
  for (int i = start_index; i <= end_index; i++) {
    result[i - start_index] = src[i];
  }
  result[result_len] = '\0'; // добавляем нулевой символ в конец строки

  return result;
}