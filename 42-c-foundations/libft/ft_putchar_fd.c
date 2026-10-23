#include "libft.h"

void ft_putchar_fd(char c, int fd)
{
    ssize_t result;

    do { result = write(fd, &c, 1); }
    while (result < 0 && errno == EINTR);
}
