#include "libft.h"

char **ft_split(const char *s, char c)
{
    size_t words = 0, i = 0, k = 0, begin;
    char **out;
    while (s[i]) {
        if (s[i] != c && (!i || s[i-1] == c)) ++words;
        ++i;
    }
    out = ft_calloc(words + 1, sizeof(*out));
    if (!out) return (NULL);
    i = 0;
    while (s[i]) {
        while (s[i] && s[i] == c) ++i;
        begin = i;
        while (s[i] && s[i] != c) ++i;
        if (i == begin) break;
        out[k] = malloc(i - begin + 1);
        if (!out[k]) {
            while (k) free(out[--k]);
            free(out); return (NULL);
        }
        ft_memcpy(out[k], s + begin, i - begin);
        out[k++][i - begin] = '\0';
    }
    return (out);
}
