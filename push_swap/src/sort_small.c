#include "push_swap.h"

static int	min_index(const t_stack *s)
{
	int	i;
	int	best;

	i = 1;
	best = 0;
	while (i < s->len)
	{
		if (s->items[i] < s->items[best])
			best = i;
		i++;
	}
	return (best);
}

void	rotate_min_to_top(t_game *g)
{
	int	index;

	index = min_index(&g->a);
	if (index <= g->a.len / 2)
		while (index-- > 0) perform(g, RA, 1);
	else
	{
		index = g->a.len - index;
		while (index-- > 0) perform(g, RRA, 1);
	}
}

void	sort_three(t_game *g)
{
	int	*a;

	a = g->a.items;
	if (a[0] > a[1] && a[0] > a[2])
		perform(g, RA, 1);
	else if (a[1] > a[0] && a[1] > a[2])
		perform(g, RRA, 1);
	if (g->a.items[0] > g->a.items[1])
		perform(g, SA, 1);
}

void	sort_small(t_game *g)
{
	if (g->a.len == 2)
	{
		if (!is_sorted(&g->a))
			perform(g, SA, 1);
		return ;
	}
	while (g->a.len > 3)
	{
		rotate_min_to_top(g);
		perform(g, PB, 1);
	}
	if (g->a.len == 3)
		sort_three(g);
	while (g->b.len)
		perform(g, PA, 1);
}
