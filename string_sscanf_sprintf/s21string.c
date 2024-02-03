#include <stdio.h>
#include <stdlib.h>

int s21_strlen(char *str) {
  int len = 0;
  while (str[len] != '\0') {
    ++len;
  }
  return len;
}

void *to_upper(char *str) {
  char *result = str;
  for (int i = 0; result[i] != '\0'; ++i) {
    if (result[i] >= 'a' && result[i] <= 'z') {
      result[i] = result[i] - 'a' + 'A'; // Преобразуем в верхний регистр
    }
  }
  return result;
}

void *to_lower(char *str) {
  char *result = str;
  for (int i = 0; result[i] != '\0'; ++i) {
    if (result[i] >= 'A' && result[i] <= 'Z') {
      result[i] = result[i] - 'A' + 'a'; // Преобразуем в верхний регистр
    }
  }
  return result;
}

//реализация insert, как в с#, но не как в задании
// void *insert(char *res, char *str, size_t start_index){
//     if (s21_strlen(res) == 0) return "NULL";
//     char *src = res, prom[s21_strlen(src) - start_index];
//     int len = 0;
//     for(int i = start_index; i < s21_strlen(src); i++){
//         prom[i - start_index] = src[i];
//         len++;
//     }
//     // Найти конец dest
//     while (start_index) {
//         src++;
//         start_index--;
//     }
//     // Копировать src в dest, вставляя его в конец
//     while (*str != '\0') {
//         *src = *str;
//         src++;
//         str++;
//     }
//     for(int i = 0; i < len; i++){
//         *src = prom[i];
//         src++;
//     }
//     // Добавить NULL-терминатор в конец склеенной строки
//     *src = '\0';
//     return src;
// }

char *s21_insert(char *src, char *str, size_t start_index) {
  if (s21_strlen(src) == 0 || (int)start_index > s21_strlen(src))
    return NULL;

  size_t result_size = s21_strlen(src) + s21_strlen(str) + 1;
  char *result = (char *)malloc(result_size * sizeof(char));
  if (result == NULL) {
    return NULL;
  }

  int i, j;

  for (i = 0; i < (int)start_index; i++) {
    result[i] = src[i];
  }

  for (j = 0; j < s21_strlen(str); j++) {
    result[i + j] = str[j];
  }

  for (i = start_index; src[i] != '\0'; i++) {
    result[i + j] = src[i];
  }

  result[i + j] = '\0';
  return result;
}

int is_trim_char(const char *trim_chars, char c) {
  while (*trim_chars != '\0') {
    if (*trim_chars == c) {
      return 1;
    }
    trim_chars++;
  }
  return 0;
}

char *trim(const char *src, const char *trim_chars) {
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

int main() {
  char str[] = "eeddddff ";
  char scr[] = "VVVV";
  char *z, *g;
  z = to_upper(str);
  g = to_lower(scr);
  char *f, q[1] = {'f'};
  f = trim("  ffqwqcxve]] ", q);
  printf("%s\n", f);
  printf("%s\n", z);
  printf("%s\n", g);
  printf("%s\n", f);
  free(f);
}