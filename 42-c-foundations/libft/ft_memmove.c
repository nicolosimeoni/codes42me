#include "libft.h"

void *ft_memmove(void *dst, const void *src, size_t n)
{
    unsigned char *d = dst;
    const unsigned char *s = src;
    if (d == s || n == 0) return (dst);
    /* Integer addresses avoid relational comparison of unrelated pointers. */
    if ((uintptr_t)d < (uintptr_t)s) return (ft_memcpy(dst, src, n));
    while (n) { --n; d[n] = s[n]; }
    return (dst);
}
