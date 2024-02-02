#include "s21_sprintf.h"

int s21_translator(int c, t_flags *flags, va_list args, char *str) {
  int result = 0;
  if (c == 'c') {
    result += s21_sprintf_c(va_arg(args, int), flags, str);
  } else if (c == 's') {
    result += s21_sprintf_s(va_arg(args, char *), flags, str);
  } else if (c == 'd' || c == 'i') {
    long long int temp;
    temp = va_arg(args, int);
    if (flags->length == 'h') {
      if (temp > 32767 || temp < -32767) {
        flags->error = 1;
      } else {
        result += s21_sprintf_d_i(temp, flags, str);
      }
    } else if (flags->length == 'l') {
      if (temp > 2147483647 || temp < -2147483647)
        flags->error = 1;
      else
        result += s21_sprintf_d_i(temp, flags, str);
    } else {
      result += s21_sprintf_d_i(temp, flags, str);
    }
  } else if (c == 'p') {
    result += s21_sprintf_p(va_arg(args, void *), flags, str);
  } else if (c == 'u') {
    long long int temp;
    temp = va_arg(args, unsigned long int);
    if (flags->length == 'h') {
      if (temp > 65535) {
        flags->error = 1;
      } else {
        result += s21_sprintf_u(temp, flags, str);
      }
    } else if (flags->length == 'l') {
      if (temp > 4294967295)
        flags->error = 1;
      else
        result += s21_sprintf_u(temp, flags, str);
    } else {
      result += s21_sprintf_u(temp, flags, str);
    }
  } else if (c == 'x') {
    long long int temp;
    temp = va_arg(args, unsigned long int);
    if (flags->length == 'h') {
      if (temp > 65535) {
        flags->error = 1;
      } else {
        result += s21_sprintf_x(temp, 1, flags, str);
      }
    } else if (flags->length == 'l') {
      if (temp > 4294967295)
        flags->error = 1;
      else
        result += s21_sprintf_x(temp, 1, flags, str);
    } else {
      result += s21_sprintf_x(temp, 1, flags, str);
    }
  } else if (c == 'X') {
    long long int temp;
    temp = va_arg(args, unsigned long int);
    if (flags->length == 'h') {
      if (temp > 65535) {
        flags->error = 1;
      } else {
        result += s21_sprintf_x(temp, 0, flags, str);
      }
    } else if (flags->length == 'l') {
      if (temp > 4294967295)
        flags->error = 1;
      else
        result += s21_sprintf_x(temp, 0, flags, str);
    } else {
      result += s21_sprintf_x(temp, 0, flags, str);
    }
  } else if (c == '%') {
    result += s21_sprintf_prc(flags, str);
  } else if (c == 'n') {
    int *n = va_arg(args, int *);
    *n = s21_strlen(str);
    if (s21_check_flags_for_n(flags))
      flags->error = 1;
  } else if (c == 'e' || c == 'g' || c == 'E' || c == 'G' || c == 'f' ||
             c == 'F') {
    long double number;
    if (flags->length != 'L') {
      number = (long double)va_arg(args, double);
    } else {
      number = va_arg(args, long double);
    }

    if (isnan(number) || isinf(number)) {
      result += s21_sprintf_nan_inf(flags, str, isnan(number), number < 0);
    } else {
      if (c == 'f' || c == 'F') {
        result += s21_sprintf_f(number, flags, str);
      } else if (c == 'g' || c == 'G') {
        result += s21_sprintf_g(number, flags, str);
      } else if (c == 'e' || c == 'E') {
        result += s21_sprintf_e(number, flags->type == 'e', flags, str,
                                flags->type == 'g' && flags->sharp == 0);
      }
    }
  } else if (c == 'o') {
    long long int temp;
    temp = va_arg(args, unsigned long int);
    if (flags->length == 'h') {
      if (temp > 65535) {
        flags->error = 1;
      } else {
        result += s21_sprintf_o(temp, flags, str);
      }
    } else if (flags->length == 'l') {
      if (temp > 4294967295)
        flags->error = 1;
      else
        result += s21_sprintf_o(temp, flags, str);
    } else {
      result += s21_sprintf_o(temp, flags, str);
    }
  }
  return result;
}

int s21_sprintf_nan_inf(t_flags *flags, char *str, int nan, int is_negative) {
  int length_str;
  if (!nan && is_negative)
    length_str = 4;
  else
    length_str = 3;

  char *temp = s21_NULL;
  temp = (char *)calloc(3, sizeof(char));
  if (temp == s21_NULL) exit(0);

  if (flags->caps_lock && nan) {
    s21_str_fill_with_chars(temp, "NAN");
  } else if (!flags->caps_lock && nan) {
    s21_str_fill_with_chars(temp, "nan");
  } else if (flags->caps_lock == 0 && !nan) {
    s21_str_fill_with_chars(temp, "inf");
  } else if (flags->caps_lock && !nan) {
    s21_str_fill_with_chars(temp, "INF");
  }

  if (flags->left_alig == 1) {
    if (length_str == 4) s21_putchar_to_str('-', str);
    s21_str_fill_with_chars(str, temp);
  }
  if (flags->width > length_str)
    length_str += s21_fill_width(flags->width, length_str, 0, str);

  if (!flags->left_alig) {
    if (length_str == 4) s21_putchar_to_str('-', str);
    s21_str_fill_with_chars(str, temp);
  }
  free(temp);
  return length_str;
}

int s21_check_flags_for_n(t_flags *flags) {
  return (flags->left_alig == 1 || flags->zero_fill == 1 || flags->width == 1 ||
          flags->precision == 1 || flags->star == 1 || flags->sign == 1 ||
          flags->space == 1 || flags->sharp == 1 || flags->length == 1);
}

int s21_fill_width(int width, int lenght, int has_zero_fill, char *str) {
  int res = width - lenght;
  if (res < 0) {
    res = 0;
  }
  for (int i = 0; i < res; i++) {
    if (has_zero_fill == 1) {
      s21_putchar_to_str('0', str);
    } else {
      s21_putchar_to_str(' ', str);
    }
  }
  return res;
}

int s21_sprintf_c(int c, t_flags *flags, char *str) {
  int result = 1;
  if (flags->zero_fill == 1 || flags->sign == 1 || flags->space == 1 ||
      flags->sharp == 1 || flags->length == 1 || flags->precision != -1) {
    flags->error = 1;
    result = 0;
  } else {
    if (flags->left_alig == 1) {
      s21_putchar_to_str(c, str);
    }
    result += s21_fill_width(flags->width, 1, flags->zero_fill, str);

    if (flags->left_alig == 0) {
      s21_putchar_to_str(c, str);
    }
  }
  return result;
}

int s21_sprintf_s(char *s, t_flags *flags, char *str) {
  int result = 0, i = 0, length_s = 0;
  if (flags->zero_fill == 1 || flags->sign == 1 || flags->space == 1 ||
      flags->sharp == 1) {
    flags->error = 1;
    result = 0;
  } else {
    if (flags->precision > (int)s21_strlen(s) || flags->precision == -1) {
      flags->precision = (int)s21_strlen(s);
      length_s = (int)s21_strlen(s);
    } else {
      length_s = flags->precision;
    }
    if (flags->left_alig == 1) {
      while (i < flags->precision) {
        s21_putchar_to_str(s[i], str);
        i++;
      }
      result += length_s;
    }
    if (flags->width > length_s)
      result += s21_fill_width(flags->width, length_s, flags->zero_fill, str);

    if (flags->left_alig == 0) {
      while (i < flags->precision) {
        result += s21_putchar_to_str(s[i], str);
        i++;
      }
    }
  }
  return result;
}

int s21_sprintf_x(unsigned long c, int check, t_flags *flags, char *str) {
  int result = 0, i = 0, length = 0;
  char *tmp = s21_convert(c, 16, flags);
  char a;
  if (check == 1) {
    a = 'x';
  } else {
    a = 'X';
  }
  if (flags->width < (int)s21_strlen(tmp) || flags->width < flags->precision) {
    flags->width = 0;
  }
  if (flags->precision < (int)s21_strlen(tmp)) {
    flags->precision = (int)s21_strlen(tmp);
  }
  if (flags->sign == 1 || flags->space == 1) {
    flags->error = 1;
  } else {
    if (flags->left_alig == 1) {
      if (flags->sharp == 1 && c != 0) {
        result += s21_putchar_to_str('0', str);
        result += s21_putchar_to_str(a, str);
      }
      if (flags->precision > (int)s21_strlen(tmp)) {
        result += s21_fill_width(flags->precision, s21_strlen(tmp), 1, str);
      }
      while (i < (int)s21_strlen(tmp)) {
        result += s21_putchar_to_str(tmp[i], str);
        i++;
      }
      if (flags->width != 0) {
        result += s21_fill_width(flags->width, result, 0, str);
      }
    } else {
      if (flags->sharp == 1) {
        length = 2;
      }
      if (flags->width != 0) {
        result +=
            s21_fill_width(flags->width, flags->precision + length, 0, str);
      }
      if (flags->sharp == 1 && c != 0) {
        result += s21_putchar_to_str('0', str);
        result += s21_putchar_to_str(a, str);
      }
      if (flags->precision > (int)s21_strlen(tmp)) {
        result += s21_fill_width(flags->precision, s21_strlen(tmp), 1, str);
      }
      while (i < (int)s21_strlen(tmp)) {
        result += s21_putchar_to_str(tmp[i], str);
        i++;
      }
    }
  }
  return result;
}

int s21_sprintf_o(unsigned long c, t_flags *flags, char *str) {
  int result = 0, i = 0, length = 0;
  char *tmp = s21_convert(c, 8, flags);
  if (flags->width < (int)s21_strlen(tmp) || flags->width < flags->precision) {
    flags->width = 0;
  }
  if (flags->precision < flags->width &&
      flags->precision <= (int)s21_strlen(tmp)) {
    flags->precision = (int)s21_strlen(tmp);
  }
  if (flags->sign == 1 || flags->space == 1) {
    flags->error = 1;
  } else {
    if (flags->left_alig == 1) {
      if (flags->sharp == 1) {
        length = 1;
      }
      if (flags->sharp == 1 && c != 0) {
        result += s21_putchar_to_str('0', str);
      }
      if (flags->precision > (int)s21_strlen(tmp)) {
        result +=
            s21_fill_width(flags->precision, s21_strlen(tmp) + length, 1, str);
      }
      while (i < (int)s21_strlen(tmp)) {
        result += s21_putchar_to_str(tmp[i], str);
        i++;
      }
      if (flags->width != 0) {
        result += s21_fill_width(flags->width, result, 0, str);
      }
    } else {
      if (flags->sharp == 1 && c != 0) {
        length = 1;
        if (flags->precision == (int)s21_strlen(tmp) && flags->width == 0) {
          result += s21_putchar_to_str('0', str);
        }
      }
      if (flags->zero_fill == 1 && flags->precision < flags->width &&
          flags->precision > (int)s21_strlen(tmp)) {
        result += s21_fill_width(flags->width, flags->precision, 0, str);
        result +=
            s21_fill_width(flags->width, result + flags->precision, 1, str);
      }
      if (flags->zero_fill == 0 && flags->width != 0) {
        result +=
            s21_fill_width(flags->width, flags->precision + length, 0, str);
      }
      if (flags->precision > (int)s21_strlen(tmp)) {
        result += s21_fill_width(flags->precision, s21_strlen(tmp), 1, str);
      }
      while (i < (int)s21_strlen(tmp)) {
        result += s21_putchar_to_str(tmp[i], str);
        i++;
      }
    }
  }
  return result;
}

int s21_sprintf_prc(t_flags *flags, char *str) {
  int res = 1;
  if (flags->width > 1) res = flags->width;
  if (flags->left_alig == 1) {
    s21_putchar_to_str('%', str);
  }
  s21_fill_width(flags->width, 1, flags->zero_fill, str);

  if (flags->left_alig == 0) s21_putchar_to_str('%', str);

  return res;
}

int s21_get_length(int n) {
  size_t length;
  int isneg;

  length = 0;
  isneg = 0;
  if (n < 0) {
    length++;
    isneg++;
    n = -n;
  }
  while (n >= 1) {
    length++;
    n /= 10;
  }
  return (length);
}

void s21_while_loop1(int arg1, int d, int arg3, int *i, char fill, char *str) {
  while (*i < (arg1 - s21_get_length(d) + arg3)) {
    s21_putchar_to_str(fill, str);
    *i = *i + 1;
  }
}

void s21_while_loop2(int arg1, int u, int *i, char fill, char *str) {
  while (*i < (arg1 - s21_get_length(u))) {
    s21_putchar_to_str(fill, str);
    *i = *i + 1;
  }
}

void s21_while_loop3(int arg1, int arg2, int arg3, int *i, char fill,
                     char *str) {
  while (*i < (arg1 - arg2 + arg3)) {
    s21_putchar_to_str(fill, str);
    *i = *i + 1;
  }
}

char *s21_gen(char *rtn, int nbr, int len, int isneg) {
  if (nbr != 0)
    rtn = malloc(sizeof(char) * (len + 1));
  else
    return "0";
  if (!rtn) return (0);
  isneg = 0;
  if (nbr < 0) {
    isneg++;
    nbr = -nbr;
  }
  rtn[len] = '\0';
  while (--len) {
    rtn[len] = (nbr % 10) + '0';
    nbr /= 10;
  }
  if (isneg == 1)
    rtn[0] = '-';
  else
    rtn[0] = (nbr % 10) + '0';
  return (rtn);
}

char *s21_u_itoa(unsigned int n) {
  int len;
  char *rtn;
  long long int nbr;
  int isneg;

  nbr = n;
  len = s21_get_length(nbr);
  rtn = 0;
  isneg = 0;
  if (!(rtn = s21_gen(rtn, nbr, len, isneg))) return (0);
  return (rtn);
}

int s21_sprintf_u(unsigned int u, t_flags *flags, char *str) {
  int result = 0, i = 0;
  if (((flags->sign == 1 || flags->space == 1 || flags->sharp == 1) &&
       flags->type == 'u') ||
      (flags->type == 'd' && flags->sharp == 1)) {
    flags->error = 1;
    result = 0;
  } else if (flags->left_alig == 1 && flags->width > flags->precision &&
             flags->precision != -1) {
    s21_while_loop1(flags->precision, u, 0, &i, '0', str);
    char *temp = s21_u_itoa(u);
    
    s21_strncat(str, temp, s21_strlen(str));
    free(temp);
    i = s21_strlen(str);
    s21_while_loop3(flags->width, 0, 0, &i, ' ', str);
  } else if (flags->left_alig == 0 && flags->width > flags->precision &&
             flags->precision != -1 && flags->width > s21_get_length(u) &&
             flags->precision < s21_get_length(u)) {
    s21_while_loop2(flags->width, u, &i, ' ', str);
    char *temp = s21_u_itoa(u);
    s21_strncat(str, temp, s21_strlen(str));
    free(temp);
  } else if (flags->left_alig == 0 && flags->width > flags->precision &&
             flags->precision != -1 && flags->zero_fill == 0 &&
             flags->width > s21_get_length(u)) {
    s21_while_loop3(flags->width, flags->precision, 0, &i, ' ', str);
    s21_while_loop1(flags->width, u, 0, &i, '0', str);
    char *temp = s21_u_itoa(u);
    s21_strncat(str, temp, s21_strlen(str));
    free(temp);
  } else if (flags->left_alig == 0 && flags->width > flags->precision &&
             flags->precision != -1 && flags->zero_fill == 1) {
    if (flags->precision <= s21_get_length(u)) {
      s21_while_loop2(flags->width, u, &i, ' ', str);
      char *temp = s21_u_itoa(u);
      s21_strncat(str, temp, s21_strlen(str));
      free(temp);
    } else {
      s21_while_loop3(flags->width, flags->precision, 0, &i, ' ', str);
      s21_while_loop1(flags->width, u, 0, &i, '0', str);
      char *temp = s21_u_itoa(u);
      s21_strncat(str, temp, s21_strlen(str));
      free(temp);
    }
  } else if (flags->precision == -1 && flags->width > s21_get_length(u) &&
             flags->zero_fill == 0 && flags->left_alig == 0) {
    s21_while_loop2(flags->width, u, &i, ' ', str);
    char *temp = s21_u_itoa(u);
    s21_strncat(str, temp, s21_strlen(str));
    free(temp);
  } else if (flags->precision == -1 && flags->width > s21_get_length(u) &&
             flags->zero_fill == 0 && flags->left_alig == 1) {
    char *temp = s21_u_itoa(u);
    s21_strncat(str, temp, s21_strlen(str));
    free(temp);
    s21_while_loop2(flags->width, u, &i, ' ', str);
  } else if (flags->precision == -1 && flags->width > s21_get_length(u) &&
             flags->zero_fill == 1) {
    s21_while_loop2(flags->width, u, &i, '0', str);
    char *temp = s21_u_itoa(u);
    s21_strncat(str, temp, s21_strlen(str));
    free(temp);
  } else if (flags->precision == -1 && flags->width <= s21_get_length(u)) {
    char *temp = s21_u_itoa(u);
    s21_strncat(str, temp, s21_strlen(str));
    free(temp);
  } else if (flags->precision > s21_get_length(u)) {
    s21_while_loop2(flags->precision, u, &i, '0', str);
    char *temp = s21_u_itoa(u);
    s21_strncat(str, temp, s21_strlen(str));
    free(temp);
  } else if (flags->precision < s21_get_length(u)) {
    char *temp = s21_u_itoa(u);
    s21_strncat(str, temp, s21_strlen(str));
    free(temp);
  } else if (flags->width > flags->precision) {
    flags->width = s21_get_length(u);
    s21_while_loop2(flags->width, u, &i, ' ', str);
    char *temp = s21_u_itoa(u);
    s21_strncat(str, temp, s21_strlen(str));
    free(temp);
  } else {
    s21_while_loop2(flags->precision, u, &i, '0', str);
    char *temp = s21_u_itoa(u);
    s21_strncat(str, temp, s21_strlen(str));
    free(temp);
  }
  result = s21_strlen(str);
  return result;
}

int s21_sprintf_d_i(int d, t_flags *flags, char *str) {
  int result = 0, i = 0;
  if (d < 0 || flags->sign == 1 || d == 0) {
    if (d == 0) {
      if (flags->left_alig == 1) {
        if (flags->sign == 1) s21_putchar_to_str('+', str);
        flags->precision--;
        s21_sprintf_u(d, flags, str);
      } else if (flags->left_alig == 0 && flags->zero_fill == 0 &&
                 flags->sign == 0) {
        if (flags->space == 1 && flags->width <= flags->precision)
          s21_putchar_to_str(' ', str);
        if (flags->space == 1 && flags->width == 0 && flags->precision == -1)
          s21_putchar_to_str(' ', str);
        flags->precision--;
        flags->width--;
        s21_sprintf_u(d, flags, str);
      } else if (flags->zero_fill == 1 && flags->sign == 0) {
        flags->precision--;
        s21_while_loop3(flags->width, 0, 0, &i, '0', str);
      } else if (flags->sign == 1) {
        if (flags->width != 0 && flags->precision != -1 &&
            flags->width > flags->precision) {
          s21_while_loop3(flags->width - 1, flags->precision, 0, &i, ' ', str);
          s21_putchar_to_str('+', str);
          s21_while_loop3(flags->width - 1, 0, 0, &i, '0', str);
        } else if (flags->precision > flags->width) {
          s21_putchar_to_str('+', str);
          s21_while_loop3(flags->precision, 0, 0, &i, '0', str);
        } else if (flags->width > 0 && flags->precision == -1 &&
                   flags->zero_fill == 0) {
          s21_while_loop2(flags->width - 1, 2, &i, ' ', str);
          s21_putchar_to_str('+', str);
          s21_putchar_to_str('0', str);
        } else if (flags->width > 0 && flags->precision == -1 &&
                   flags->zero_fill == 1) {
          s21_putchar_to_str('+', str);
          s21_while_loop3(flags->width, 1, 0, &i, '0', str);
        } else if (flags->precision != -1) {
          s21_putchar_to_str('+', str);
          s21_while_loop3(flags->precision, 0, 0, &i, '0', str);
        } else {
          s21_putchar_to_str('+', str);
          s21_putchar_to_str('0', str);
        }
      }
    } else if (flags->width > s21_get_length(d) &&
               flags->precision <= s21_get_length(d) && flags->left_alig == 0 &&
               flags->precision != -1) {
      if (flags->precision != s21_get_length(d)) {
        if (flags->sign == 1 && d > 0) {
          s21_while_loop2(flags->width - 1, d, &i, ' ', str);
          s21_putchar_to_str('+', str);
          char *temp = s21_u_itoa(d);
          s21_strncat(str, temp, s21_strlen(str));
          free(temp);
        } else {
          s21_while_loop2(flags->width, d, &i, ' ', str);
          char *temp = s21_u_itoa(d);
          s21_strncat(str, temp, s21_strlen(str));
          free(temp);
        }
      } else {
        if (flags->sign == 1 && d > 0) {
          s21_while_loop1(flags->width, d, -1, &i, ' ', str);
          s21_putchar_to_str('+', str);
          char *temp = s21_u_itoa(d);
          s21_strncat(str, temp, s21_strlen(str));
          free(temp);
        } else {
          s21_while_loop1(flags->width, d, -1, &i, ' ', str);
          s21_putchar_to_str('-', str);
          s21_putchar_to_str('0', str);
          char *temp = s21_u_itoa(-d);
          s21_strncat(str, temp, s21_strlen(str));
          free(temp);
        }
      }
    } else if (flags->width > s21_get_length(d) && flags->zero_fill == 0 &&
               flags->precision > s21_get_length(d) && flags->left_alig == 0 &&
               flags->width > flags->precision) {
      if (flags->sign == 1 && d > 0) {
        s21_while_loop3(flags->width, flags->precision, -1, &i, ' ', str);
        s21_putchar_to_str('+', str);
        s21_while_loop2(flags->width - 1, d, &i, '0', str);
        char *temp = s21_u_itoa(d);
        s21_strncat(str, temp, s21_strlen(str));
        free(temp);
      } else {
        s21_while_loop3(flags->width, flags->precision, -1, &i, ' ', str);
        s21_putchar_to_str('-', str);
        s21_while_loop2(flags->width, d, &i, '0', str);
        char *temp = s21_u_itoa(-d);
        s21_strncat(str, temp, s21_strlen(str));
        free(temp);
      }
    } else if (flags->zero_fill == 1 && flags->width > flags->precision &&
               flags->precision > s21_get_length(d)) {
      if (flags->sign == 1 && d > 0) {
        s21_while_loop3(flags->width, flags->precision, -1, &i, ' ', str);
        s21_putchar_to_str('+', str);
        s21_while_loop2(flags->width - 1, d, &i, '0', str);
        char *temp = s21_u_itoa(d);
        s21_strncat(str, temp, s21_strlen(str));
        free(temp);
      } else {
        s21_while_loop3(flags->width, flags->precision, -1, &i, ' ', str);
        s21_putchar_to_str('-', str);
        s21_while_loop2(flags->width, d, &i, '0', str);
        char *temp = s21_u_itoa(-d);
        s21_strncat(str, temp, s21_strlen(str));
        free(temp);
      }
    } else if (flags->zero_fill == 1 && flags->width > flags->precision &&
               flags->precision < s21_get_length(d) && flags->precision != -1) {
      if (flags->sign == 1 && d > 0) {
        s21_putchar_to_str('+', str);
        s21_while_loop3(flags->precision, d, 1, &i, '0', str);
        char *temp = s21_u_itoa(d);
        s21_strncat(str, temp, s21_strlen(str));
        free(temp);
      } else {
        s21_putchar_to_str('-', str);
        s21_while_loop3(flags->precision, -d, 1, &i, '0', str);
        char *temp = s21_u_itoa(-d);
        s21_strncat(str, temp, s21_strlen(str));
        free(temp);
      }
    } else if (flags->width <= flags->precision) {
      if (flags->sign == 1 && d > 0) {
        s21_putchar_to_str('+', str);
        s21_sprintf_u(d, flags, str);
      } else {
        s21_putchar_to_str('-', str);
        s21_sprintf_u(-d, flags, str);
      }
    } else if (flags->width <= s21_get_length(d)) {
      if (flags->sign == 1 && d > 0) {
        s21_putchar_to_str('+', str);
        char *temp = s21_u_itoa(d);
        s21_strncat(str, temp, s21_strlen(str));
        free(temp);
      } else {
        char *temp = s21_u_itoa(d);
        s21_strncat(str, temp, s21_strlen(str));
        free(temp);
      }
    } else if (flags->left_alig == 1 && flags->width > flags->precision) {
      if (flags->precision < s21_get_length(d)) {
        if (flags->sign == 1 && d > 0) {
          s21_putchar_to_str('+', str);
          char *temp = s21_u_itoa(d);
          s21_strncat(str, temp, s21_strlen(str));
          free(temp);
          i += s21_get_length(d);
          s21_while_loop1(flags->width - 1, 0, 0, &i, ' ', str);
        } else {
          char *temp = s21_u_itoa(d);
          s21_strncat(str, temp, s21_strlen(str));
          free(temp);
          i += s21_get_length(d);
          s21_while_loop1(flags->width, 0, 0, &i, ' ', str);
        }
      } else {
        if (flags->sign == 1 && d > 0) {
          s21_putchar_to_str('+', str);
          i++;
          s21_while_loop1(flags->precision, d, 1, &i, '0', str);
          char *temp = s21_u_itoa(d);
          s21_strncat(str, temp, s21_strlen(str));
          free(temp);
          i += s21_get_length(d);
          s21_while_loop2(flags->width, 0, &i, ' ', str);
        } else {
          s21_putchar_to_str('-', str);
          i++;
          s21_while_loop1(flags->precision, -d, 1, &i, '0', str);
          char *temp = s21_u_itoa(-d);
          s21_strncat(str, temp, s21_strlen(str));
          free(temp);
          i += s21_get_length(-d);
          s21_while_loop2(flags->width, 0, &i, ' ', str);
        }
      }
    } else if (flags->precision == -1 && flags->width > s21_get_length(d) &&
               flags->zero_fill == 1 && flags->sign == 1) {
      if (d < 0) {
        s21_putchar_to_str('-', str);
        s21_while_loop2(flags->width, d, &i, '0', str);
        char *temp = s21_u_itoa(-d);
        s21_strncat(str, temp, s21_strlen(str));
        free(temp);
      } else {
        s21_putchar_to_str('+', str);
        i++;
        s21_while_loop2(flags->width, d, &i, '0', str);
        char *temp = s21_u_itoa(d);
        s21_strncat(str, temp, s21_strlen(str));
        free(temp);
      }
    } else if (flags->precision == -1 && flags->width > s21_get_length(d) &&
               flags->zero_fill == 0) {
      if (flags->sign == 1 && d > 0) {
        s21_while_loop2(flags->width - 1, d, &i, ' ', str);
        s21_putchar_to_str('+', str);
        char *temp = s21_u_itoa(d);
        s21_strncat(str, temp, s21_strlen(str));
        free(temp);
      } else {
        s21_while_loop2(flags->width, d, &i, ' ', str);
        char *temp = s21_u_itoa(d);
        s21_strncat(str, temp, s21_strlen(str));
        free(temp);
      }
    } else if (flags->precision == -1 && flags->width > s21_get_length(d) &&
               d < 0 && flags->zero_fill == 1) {
      s21_putchar_to_str('-', str);
      i++;
      s21_while_loop2(flags->width, -d, &i, '0', str);
      char *temp = s21_u_itoa(-d);
      s21_strncat(str, temp, s21_strlen(str));
      free(temp);
    }
  } else {
    if (d == 0) {
      if (flags->width > flags->precision) flags->precision--;
    }
    if (flags->space == 1 && flags->width > s21_get_length(d)) {
      s21_putchar_to_str(' ', str);
      flags->width = flags->width - 1;
    } else if (flags->space == 1 && flags->width <= s21_get_length(d) &&
               flags->precision >= s21_get_length(d)) {
      s21_putchar_to_str(' ', str);
    } else if (flags->space == 1 && flags->width < s21_get_length(d) &&
               flags->precision < s21_get_length(d)) {
      s21_putchar_to_str(' ', str);
    }
    result = s21_sprintf_u(d, flags, str);
  }
  result = s21_strlen(str);
  return result;
}