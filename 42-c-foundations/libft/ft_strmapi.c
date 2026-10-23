#include "libft.h"

char *ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
    size_t i = 0;
    char *p = ft_strdup(s);
    if (p) while (s[i]) { p[i] = f((unsigned int)i, s[i]); ++i; }
    return (p);
}
