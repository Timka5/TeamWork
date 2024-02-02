#include "s21_string.h"

char *s21_insert(char *src, char *str, size_t start_index) {
    if (s21_strlen(src) == 0 || (int)start_index > s21_strlen(src)) return NULL;

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