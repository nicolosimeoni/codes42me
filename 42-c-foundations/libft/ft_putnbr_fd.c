#include "libft.h"

void ft_putnbr_fd(int n, int fd)
{
    unsigned int u = n < 0 ? 0U - (unsigned int)n : (unsigned int)n;
    if (n < 0) ft_putchar_fd('-', fd);
    if (u >= 10) ft_putnbr_fd((int)(u / 10), fd);
    ft_putchar_fd((char)('0' + u % 10), fd);
}
