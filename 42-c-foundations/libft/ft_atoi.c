#include "libft.h"

int ft_atoi(const char *s)
{
    unsigned int n = 0, limit;
    int negative = 0;
    while (*s == ' ' || (*s >= '\t' && *s <= '\r')) ++s;
    if (*s == '-' || *s == '+') negative = (*s++ == '-');
    limit = negative ? (unsigned int)INT_MAX + 1U : (unsigned int)INT_MAX;
    while (ft_isdigit((unsigned char)*s)) {
        if (n > (limit - (unsigned int)(*s - '0')) / 10)
            return (negative ? INT_MIN : INT_MAX);
        n = n * 10 + (unsigned int)(*s++ - '0');
    }
    if (negative && n == (unsigned int)INT_MAX + 1U) return (INT_MIN);
    return (negative ? -(int)n : (int)n);
}
