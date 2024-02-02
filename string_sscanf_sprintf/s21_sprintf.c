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

char* s21_convert(unsigned long long num, int base, t_flags *flags) {
    static char Representation1[]= "0123456789abcdef";
    static char Representation2[]= "0123456789ABCDEF";
    static char buffer[50];
    char *ptr;

    ptr = &buffer[49];
    *ptr = '\0';
    if (flags->type == 'x' || flags->type == 'o' || flags->type == 'p') {
        do {
            *--ptr = Representation1[num%base];
            num /= base;
        } while (num != 0);
    } else {
        do {
            *--ptr = Representation2[num%base];
            num /= base;
        } while (num != 0);
    }
    return (ptr);
}