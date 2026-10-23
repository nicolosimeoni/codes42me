
#include "ft_printf.h"
#include "../libft/libft.h"
#include <stdarg.h>

static int emit(const char *s, size_t n, int *total)
{
    ssize_t written;

    if (n > (size_t)(INT_MAX - *total)) { errno = EOVERFLOW; return (-1); }
    while (n) {
        written = write(STDOUT_FILENO, s, n);
        if (written < 0 && errno == EINTR) continue;
        if (written <= 0) return (-1);
        s += written;
        n -= (size_t)written;
        *total += (int)written;
    }
    return (0);
}

static int number(uintmax_t n, unsigned int base, const char *digits,
                  const char *prefix, int *total)
{
    char buffer[sizeof(uintmax_t) * CHAR_BIT + 3];
    size_t i = sizeof(buffer), p = ft_strlen(prefix);

    do { buffer[--i] = digits[n % base]; n /= base; } while (n);
    while (p) buffer[--i] = prefix[--p];
    return (emit(buffer + i, sizeof(buffer) - i, total));
}

static int conversion(char spec, va_list *args, int *total)
{
    const char *s, *digits = "0123456789abcdef";
    char c;
    int value;
    unsigned int magnitude;
    void *pointer;

    if (spec == 'c' || spec == '%') {
        c = spec == '%' ? '%' : (char)va_arg(*args, int);
        return (emit(&c, 1, total));
    }
    if (spec == 's') {
        s = va_arg(*args, char *);
        if (!s) s = "(null)";
        return (emit(s, ft_strlen(s), total));
    }
    if (spec == 'd' || spec == 'i') {
        value = va_arg(*args, int);
        magnitude = value < 0 ? 0U - (unsigned int)value : (unsigned int)value;
        return (number(magnitude, 10, digits, value < 0 ? "-" : "", total));
    }
    if (spec == 'p') {
        pointer = va_arg(*args, void *);
        return (number((uintptr_t)pointer, 16, digits, "0x", total));
    }
    if (spec == 'u' || spec == 'x' || spec == 'X') {
        if (spec == 'X') digits = "0123456789ABCDEF";
        return (number(va_arg(*args, unsigned int), spec == 'u' ? 10 : 16,
                       digits, "", total));
    }
    errno = EINVAL;
    return (-1);
}

int ft_printf(const char *format, ...)
{
    va_list args;
    const char *begin;
    int total = 0, result = 0;

    if (!format) { errno = EINVAL; return (-1); }
    va_start(args, format);
    while (*format && result == 0) {
        if (*format == '%') {
            ++format;
            result = conversion(*format, &args, &total);
            if (*format) ++format;
        } else {
            begin = format;
            while (*format && *format != '%') ++format;
            result = emit(begin, (size_t)(format - begin), &total);
        }
    }
    va_end(args);
    return (result < 0 ? -1 : total);
}
