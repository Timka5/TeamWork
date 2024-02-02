#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  int len_str1 = s21_strlen(str1);
  int len_str2 = s21_strlen(str2);

  for (int i = 0; i < len_str1; ++i) {
    for (int j = 0; j < len_str2; ++j) {
      if (str1[i] == str2[j]) {
        return i; // Возвращаем позицию первого совпадения
      }
    }
  }
  return len_str1; // Если совпадений нет, возвращаем длину str1
}
