#ifndef SRC_S21_SPRINTF_H_
#define SRC_S21_SPRINTF_H_
#include <math.h>
#include <stdarg.h>
#include <unistd.h>
#include "s21_string.h"

#if defined(__APPLE__)
#define FLAG_ERROR 1
#elif defined(__linux__)
#define FLAG_ERROR 0
#endif

typedef struct flags {
  int type;
  int left_alig;
  int zero_fill;
  int width;
  int star;
  int precision;
  int sign;
  int space;
  int sharp;
  int length;
  int error;
  int caps_lock;
} t_flags;

int s21_read_str(char *str, const char *format, va_list av);
t_flags s21_init_flags(void);
int s21_putchar_to_str(const char c, char *str);
void s21_write_error(char *str, int *length);
void check_struct(t_flags *flags);
char *s21_convert(unsigned long long num, int base, t_flags *flags);
int s21_read_flags(const char *format, int i, t_flags *flags, va_list args);
int s21_check_flags(t_flags *flags);
int s21_is_digit(int c);
int s21_is_specifier(int c);
int s21_get_number(const char *format, int *i);
int s21_translator(int c, t_flags *flags, va_list args, char *str);
int s21_sprintf_c(int c, t_flags *flags, char *str);
int s21_sprintf_s(char *s, t_flags *flags, char *str);
int s21_sprintf_x(unsigned long c, int check, t_flags *flags, char *str);
int s21_sprintf_o(unsigned long c, t_flags *flags, char *str);
int s21_sprintf_u(unsigned int u, t_flags *flags, char *str);
int s21_sprintf_d_i(int d, t_flags *flags, char *str);
int s21_fill_width(int width, int lenght, int has_zero_fill, char *str);
int s21_putstring_to_str(char *s, char *str);
int s21_convert_long_number_to_mantissa(long double *number, int precision);
int calculate_length_no_width(t_flags flags, int is_negative, int e);
int create_right_part_no_mantissa(char *right_part, long double right_digits,
                                  int precision, int delete_zeros,
                                  t_flags *flags);
void create_right_mantissa_part(char *right_mantissa_part, char letter, int e);
void create_final_str(char *final_str, char *left_part, char *right_part,
                      char *right_mantissa_part, t_flags flags, int is_negative,
                      int length);
int s21_sprintf_e(long double number, int letter_flag, t_flags *flags,
                  char *str, int delete_zeros);
int s21_str_fill_with_chars(char *str, char *chars);
int s21_sprintf_nan_inf(t_flags *flags, char *str, int nan, int is_negative);
int s21_sprintf_g(long double b, t_flags *flags, char *str);
void s21_check_specifier_caps_lock(t_flags *flags);
int s21_sprintf_f(long double b, t_flags *flags, char *str);
int s21_get_length_int(int b);
void s21_sprintf_f_putchar_sign(t_flags *flags, int is_Negative, char *str);
void s21_putchar_array_to_str(char *temp, int length_digit, char *str);
int s21_putstr_to_str(char *c, char *str);
void s21_sprintf_f_put_in_str(t_flags *flags, int is_Negative,
                              int length_for_str, int length_digit, char *temp,
                              char *str);
int s21_sprintf_f_proceccing_nan_inf(long double b, t_flags *flags,
                                     int *length_for_str, char *str);
int s21_sprintf_prc(t_flags *flags, char *str);
int s21_check_flags_for_n(t_flags *flags);
int s21_sprintf_p(void *pointer, t_flags *flags, char *str);
int s21_sprintf_u(unsigned int u, t_flags *flags, char *str);
int s21_sprintf_d_i(int d, t_flags *flags, char *str);
void s21_while_loop1(int arg1, int d, int arg3, int *i, char fill, char *str);
void s21_while_loop2(int arg1, int u, int *i, char fill, char *str);
void s21_while_loop3(int arg1, int arg2, int arg3, int *i, char fill,
                     char *str);
char *s21_to_positive(int d);
char *s21_u_itoa(unsigned int n);
char *s21_gen(char *rtn, int nbr, int len, int isneg);
int s21_get_length(int n);

#endif  // SRC_S21_SPRINTF_H_