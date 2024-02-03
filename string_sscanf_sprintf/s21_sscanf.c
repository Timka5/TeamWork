#include "s21_sscanf.h"

int s21_sscanf(const char *buf, const char *frmt, ...) {
  int eof_var = check_EOF(buf), result = 0;
  if (!eof_var) {
    va_list ap;
    va_start(ap, frmt);
    int format_len = 0;
    char *frmtstr = (char *)frmt;
    int len = (int)s21_strlen(frmtstr);
    char *str = (char *)buf;
    format formats[512];
    while (*frmtstr && frmtstr < frmt + len && format_len < 512) {
      formats[format_len] = parse_format(&frmtstr, &ap);
      format_len++;
    }
    write_formats_to_memory(&str, formats, format_len, &result);
    va_end(ap);
  }
  return (eof_var) ? eof_var : result;
}

int check_EOF(const char *str) {
  int res = -1;
  for (int i = 0; str[i]; i++) {
    if (!isspace(str[i]) && str[i] != '\0') {
      res = 0;
      break;
    }
  }
  return res;
}

format parse_format(char **frmtstr, va_list *ap) {
  format param = {.address = NULL,
                  .length = NONE_LENGTH,
                  .specifier = 0,
                  .width = NONE_WIDTH,
                  .width_num = 0};

  if (isspace(**frmtstr)) {
    param.specifier = 'z';
    skip_spaces(frmtstr);
  }
  if (**frmtstr == '%' && !param.specifier) {
    (*frmtstr)++;

    if (**frmtstr == '%') {
      s21_memset(param.buff, '\0', 512 - 1);
      param.buff[0] = '%';
      (*frmtstr)++;
      param.specifier = 'b';
    } else {
      parse_width(frmtstr, &param);
      parse_length(frmtstr, &param);
      parse_specifier(frmtstr, &param);

      if (param.width != WIDTH_SUP) {
        param.address = va_arg(*ap, void *);
      }
    }
    if (param.specifier == 'p') {
      param.length = NONE_LENGTH;
    }
  }
  if (isalpha(**frmtstr) && !param.specifier) {
    s21_memset(param.buff, '\0', 512 - 1);
    int i = 0;
    while (**frmtstr && !isspace(**frmtstr) && **frmtstr != '%') {
      param.buff[i++] = **frmtstr;
      (*frmtstr)++;
    }
    param.specifier = 'b';
  }
  return param;
}

void skip_spaces(char **str) {
  while (**str && isspace(**str)) {
    (*str)++;
  }
}

void parse_width(char **frmtstr, format *param) {
  if (**frmtstr == '*') {
    (*frmtstr)++;
    param->width = WIDTH_SUP;
  } else {
    int res = parse_number(frmtstr);
    if (res) {
      param->width = WIDTH_NUMBER;
      param->width_num = res;
    }
  }
}

int parse_number(char **frmtstr) {
  char tmp[512] = {'\0'};
  int res = 0, i = 0;
  while (**frmtstr >= '0' && **frmtstr <= '9') {
    tmp[i] = **frmtstr;
    (*frmtstr)++;
    i++;
  }
  res = atoi(tmp);
  return res;
}

void parse_length(char **frmtstr, format *param) {
  switch (**frmtstr) {
  case 'h':
    param->length = LENGTH_SHORT;
    (*frmtstr)++;
    break;
  case 'l':
    param->length = LENGTH_LONG;
    (*frmtstr)++;
    if (**frmtstr == 'l') {
      param->length = LENGTH_LONG_LONG;
      (*frmtstr)++;
    }
    break;
  case 'L':
    param->length = LENGTH_LONG_DOUBLE;
    (*frmtstr)++;
    break;
  }
}

void parse_specifier(char **frmtstr, format *param) {
  param->specifier = (**frmtstr);
  (*frmtstr)++;
}

void write_formats_to_memory(char **str, format *formats, int format_len,
                             int *res) {
  char *start = *str;

  for (int i = 0, fail = 0; i < format_len && !fail; i++) {
    char spec = formats[i].specifier;
    if (spec == 'c') {
      write_char(str, res, (formats + i), &fail);
    }
    if (spec == 'd') {
      write_int(str, &fail, res, (formats + i));
    }
    if (spec == 'i' || spec == 'p') {
      write_unspec_int(str, &fail, res, (formats + i));
    }
    if (spec == 'g' || spec == 'G' || spec == 'f' || spec == 'e' ||
        spec == 'E') {
      write_float(str, res, (formats + i));
    }
    if (spec == 's') {
      write_string(str, &fail, res, (formats + i));
    }
    if (spec == 'u') {
      write_unsigned(str, &fail, res, (formats + i));
    }
    if (spec == 'x' || spec == 'X') {
      write_hex_oct(str, &fail, res, (formats + i), 16);
    }
    if (spec == 'o') {
      write_hex_oct(str, &fail, res, (formats + i), 8);
    }
    if (spec == 'n') {
      *((int *)formats[i].address) = (*str) - start;
    }
    if (spec == 'z') {
      skip_spaces(str);
    }
    if (spec == 'b') {
      skip_chars_in_buffer(str, &fail, (formats + i));
    }
  }
}

void write_char(char **str, int *res, format *param, int *fail) {
  *fail = 1;
  while (**str) {
    *fail = 0;
    if (param->width == WIDTH_SUP) {
      (*str)++;
      break;
    } else {
      *(char *)param->address = **str;
      (*str)++;
      (*res)++;
      break;
    }
  }
}

void write_int(char **str, int *fail_flag, int *res, format *param) {
  long long int result = 0;
  char buff[512] = {'\0'};
  *fail_flag = 1;

  if (strspn(*str, "0123456789+-")) {
    int sign = strspn(*str, "+-");
    if (!(sign > 1 || (sign && (param->width_num <= 1 && param->width)))) {
      buff[0] = **str;
      (*str)++;
      write_chars_to_buff(str, "0123456789", buff, param->width_num, 1);
      if (param->width != WIDTH_SUP)
        (*res)++;
      *fail_flag = 0;
    }
  }
  result = atoi(buff);

  if (param->specifier == 'p' && param->width != WIDTH_SUP && !*fail_flag) {
    unsigned long long int rez = strntollu(buff, NULL, 16, s21_strlen(buff));
    *(int *)param->address = (int)rez;
  } else {
    if (param->width != WIDTH_SUP && !*fail_flag)
      int_converter(param, result, 1);
  }
  if (param->width != WIDTH_NUMBER)
    write_chars_to_buff(str, "0123456789", NULL, 0, 0);
}

void write_chars_to_buff(char **str, const char *chars, char *buff,
                         __int16_t width, int start_ind) {
  while (**str && strspn(*str, chars) != 0) {
    if ((width && start_ind >= width) || (isspace(**str)))
      break;
    if (buff)
      buff[start_ind] = **str;
    (*str)++;
    start_ind++;
  }
}

unsigned long long int strntollu(const char *string, char **endptr, int basis,
                                 int n_byte) {
  unsigned long long res = 0;
  int sign = 1;
  if (endptr)
    *endptr = NULL;
  char dict[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  if (*string == '-') {
    sign = -1;
    string++;
  }
  if (basis == 16 &&
      (!s21_strncmp(string, "0x", 2) || !s21_strncmp(string, "0X", 2)))
    string += 2;
  long long val;
  int exit = 0;
  while (*string && n_byte && !exit) {
    char *tmp2;
    char current_sim =
        (*string >= 'a' && *string <= 'z') ? *string - 'a' + 'A' : *string;
    tmp2 = s21_strchr(dict, (int)current_sim);
    if (!tmp2) {
      exit = 1;
    } else {
      val = (tmp2 - dict) / sizeof(char);

      if (val >= basis) {
        exit = 1;
      } else {
        res = res * basis + val;
        string++;
        n_byte--;
      }
    }
    if (exit)
      *endptr = (char *)string;
  }
  return res * sign;
}

void int_converter(format *param, long long int result, int sign) {
  if (param->specifier != 'p') {
    if (param->length == NONE_LENGTH) {
      *(int *)param->address = sign * (int)result;
    } else if (param->length == LENGTH_SHORT) {
      *(short int *)param->address = sign * (short int)result;
    } else if (param->length == LENGTH_LONG) {
      *(long int *)param->address = sign * (long int)result;
    } else if (param->length == LENGTH_LONG_LONG) {
      *(long long int *)param->address = sign * (long long int)result;
    }
  }
}

void write_unspec_int(char **str, int *fail_flag, int *res, format *param) {
  *fail_flag = 1;
  skip_spaces(str);
  if (strspn(*str, "0x") == 2) {
    *fail_flag = 0;
    write_hex_oct(str, fail_flag, res, param, 16);
  } else if (strspn(*str, "0") == 1) {
    *fail_flag = 0;
    write_hex_oct(str, fail_flag, res, param, 8);
  } else if (strspn(*str, "+-0123456789")) {
    *fail_flag = 0;
    write_int(str, fail_flag, res, param);
  }
}

void write_float(char **str, int *res, format *param) {
  int test = 0;
  if (param->specifier == 'f')
    test = strspn(*str, "0123456789+-");
  else
    test = strspn(*str, "0123456789eE+-NnaAifIF");
  if (test) {
    int sign = strspn(*str, "+-");
    if (!(sign > 1 || (sign && (param->width_num <= 1 && param->width)))) {
      char buff[512] = {'\0'};
      int start_ind = 0;
      if (sign) {
        buff[0] = **str;
        start_ind = 1;
        (*str)++;
      }

      if (param->specifier == 'f')
        write_chars_to_buff(str, ".0123456789+-", buff, param->width_num,
                            start_ind);
      else
        write_chars_to_buff(str, ".0123456789eE+-NnaAifIF", buff,
                            param->width_num, start_ind);

      if (param->width != WIDTH_SUP) {
        long double result = strtold(buff, NULL);
        (*res)++;
        float_converter(param, result);
      }
    }
  }
  if (param->width != WIDTH_NUMBER) {
    if (param->specifier == 'f')
      write_chars_to_buff(str, ".0123456789", NULL, 0, 0);
    else
      write_chars_to_buff(str, ".0123456789eE+-NaAifIFn", NULL, 0, 0);
  }
}

void float_converter(format *param, long double result) {
  if (param->length == NONE_LENGTH)
    *(float *)param->address = (float)result;
  if (param->length == LENGTH_LONG)
    *(double *)param->address = (double)result;
  if (param->length == LENGTH_LONG_DOUBLE)
    *(long double *)param->address = (long double)result;
}

void write_string(char **str, const int *fail_flag, int *res, format *param) {
  int rez = 0;
  char buff[512] = {'\0'};
  unsigned int i = 0;
  while (**str != '\0' && !rez && !(*fail_flag)) {
    if (!isspace(**str)) {
      rez = 1;
      while (**str != '\0' && !(*fail_flag)) {
        buff[i] = **str;
        i++;
        if (param->width == WIDTH_NUMBER && i >= param->width_num) {
          break;
        }
        (*str)++;
        if (isspace(**str)) {
          (*str)--;
          break;
        }
      }
    }
    (*str)++;
  }
  if (param->width != WIDTH_SUP && rez) {
    s21_strncpy((char *)param->address, buff, sizeof(buff));
    (*res)++;
  }
}

void write_unsigned(char **str, int *fail_flag, int *res, format *param) {
  *fail_flag = 1;
  skip_spaces(str);
  char buff[512] = {'\0'};

  if (strspn(*str, "0123456789+-")) {
    int sign = strspn(*str, "+-");
    if (!((sign > 1 || (sign && (param->width_num <= 1 && param->width))))) {
      *fail_flag = 0;
      buff[0] = **str;
      (*str)++;

      write_chars_to_buff(str, "0123456789", buff, param->width_num, 1);

      if (param->width != WIDTH_SUP)
        (*res)++;
    }
  }

  unsigned long long int result = atoi(buff);

  if (param->width != WIDTH_SUP && !*fail_flag)
    unsigned_converter(param, result, 1);

  if (param->width != WIDTH_NUMBER)
    write_chars_to_buff(str, "0123456789", NULL, 0, 0);
}

void write_hex_oct(char **str, int *fail_flag, int *res, format *param,
                   int base) {
  int sign = 1;
  char *ptr = NULL;
  if (param->specifier == 'p')
    base = 16;

  skip_spaces(str);
  if (**str == '-') {
    param->width_num--;
    sign = -1;
    (*str)++;
  }
  if (base == 16 && **str == '0' && (*(*str + 1) == 'x' || *(*str + 1) == 'X'))
    param->width_num -= 2;

  if (strspn(*str, "0123456789abcdefABCDEF") > 0 ||
      strspn(*str, "xX0123456789abcdefABCDEF") >= 2) {
    unsigned long long int result =
        strntollu(*str, &ptr, base,
                  param->width ? (unsigned int)param->width_num
                               : (unsigned int)s21_strlen(*str));

    if (param->width != WIDTH_SUP) {
      *res += 1;

      if (param->specifier == 'p')
        *(int *)param->address = (int)result;
      else
        unsigned_converter(param, result, sign);
    }
  } else {
    *fail_flag = 1;
  }
  unsigned int max = (unsigned int)strspn(*str, "xX0123456789abcdefABCDEF");

  if (param->width != WIDTH_NUMBER)
    *str += max;
  else
    *str += max < param->width_num ? max : param->width_num;
}

void unsigned_converter(format *param, unsigned long long int result,
                        int sign) {
  if (param->length == NONE_LENGTH) {
    *(unsigned int *)param->address = sign * (unsigned int)result;
  } else if (param->length == LENGTH_SHORT) {
    *(unsigned short int *)param->address = sign * (unsigned short int)result;
  } else if (param->length == LENGTH_LONG) {
    *(unsigned long int *)param->address = sign * (unsigned long int)result;
  } else if (param->length == LENGTH_LONG_LONG) {
    *(unsigned long long int *)param->address =
        sign * (unsigned long long int)result;
  }
}

void skip_chars_in_buffer(char **str, int *fail, format *param) {
  int test = strspn(*str, param->buff);
  int len = s21_strlen(param->buff);

  if (len == 1 && **str == param->buff[0]) {
    (*str) = (*str) + len;
    return;
  }
  if (test != len)
    *fail = 1;
  else
    (*str) = (*str) + len;
}

s21_size_t strcspn(const char *str1, const char *str2) {
  s21_size_t counter = 0;
  for (const char *a = str1; *a; a++) {
    unsigned short find = 0;
    for (const char *b = str2; *b; b++) {
      if (*a == *b) {
        find = 1;
        break;
      }
    }
    if (find) {
      break;
    } else {
      counter++;
    }
  }
  return counter;
}