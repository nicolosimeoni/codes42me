#include "push_swap.h"
#include <limits.h>

static int	index_of_min(const t_stack *s)
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

/* Place x before the next lower value in circular descending stack B. */
static int	target_in_b(const t_stack *s, int x)
{
	int	i;
	int	index;
	int	lower;

	i = 0;
	index = -1;
	lower = INT_MIN;
	while (i < s->len)
	{
		if (s->items[i] < x && (index < 0 || s->items[i] > lower))
		{
			lower = s->items[i];
			index = i;
		}
		i++;
	}
	if (index >= 0) return (index);
	i = 1;
	index = 0;
	while (i < s->len)
	{
		if (s->items[i] > s->items[index]) index = i;
		i++;
	}
	return (index);
}

/* Place x before the next higher value in circular ascending stack A. */
static int	target_in_a(const t_stack *s, int x)
{
	int	i;
	int	index;
	int	higher;

	i = 0;
	index = -1;
	higher = INT_MAX;
	while (i < s->len)
	{
		if (s->items[i] > x && (index < 0 || s->items[i] < higher))
		{
			higher = s->items[i];
			index = i;
		}
		i++;
	}
	if (index >= 0) return (index);
	return (index_of_min(s));
}

static int	absolute(int n)
{
	if (n < 0) return (-n);
	return (n);
}

static int	max_int(int x, int y)
{
	if (x > y) return (x);
	return (y);
}

static int	plan_cost(int a, int b)
{
	if ((a >= 0 && b >= 0) || (a <= 0 && b <= 0))
		return (max_int(absolute(a), absolute(b)));
	return (absolute(a) + absolute(b));
}

static t_plan	best_directions(int idx_a, int n_a, int idx_b, int n_b)
{
	t_plan	best;
	int		as[2];
	int		bs[2];
	int		i;
	int		j;
	int		cost;

	as[0] = idx_a;
	as[1] = idx_a - n_a;
	bs[0] = idx_b;
	bs[1] = idx_b - n_b;
	best.cost = INT_MAX;
	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 2)
		{
			cost = plan_cost(as[i], bs[j]);
			if (cost < best.cost)
			{
				best.steps_a = as[i];
				best.steps_b = bs[j];
				best.cost = cost;
			}
			j++;
		}
		i++;
	}
	return (best);
}

static t_plan	find_cheapest(t_game *g, int a_to_b)
{
	t_plan	best;
	t_plan	candidate;
	int		i;
	int		index;

	best.cost = INT_MAX;
	i = 0;
	while ((a_to_b && i < g->a.len) || (!a_to_b && i < g->b.len))
	{
		if (a_to_b)
		{
			index = target_in_b(&g->b, g->a.items[i]);
			candidate = best_directions(i, g->a.len, index, g->b.len);
		}
		else
		{
			index = target_in_a(&g->a, g->b.items[i]);
			candidate = best_directions(index, g->a.len, i, g->b.len);
		}
		if (candidate.cost < best.cost) best = candidate;
		i++;
	}
	return (best);
}

static void	execute_plan(t_game *g, t_plan p, t_op push)
{
	while (p.steps_a > 0 && p.steps_b > 0)
	{
		perform(g, RR, 1);
		p.steps_a--;
		p.steps_b--;
	}
	while (p.steps_a < 0 && p.steps_b < 0)
	{
		perform(g, RRR, 1);
		p.steps_a++;
		p.steps_b++;
	}
	while (p.steps_a > 0) { perform(g, RA, 1); p.steps_a--; }
	while (p.steps_a < 0) { perform(g, RRA, 1); p.steps_a++; }
	while (p.steps_b > 0) { perform(g, RB, 1); p.steps_b--; }
	while (p.steps_b < 0) { perform(g, RRB, 1); p.steps_b++; }
	perform(g, push, 1);
}

void	sort_stack(t_game *g)
{
	if (is_sorted(&g->a)) return ;
	if (g->a.len <= 5) { sort_small(g); return ; }
	perform(g, PB, 1);
	perform(g, PB, 1);
	while (g->a.len > 3)
		execute_plan(g, find_cheapest(g, 1), PB);
	sort_three(g);
	while (g->b.len)
		execute_plan(g, find_cheapest(g, 0), PA);
	rotate_min_to_top(g);
}
