#include "s21_string.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void strrev(char *str) {
  char *start = str;
  char *end = str + ы21_strlen(str) - 1;
  while (end > start) {
    char temp = *start;
    *start = *end;
    *end = temp;
    ++start;
    --end;
  }
}

int int_to_str(char *buffer, int num) {
  int digits = 0;
  do {
    *buffer++ = num % 10 + '0';
    num /= 10;
    digits++;
  } while (num != 0);
  strrev(buffer - digits);
  return digits;
}

char *precision_format(char specifier, int precision, void *value) {
  switch (specifier) {
  case 'd':
  case 'i':
  case 'o':
  case 'u':
  case 'x':
  case 'X': {
    int num = *(int *)value;
    int abs_num = num < 0 ? -num : num;
    int num_digits = 1;
    while (abs_num /= 10)
      num_digits++;
    int padding = precision - num_digits;
    char *buffer = malloc(padding + num_digits + 1);
    char *ptr = buffer;
    if (num < 0) {
      *ptr++ = '-';
    }
    while (padding--) {
      *ptr++ = '0';
    }
    do {
      *ptr++ = (num % 10) + '0';
      num /= 10;
    } while (num);
    *ptr = '\0';
    strrev(buffer);
    char *p = buffer;
    strcpy((char *)value, buffer);
    return p;
    break;
  }
  case 'e':
  case 'E':
  case 'f': {
    double num = *(double *)value;
    char *buffer = malloc(precision + 10);
    char *ptr = buffer;
    int exponent = 0;
    if (num != 0) {
      while (fabs(num) < 1.0) {
        num *= 10.0;
        exponent--;
      }
      while (fabs(num) >= 10.0) {
        num /= 10.0;
        exponent++;
      }
    }
    if (specifier == 'f') {
      int int_part = (int)num;
      ptr += int_to_str(ptr, int_part);
      num -= int_part;
      if (precision > 0) {
        *ptr++ = '.';
        while (precision--) {
          num *= 10.0;
          int digit = (int)num;
          *ptr++ = digit + '0';
          num -= digit;
        }
      }
    } else {
      *ptr++ = num < 0 ? '-' : '+';
      num = fabs(num);
      int digit = (int)num;
      *ptr++ = digit + '0';
      num -= digit;
      if (precision > 0) {
        *ptr++ = '.';
        while (precision--) {
          num *= 10.0;
          digit = (int)num;
          *ptr++ = digit + '0';
          num -= digit;
        }
      }
      *ptr++ = 'e';
      if (exponent < 0) {
        *ptr++ = '-';
        exponent = -exponent;
      } else {
        *ptr++ = '+';
      }
      ptr += int_to_str(ptr, exponent);
    }
    *ptr = '\0';
    char *p = buffer;
    strcpy((char *)value, buffer);
    return p;
    break;
  }
  case 'g':
  case 'G': {
    double num = *(double *)value;
    char *buffer = malloc(precision + 10);
    char *ptr = buffer;
    int exponent = 0;
    if (num != 0) {
      while (fabs(num) < 1.0) {
        num *= 10.0;
        exponent--;
      }
      while (fabs(num) >= 10.0) {
        num /= 10.0;
        exponent++;
      }
    }
    if (exponent >= -4 && exponent <= precision) {
      int int_part = (int)num;
      ptr += int_to_str(ptr, int_part);
      num -= int_part;
      if (precision > 0) {
        *ptr++ = '.';
        while (precision--) {
          num *= 10.0;
          int digit = (int)num;
          *ptr++ = digit + '0';
          num -= digit;
        }
      }
    } else {
      int int_part = (int)num;
      ptr += int_to_str(ptr, int_part);
      num -= int_part;
      if (precision > 0) {
        *ptr++ = '.';
        while (precision--) {
          num *= 10.0;
          int digit = (int)num;
          *ptr++ = digit + '0';
          num -= digit;
        }
      }
      *ptr++ = 'e';
      if (exponent < 0) {
        *ptr++ = '-';
        exponent = -exponent;
      } else {
        *ptr++ = '+';
      }
      ptr += int_to_str(ptr, exponent);
    }
    *ptr = '\0';
    char *p = buffer;
    strcpy((char *)value, buffer);
    return p;
    break;
  }
  default:
    break;
  }
}

int main() {
  int i_value = 12345;
  double f_value = 123.456;
  char *d;

  d = precision_format('d', 8, &i_value);
  printf("Formatted integer value: %s\n",
         d); //После срабатывания функции добавить отчиску памяти!!!!

  d = precision_format('f', 5, &f_value);
  printf("Formatted floating point value: %s\n", d);

  return 0;
}