#include "libft.h"

void ft_lstadd_back(t_list **lst, t_list *node)
{
    t_list *last;
    if (!lst || !node) return;
    last = ft_lstlast(*lst);
    if (last) last->next = node;
    else *lst = node;
}
