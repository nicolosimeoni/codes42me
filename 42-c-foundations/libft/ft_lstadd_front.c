#include "libft.h"

void ft_lstadd_front(t_list **lst, t_list *node)
{
    if (lst && node) { node->next = *lst; *lst = node; }
}
