#include "s21_string.h"
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef S21_SSCANF_H_
#define S21_SSCANF_H_

typedef enum w_t { NONE_WIDTH, WIDTH_NUMBER, WIDTH_SUP } w_t;

typedef enum l_t {
  NONE_LENGTH,
  LENGTH_SHORT,
  LENGTH_LONG,
  LENGTH_LONG_LONG,
  LENGTH_DOUBLE,
  LENGTH_LONG_DOUBLE
} l_t;

typedef struct format {
  void *address;
  w_t width;
  unsigned int width_num;
  l_t length;
  char buff[512];
  char specifier;
} format;

int s21_sscanf(const char *buf, const char *frmt, ...);
int check_EOF(const char *src);
format parse_format(char **fstr, va_list *va);
void skip_spaces(char **str);
void parse_width(char **frmtstr, format *param);
int parse_number(char **frmtstr);
void parse_length(char **frmtstr, format *param);
void parse_specifier(char **frmtstr, format *param);
void write_formats_to_memory(char **str, format *param, int formats_len,
                             int *res);
void write_char(char **str, int *res, format *param, int *fail);
void write_int(char **str, int *fail_flag, int *res, format *param);
void write_chars_to_buff(char **str, const char *chars, char *buff,
                         __int16_t width, int start_ind);
unsigned long long int strntollu(const char *string, char **endptr, int basis,
                                 int n_byte);
void int_converter(format *param, long long int result, int sign);
void write_unspec_int(char **str, int *fail_flag, int *res, format *param);
void write_float(char **str, int *res, format *param);
void float_converter(format *param, long double result);
void unsigned_converter(format *param, unsigned long long int result, int sign);
void skip_chars_in_buffer(char **src, int *fail, format *param);
void write_string(char **str, const int *fail_flag, int *res, format *param);
void write_unsigned(char **str, int *fail_flag, int *res, format *param);
void write_hex_oct(char **str, int *fail_flag, int *res, format *param,
                   int base);
#endif