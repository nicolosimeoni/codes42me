#include "libft.h"

char *ft_strdup(const char *s)
{
    size_t n = ft_strlen(s);
    char *p = malloc(n + 1);
    if (p) ft_memcpy(p, s, n + 1);
    return (p);
}
