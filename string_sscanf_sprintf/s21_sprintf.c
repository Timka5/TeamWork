#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
  str[0] = '\0';
  str[1] = '\0';
  va_list args;
  int result;
  if (str == s21_NULL) {
    result = -1;
  } else {
    va_start(args, format);
    result = s21_read_str(str, format, args);
    va_end(args);
  }
  return result;
}

int s21_read_str(char *str, const char *format, va_list args) {
  t_flags flags;
  int result;
  int i;

  result = 0;
  i = -1;
  while (format[++i]) {
    if (format[i] != '%') {
      result += s21_putchar_to_str(format[i], str);
    } else if (format[i] == '%' && format[i + 1]) {
      i++;
      flags = s21_init_flags();
      i = s21_read_flags(format, i, &flags, args);
      if (flags.error == 1) {
        if (FLAG_ERROR == 1) {
          s21_write_error(str, &result);
        }
        break;
      } else {
        result += s21_translator(flags.type, &flags, args, str);
        if (flags.error == 1) {
          if (FLAG_ERROR == 1) {
            s21_write_error(str, &result);
          }
          break;
        }
      }
    }
  }
  return result;
}

int s21_putchar_to_str(const char c, char *str) {
  while (*str) {
    str++;
  }

  *str = c;
  str++;
  *str = '\0';
  return 1;
}

t_flags s21_init_flags(void) {
  t_flags flags;
  flags.type = 0;
  flags.left_alig = 0;
  flags.zero_fill = 0;
  flags.width = 0;
  flags.star = 0;
  flags.precision = -1;
  flags.sign = 0;
  flags.space = 0;
  flags.sharp = 0;
  flags.length = 0;
  flags.error = 0;
  flags.caps_lock = 0;
  return flags;
}

char *s21_convert(unsigned long long num, int base, t_flags *flags) {
  static char Representation1[] = "0123456789abcdef";
  static char Representation2[] = "0123456789ABCDEF";
  static char buffer[50];
  char *ptr;

  ptr = &buffer[49];
  *ptr = '\0';
  if (flags->type == 'x' || flags->type == 'o' || flags->type == 'p') {
    do {
      *--ptr = Representation1[num % base];
      num /= base;
    } while (num != 0);
  } else {
    do {
      *--ptr = Representation2[num % base];
      num /= base;
    } while (num != 0);
  }
  return (ptr);
}

int s21_read_flags(const char *format, int i, t_flags *flags, va_list args) {
  int has_width = 0;
  int has_precision = 0;
  while (format[i]) {
    if (format[i] == '-' && has_width == 0 && has_precision == 0) {
      flags->left_alig = 1;
    } else if (format[i] == '+' && has_width == 0 && has_precision == 0) {
      flags->sign = 1;
    } else if (format[i] == ' ' && has_width == 0 && has_precision == 0) {
      flags->space = 1;
    } else if (format[i] == '#' && has_width == 0 && has_precision == 0) {
      flags->sharp = 1;
    } else if (format[i] == '0' && has_width == 0 && has_precision == 0) {
      flags->zero_fill = 1;
    } else if ((s21_is_digit(format[i]) || format[i] == '*') &&
               has_precision == 0 && flags->precision == -1 &&
               flags->width == 0) {
      has_width = 1;
      if (s21_is_digit(format[i])) {
        flags->width = s21_get_number(format, &i);
      } else {
        flags->width = va_arg(args, int);
        if (flags->width < 0) {
          flags->zero_fill = 0;
          flags->left_alig = 1;
          flags->width *= -1;
        }
      }
    } else if (format[i] == '.' && flags->precision == -1 &&
               has_precision == 0) {
      has_precision = 1;
      if (!s21_is_digit(format[i + 1]) && format[i + 1] != '*') {
        flags->precision = 0;
      } else if (s21_is_digit(format[++i])) {
        flags->precision = s21_get_number(format, &i);
      } else {
        flags->precision = va_arg(args, int);
        if (flags->precision < 0) {
          flags->precision = -1;
        }
      }
    } else if ((format[i] == 'h' || format[i] == 'l') &&
               (format[i + 1] == 'i' || format[i + 1] == 'd' ||
                format[i + 1] == 'o' || format[i + 1] == 'u' ||
                format[i + 1] == 'x' || format[i + 1] == 'X' ||
                format[i + 1] == '%')) {
      flags->length = format[i];
    } else if (format[i] == 'L' &&
               (format[i + 1] == 'e' || format[i + 1] == 'E' ||
                format[i + 1] == 'f' || format[i + 1] == 'g' ||
                format[i + 1] == 'G' || format[i + 1] == '%' ||
                format[i + 1] == 'F')) {
      flags->length = format[i];
    } else if (s21_is_specifier(format[i])) {
      flags->type = format[i];
      if (!s21_check_flags(flags))
        flags->error = 1;
      s21_check_specifier_caps_lock(flags);
      break;
    } else {
      flags->error = 1;
      break;
    }
    i++;
  }
  return i;
}

int s21_check_flags(t_flags *flags) {
  int res = 1;
  if (flags->left_alig && flags->zero_fill && flags->type != '%')
    res = 0;
  else if (flags->left_alig && flags->zero_fill && flags->type == '%')
    flags->zero_fill = 0;
  else if (flags->sign && flags->space && flags->type != '%')
    res = 0;
  return res;
}

int s21_is_digit(int c) { return (c >= '0' && c <= '9'); }

int s21_is_specifier(int c) {
  return (c == 'c' || c == 'd' || c == 'i' || c == 'e' || c == 'E' ||
          c == 'f' || c == 'g' || c == 'G' || c == 'o' || c == 's' ||
          c == 'u' || c == 'x' || c == 'X' || c == 'p' || c == 'n' ||
          c == '%' || c == 'F');
}

void s21_check_specifier_caps_lock(t_flags *flags) {
  if (flags->type == 'F' || flags->type == 'E' || flags->type == 'G')
    flags->caps_lock = 1;
}

int s21_get_number(const char *format, int *i) {
  int width = 0;
  width += format[*i] - '0';
  *i += 1;
  while (s21_is_digit(format[*i])) {
    width *= 10;
    width += format[*i] - '0';
    *i += 1;
  }
  *i -= 1;
  return width;
}