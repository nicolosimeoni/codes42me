#include "libft.h"

t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
    t_list *out = NULL, **tail = &out, *node;
    void *content;
    while (lst) {
        content = f(lst->content);
        node = ft_lstnew(content);
        if (!node) { if (del) del(content); ft_lstclear(&out, del); return (NULL); }
        *tail = node; tail = &node->next; lst = lst->next;
    }
    return (out);
}
