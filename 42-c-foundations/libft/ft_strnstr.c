#include "libft.h"

char *ft_strnstr(const char *haystack, const char *needle, size_t len)
{
    size_t i = 0, j;
    if (!*needle) return ((char *)haystack);
    while (i < len && haystack[i]) {
        j = 0;
        while (j < len - i && needle[j] && haystack[i+j] == needle[j]) ++j;
        if (!needle[j]) return ((char *)haystack + i);
        ++i;
    }
    return (NULL);
}
