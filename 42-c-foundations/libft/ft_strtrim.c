#include "libft.h"

char *ft_strtrim(const char *s, const char *set)
{
    size_t n;
    char *p;
    while (*s && ft_strchr(set, *s)) ++s;
    n = ft_strlen(s);
    while (n && ft_strchr(set, s[n-1])) --n;
    p = malloc(n + 1);
    if (p) { ft_memcpy(p, s, n); p[n] = '\0'; }
    return (p);
}
