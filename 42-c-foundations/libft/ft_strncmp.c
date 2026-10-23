#include "libft.h"

int ft_strncmp(const char *a, const char *b, size_t n)
{
    while (n) {
        if ((unsigned char)*a != (unsigned char)*b || !*a)
            return ((unsigned char)*a - (unsigned char)*b);
        ++a; ++b; --n;
    }
    return (0);
}
