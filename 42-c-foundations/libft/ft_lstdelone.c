#include "libft.h"

void ft_lstdelone(t_list *node, void (*del)(void *))
{
    if (node) { if (del) del(node->content); free(node); }
}
