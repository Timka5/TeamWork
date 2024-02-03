#include "s21_sprintf.h"

int s21_convert_long_number_to_mantissa(long double *number, int precision) {
  int e = 0;
  if (*number >= 10) {
    while (*number >= 10) {
      *number /= 10.0;
      e += 1;
    }
  } else if (*number < 1 && *number != 0) {
    while (*number < 1) {
      *number *= 10;
      e -= 1;
    }
  }
  *number = round(*number * pow(10, precision)) * pow(10, -precision);
  if (*number >= 10) {
    *number /= 10.0;
    e += 1;
  } else if (*number < 1 && *number != 0) {
    *number *= 10;
    e -= 1;
  }
  return e;
}

unsigned long long convert_from_double_to_long(long double digits,
                                               int precision) {
  unsigned long long long_digits = digits * pow(10, precision);
  digits *= pow(10, precision);
  if ((int)(digits * 10) % 10 >= 5) {
    long_digits++;
  }
  return long_digits;
}

int calculate_length_no_width(t_flags flags, int is_negative, int e) {
  int length = 5;
  length += (e / 10) >= 10;
  int precision = flags.precision == -1 ? 6 : flags.precision;
  if ((flags.type == 'g' || flags.type == 'G') && precision != 0)
    precision--;
  if (is_negative || (!is_negative && flags.sign) ||
      (!is_negative && flags.space && !flags.sign))
    length++;
  if (precision != 0)
    length = length + precision + 1;
  if (precision == 0 && flags.sharp == 1)
    length++;
  return length;
}

int create_right_part_no_mantissa(char *right_part, long double right_digits,
                                  int precision, int delete_zeros,
                                  t_flags *flags) {
  int counter = 0;
  long double right_digits_copy = right_digits;
  right_part[0] = '\0';
  right_part[1] = '\0';
  while (1) {
    if (counter >= precision)
      break;
    counter++;
    right_digits_copy = right_digits_copy * 10;
    if ((unsigned long int)right_digits_copy != 0)
      break;
    s21_putchar_to_str('0', right_part);
  }
  char *right_part_no_zeros;
  unsigned long long right_digits_long =
      convert_from_double_to_long(right_digits, precision);
  right_part_no_zeros = s21_convert(right_digits_long, 10, flags);
  while (right_part_no_zeros[counter]) {
    if (right_part_no_zeros[counter] == '.') {
      right_part_no_zeros[counter] = '\0';
      break;
    }
    counter++;
  }
  int is_right_part_null = 1;
  if ((right_part_no_zeros[0] == '0' && s21_strlen(right_part_no_zeros) == 1) ||
      (right_part_no_zeros[0] == '-' && right_part_no_zeros[1] == '0' &&
       s21_strlen(right_part_no_zeros) == 2)) {
    is_right_part_null = 0;
  }
  int result = 0;
  if (delete_zeros) {
    for (int i = s21_strlen(right_part_no_zeros) - 1;
         right_part_no_zeros[i] == '0'; i--) {
      right_part_no_zeros[i] = '\0';
      result++;
    }
    if (is_right_part_null == 0) {
      for (int i = s21_strlen(right_part) - 1; right_part[i] == '0'; i--) {
        right_part[i] = '\0';
        result++;
      }
    }
  }
  if (is_right_part_null == 1)
    s21_str_fill_with_chars(right_part, right_part_no_zeros);
  return result;
}

int s21_str_fill_with_chars(char *str, char *chars) {
  int counter = 0;
  while (chars[counter]) {
    s21_putchar_to_str(chars[counter], str);
    counter++;
  }
  return counter;
}

void create_right_mantissa_part(char *right_mantissa_part, char letter, int e) {
  right_mantissa_part[0] = '\0';
  right_mantissa_part[1] = '\0';
  s21_putchar_to_str(letter, right_mantissa_part);
  e < 0 ? s21_putchar_to_str('-', right_mantissa_part)
        : s21_putchar_to_str('+', right_mantissa_part);
  char mantissa_number[4];
  gcvt(abs(e), 3, mantissa_number);
  if (abs(e) < 10) {
    mantissa_number[s21_strlen(mantissa_number) + 1] = '\0';
    for (s21_size_t i = s21_strlen(mantissa_number) - 1; i <= 0; i--) {
      mantissa_number[i + 1] = mantissa_number[i];
    }
    mantissa_number[0] = '0';
  }
  int counter = 0;
  while (mantissa_number[counter]) {
    s21_putchar_to_str(mantissa_number[counter], right_mantissa_part);
    counter++;
  }
}

void create_final_str(char *final_str, char *left_part, char *right_part,
                      char *right_mantissa_part, t_flags flags, int is_negative,
                      int length) {
  int precision = flags.precision == -1 ? 6 : flags.precision;
  if ((flags.type == 'g' || flags.type == 'G') && precision != 0)
    precision--;

  if (!flags.left_alig) {
    if ((is_negative || (!is_negative && flags.sign)) && flags.zero_fill) {
      is_negative ? s21_putchar_to_str('-', final_str)
                  : s21_putchar_to_str('+', final_str);
    }
    if (flags.space && !is_negative) {
      s21_putchar_to_str(' ', final_str);
    }
    s21_fill_width(flags.width, length, flags.zero_fill, final_str);
    if ((flags.zero_fill == 0 && is_negative) ||
        (flags.zero_fill == 0 && is_negative == 0 && flags.sign)) {
      is_negative ? s21_putchar_to_str('-', final_str)
                  : s21_putchar_to_str('+', final_str);
    }
  }
  if (flags.left_alig) {
    if (is_negative || (!is_negative && flags.sign)) {
      is_negative ? s21_putchar_to_str('-', final_str)
                  : s21_putchar_to_str('+', final_str);
    }
    if (flags.space && !is_negative) {
      s21_putchar_to_str(' ', final_str);
    }
  }
  s21_str_fill_with_chars(final_str, left_part);
  if (flags.sharp || precision)
    s21_putchar_to_str('.', final_str);
  s21_str_fill_with_chars(final_str, right_part);
  s21_str_fill_with_chars(final_str, right_mantissa_part);
  if (flags.left_alig) {
    s21_fill_width(flags.width, length, flags.zero_fill, final_str);
  }
}

int s21_sprintf_e(long double number, int letter_flag, t_flags *flags,
                  char *str, int delete_zeros) {
  char *final_str = (char *)calloc(100, sizeof(char));
  int precision = flags->precision == -1 ? 6 : flags->precision;
  if ((flags->type == 'g' || flags->type == 'G') && precision != 0)
    precision--;
  int is_negative = number < 0 || (number == 0 && (1 / number) < 0);
  if (is_negative)
    number *= -1;
  char letter = letter_flag ? 'e' : 'E';
  int result = 0;
  int e = s21_convert_long_number_to_mantissa(&number, precision);

  char *left_part_pointer =
      s21_convert(convert_from_double_to_long(number, 1), 10, flags);
  char left_part[2];
  left_part[0] = left_part_pointer[0];
  left_part[1] = '\0';
  char right_part[50];
  right_part[0] = '\0';
  right_part[1] = '\0';
  int length_diff = 0;
  if (precision != 0) {
    long double right_digits =
        (long double)(number - (unsigned long int)number);
    long double temp = right_digits * powl(10, (double)precision);
    if (!delete_zeros || temp != 0) {
      length_diff += create_right_part_no_mantissa(
          right_part, right_digits, precision, delete_zeros, flags);
    } else {
      flags->precision = 0;
    }
  }
  int length = calculate_length_no_width(*flags, is_negative, e) - length_diff;

  char right_mantissa_part[6];
  create_right_mantissa_part(right_mantissa_part, letter, e);
  create_final_str(final_str, left_part, right_part, right_mantissa_part,
                   *flags, is_negative, length);

  if (flags->error)
    result = 0;
  else
    result += s21_str_fill_with_chars(str, final_str);
  free(final_str);
  return result;
}

int s21_sprintf_p(void *pointer, t_flags *flags, char *str) {
  int result = 0;
  if (flags->zero_fill == 1 || flags->sign == 1 || flags->space == 1 ||
      flags->sharp == 1 || flags->length == 1 || flags->precision > -1) {
    flags->error = 1;
  } else {
    char final_str[80] = "\0";
    char *str_number = s21_convert((unsigned long long)pointer, 16, flags);
    int pointer_length = (int)s21_strlen(str_number) + 2;
    if (pointer_length < flags->width && flags->left_alig == 0) {
      s21_fill_width(flags->width, pointer_length, flags->zero_fill, final_str);
    }
    s21_putchar_to_str('0', final_str);
    s21_putchar_to_str('x', final_str);
    s21_str_fill_with_chars(final_str, str_number);
    if (pointer_length < flags->width && flags->left_alig == 1) {
      s21_fill_width(flags->width, pointer_length, flags->zero_fill, final_str);
    }
    result += s21_str_fill_with_chars(str, final_str);
  }
  return result;
}