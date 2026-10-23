#include "libft.h"

char *ft_strrchr(const char *s, int c)
{
    const char *last = NULL;
    do { if (*s == (char)c) last = s; } while (*s++);
    return ((char *)last);
}
