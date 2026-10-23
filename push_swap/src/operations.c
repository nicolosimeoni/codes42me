#include "push_swap.h"
#include <unistd.h>

static void	swap_top(t_stack *s)
{
	int	v;

	if (s->len < 2)
		return ;
	v = s->items[0];
	s->items[0] = s->items[1];
	s->items[1] = v;
}

static void	push_top(t_stack *from, t_stack *to)
{
	int	i;
	int	v;

	if (!from->len)
		return ;
	v = from->items[0];
	i = 1;
	while (i < from->len)
	{
		from->items[i - 1] = from->items[i];
		i++;
	}
	from->len--;
	i = to->len;
	while (i > 0)
	{
		to->items[i] = to->items[i - 1];
		i--;
	}
	to->items[0] = v;
	to->len++;
}

static void	rotate(t_stack *s)
{
	int	v;
	int	i;

	if (s->len < 2)
		return ;
	v = s->items[0];
	i = 1;
	while (i < s->len)
	{
		s->items[i - 1] = s->items[i];
		i++;
	}
	s->items[s->len - 1] = v;
}

static void	reverse_rotate(t_stack *s)
{
	int	v;
	int	i;

	if (s->len < 2)
		return ;
	v = s->items[s->len - 1];
	i = s->len - 1;
	while (i > 0)
	{
		s->items[i] = s->items[i - 1];
		i--;
	}
	s->items[0] = v;
}

static const char	*operation_name(t_op op)
{
	if (op == SA) return ("sa\n");
	if (op == SB) return ("sb\n");
	if (op == SS) return ("ss\n");
	if (op == PA) return ("pa\n");
	if (op == PB) return ("pb\n");
	if (op == RA) return ("ra\n");
	if (op == RB) return ("rb\n");
	if (op == RR) return ("rr\n");
	if (op == RRA) return ("rra\n");
	if (op == RRB) return ("rrb\n");
	if (op == RRR) return ("rrr\n");
	return (NULL);
}

void	perform(t_game *g, t_op op, int output)
{
	const char	*name;
	int			length;

	if (op == SA || op == SS) swap_top(&g->a);
	if (op == SB || op == SS) swap_top(&g->b);
	if (op == PA) push_top(&g->b, &g->a);
	if (op == PB) push_top(&g->a, &g->b);
	if (op == RA || op == RR) rotate(&g->a);
	if (op == RB || op == RR) rotate(&g->b);
	if (op == RRA || op == RRR) reverse_rotate(&g->a);
	if (op == RRB || op == RRR) reverse_rotate(&g->b);
	if (!output) return ;
	name = operation_name(op);
	if (!name) return ;
	length = 3;
	if (op == RRA || op == RRB || op == RRR) length = 4;
	write(1, name, length);
}

static int	string_eq(const char *a, const char *b)
{
	while (*a && *b && *a == *b)
	{
		a++;
		b++;
	}
	return (!*a && !*b);
}

t_op	parse_op(const char *line)
{
	if (string_eq(line, "sa")) return (SA);
	if (string_eq(line, "sb")) return (SB);
	if (string_eq(line, "ss")) return (SS);
	if (string_eq(line, "pa")) return (PA);
	if (string_eq(line, "pb")) return (PB);
	if (string_eq(line, "ra")) return (RA);
	if (string_eq(line, "rb")) return (RB);
	if (string_eq(line, "rr")) return (RR);
	if (string_eq(line, "rra")) return (RRA);
	if (string_eq(line, "rrb")) return (RRB);
	if (string_eq(line, "rrr")) return (RRR);
	return (INVALID);
}
