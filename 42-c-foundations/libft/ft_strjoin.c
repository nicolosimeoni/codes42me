#include "libft.h"

char *ft_strjoin(const char *a, const char *b)
{
    size_t x = ft_strlen(a), y = ft_strlen(b);
    char *p;
    if (x == SIZE_MAX || y > SIZE_MAX - x - 1) return (NULL);
    p = malloc(x + y + 1);
    if (p) { ft_memcpy(p, a, x); ft_memcpy(p + x, b, y + 1); }
    return (p);
}
