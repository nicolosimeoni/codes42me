#include "libft.h"

size_t ft_strlcat(char *dst, const char *src, size_t size)
{
    size_t d = 0, s = ft_strlen(src);
    while (d < size && dst[d]) ++d;
    if (d == size) return (size + s);
    ft_strlcpy(dst + d, src, size - d);
    return (d + s);
}
