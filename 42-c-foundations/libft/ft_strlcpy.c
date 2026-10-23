#include "libft.h"

size_t ft_strlcpy(char *dst, const char *src, size_t size)
{
    size_t len = ft_strlen(src), n;
    if (size) {
        n = len < size - 1 ? len : size - 1;
        ft_memcpy(dst, src, n); dst[n] = '\0';
    }
    return (len);
}
