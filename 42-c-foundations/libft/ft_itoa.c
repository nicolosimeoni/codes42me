#include "libft.h"

char *ft_itoa(int value)
{
    char buf[sizeof(int) * CHAR_BIT + 2];
    size_t i = sizeof(buf);
    unsigned int n = value < 0 ? 0U - (unsigned int)value : (unsigned int)value;
    buf[--i] = '\0';
    do { buf[--i] = (char)('0' + n % 10); n /= 10; } while (n);
    if (value < 0) buf[--i] = '-';
    return (ft_strdup(buf + i));
}
