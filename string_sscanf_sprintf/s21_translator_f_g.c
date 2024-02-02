#include "s21_sprintf.h"

int s21_get_length_for_str(t_flags *flags, int length_digit);

int s21_get_length_for_str(t_flags *flags, int length_digit);
void s21_sprintf_f_add_zero(t_flags *flags, char *temp, int length_int);
void s21_float_in_str(char *temp_convert, char *temp, t_flags *flags,
                      int length_int, long double b);
void s21_fcvt(long double b, t_flags *flags, int length_int, char *temp,
              char *temp_convert);

void s21_sprintf_f_put_in_str(t_flags *flags, int is_Negative,
                              int length_for_str, int length_digit, char *temp,
                              char *str) {
  int has_sign = 0;
  if (flags->left_alig == 1) {
    s21_sprintf_f_putchar_sign(flags, is_Negative,
                               str);
    s21_putchar_array_to_str(temp, length_digit,
                             str);
  }

  if (length_for_str - length_digit > 0) {
    if (flags->left_alig == 0 &&
        flags->zero_fill == 1) {
      s21_sprintf_f_putchar_sign(flags, is_Negative, str);
      has_sign = 1;
    }
    s21_fill_width(flags->width, length_digit, flags->zero_fill,
                   str);
  }
  if (flags->left_alig == 0) {
    if (!has_sign) s21_sprintf_f_putchar_sign(flags, is_Negative, str);
    s21_putchar_array_to_str(temp, length_digit,
                             str);
  }
}

int s21_get_length_for_str(t_flags *flags, int length_digit) {
  int length = 0;
  if (flags->width > length_digit) {
    length = flags->width;
  } else {
    length = length_digit;
  }

  return length;
}

int s21_get_length_int(int b) {
  int i = 0;
  do {
    b /= 10;
    i++;
  } while (b != 0);
  return i;
}

void s21_sprintf_f_putchar_sign(t_flags *flags, int is_Negative, char *str) {
  if (is_Negative)
    s21_putchar_to_str('-', str);
  else if (flags->sign == 1)
    s21_putchar_to_str('+', str);
  else if (flags->space == 1)
    s21_putchar_to_str(' ', str);
}

void s21_putchar_array_to_str(char *temp, int length_digit, char *str) {
  for (int i = 0; i < length_digit; i++) {
    s21_putchar_to_str(temp[i], str);
  }
}

int s21_sprintf_f_remove_zero(char *temp, int length_int) {
  int cnt = 0;
  for (int i = s21_strlen(temp) - 1; i >= length_int; i--) {
    if (temp[i] == '0' || temp[i] == '.') {
      temp[i] = '\0';
      cnt++;
    } else {
      break;
    }
  }
  return cnt;
}

int s21_sprintf_f(long double b, t_flags *flags, char *str) {
  int is_Negative = 0, length_for_str = 0, sign = 0, length_int = 0,
      length_digit = 0;

  if (flags->space != 0 || flags->sign != 0 || b < 0) sign = 1;
  if (flags->precision == -1) flags->precision = 6;

  if (b < 0) {
    is_Negative = 1;
    b *= -1;
  }

  length_int = s21_get_length_int((int)b);
  length_digit = length_int + flags->precision + sign;
  if (flags->precision != 0 || flags->sharp != 0) length_digit++;
  length_for_str = s21_get_length_for_str(flags, length_digit);

  char *temp_convert = s21_NULL, *temp = s21_NULL;
  temp = (char *)calloc((length_for_str + 1), sizeof(char));
  if (!temp) exit(0);

  s21_float_in_str(temp_convert, temp, flags, length_int, b);

  if ((flags->type == 'g' || flags->type == 'G') && flags->sharp == 0) {
    int remove_zero = s21_sprintf_f_remove_zero(temp, length_int);
    flags->precision -= remove_zero;
    length_digit = s21_strlen(temp) + sign;
    length_for_str = s21_get_length_for_str(flags, length_digit);
  }
  s21_sprintf_f_put_in_str(flags, is_Negative, length_for_str, length_digit,
                           temp, str);

  free(temp);
  return length_for_str;
}

void s21_float_in_str(char *temp_convert, char *temp, t_flags *flags,
                      int length_int, long double b) {
  if (flags->precision == 0) {
    temp_convert = s21_convert(b, 10, flags);

    s21_str_fill_with_chars(temp, temp_convert);
    if (flags->sharp == 1)
      temp[length_int] = '.';
  } else {
    s21_fcvt(b, flags, length_int, temp, temp_convert);
  }
}

void s21_fcvt(long double b, t_flags *flags, int length_int, char *temp,
              char *temp_convert) {
  long double frac = b - (int)b;
  temp_convert = s21_convert((int)b, 10, flags);
  s21_str_fill_with_chars(temp, temp_convert);

  s21_size_t len = s21_strlen(temp);
  temp[len] = '.';
  temp[len + 1] = '\0';

  int prec_copy = flags->precision;
  if (frac < 0.1) {
    temp[len + 1] = '0';
    temp[len + 2] = '\0';
  }

  int j = 1;
  long double num = 0.1;
  while (j < flags->precision) {
    if (frac < num) {
      temp[len + j] = '0';
      temp[len + j + 1] = '\0';
      j++;
      num *= 0.1;
    } else {
      break;
    }
  }
  while (prec_copy != 0) {
    frac *= 10;
    prec_copy--;
  }

  if ((unsigned long long)(frac * 10) % 10 >= 5) frac++;

  temp_convert = s21_convert((unsigned long long)frac, 10, flags);
  s21_strncat(temp, temp_convert, len);
  s21_sprintf_f_add_zero(flags, temp, length_int);
}

void s21_sprintf_f_add_zero(t_flags *flags, char *temp, int length_int) {
  int i = 0;
  if ((flags->precision > 0 && temp[length_int] == '\0') ||
      (flags->precision == 0 && flags->sharp == 1))
    temp[length_int] = '.';

  for (; i < flags->precision; i++) {
    if (temp[length_int + 1 + i] == '\0') {
      temp[length_int + 1 + i] = '0';
    }
  }
  temp[length_int + 1 + i + 1] = '\0';
}

int s21_sprintf_g(long double b, t_flags *flags, char *str) {
  int res;
  if (flags->precision == -1)
    flags->precision = 6;
  else if (flags->precision == 0)
    flags->precision = 1;

  long double b_copy = b;
  if (b_copy < 0)
    b_copy *= -1;

  int e = s21_convert_long_number_to_mantissa(
      &b_copy, flags->precision);
  if (flags->precision > e && e >= -4) {
    flags->precision -= (e + 1);
    res = s21_sprintf_f(b, flags, str);
  } else {
    res = s21_sprintf_e(b, flags->type == 'g', flags, str, flags->sharp == 0);
  }
  return res;
}

void s21_write_error(char *str, int *length) {
    *length = 0;
    str[0] = '\0';
    char error[17] = "INCORRECT INPUT\n";
    int i = 0;
    while (i != 17) {
        write(1, &error[i], 1);
        i++;
    }
}