#include "s21_string.h"

void *s21_to_upper(char *str) {
    char *result = str;
    for (int i = 0; result[i] != '\0'; ++i) {
        if (result[i] >= 'a' && result[i] <= 'z') {
            result[i] = result[i] - 'a' + 'A'; // Преобразуем в верхний регистр
        }
    }
    return result;
}
