#include "libft.h"

t_list *ft_lstnew(void *content)
{
    t_list *node = malloc(sizeof(*node));
    if (node) { node->content = content; node->next = NULL; }
    return (node);
}
