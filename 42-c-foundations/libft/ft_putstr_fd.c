#include "libft.h"

void ft_putstr_fd(char *s, int fd)
{
    size_t left = ft_strlen(s);
    ssize_t n;
    while (left) {
        n = write(fd, s, left);
        if (n < 0 && errno == EINTR) continue;
        if (n <= 0) return;
        s += n; left -= (size_t)n;
    }
}
