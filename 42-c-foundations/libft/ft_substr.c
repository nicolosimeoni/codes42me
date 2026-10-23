#include "libft.h"

char *ft_substr(const char *s, unsigned int start, size_t len)
{
    size_t n = ft_strlen(s);
    char *p;
    if (start >= n) return (ft_strdup(""));
    if (len > n - start) len = n - start;
    p = malloc(len + 1);
    if (p) { ft_memcpy(p, s + start, len); p[len] = '\0'; }
    return (p);
}
