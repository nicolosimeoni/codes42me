#include "push_swap.h"
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

static int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static int	count_tokens(int argc, char **argv)
{
	int	i;
	int	count;
	int	found;
	const char	*p;

	i = 1;
	count = 0;
	while (i < argc)
	{
		found = 0;
		p = argv[i];
		while (*p)
		{
			while (is_space(*p))
				p++;
			if (!*p)
				break ;
			found = 1;
			count++;
			while (*p && !is_space(*p))
				p++;
		}
		if (!found)
			return (-1);
		i++;
	}
	return (count);
}

static int	parse_int(const char **input, int *value)
{
	const char	*p;
	long		result;
	long		limit;
	int			sign;

	p = *input;
	sign = 1;
	if (*p == '-' || *p == '+')
	{
		if (*p == '-')
			sign = -1;
		p++;
	}
	if (*p < '0' || *p > '9')
		return (0);
	result = 0;
	limit = INT_MAX;
	if (sign < 0)
		limit = (long)INT_MAX + 1;
	while (*p >= '0' && *p <= '9')
	{
		if (result > (limit - (*p - '0')) / 10)
			return (0);
		result = result * 10 + (*p++ - '0');
	}
	if (*p && !is_space(*p))
		return (0);
	*value = (int)(result * sign);
	*input = p;
	return (1);
}

static int	read_values(t_game *game, int argc, char **argv)
{
	const char	*p;
	int			i;
	int			j;
	int			value;

	i = 1;
	while (i < argc)
	{
		p = argv[i++];
		while (*p)
		{
			while (is_space(*p))
				p++;
			if (!*p)
				break ;
			if (!parse_int(&p, &value))
				return (0);
			j = 0;
			while (j < game->a.len)
			{
				if (game->a.items[j++] == value)
					return (0);
			}
			game->a.items[game->a.len++] = value;
		}
	}
	return (1);
}

int	parse_args(t_game *game, int argc, char **argv)
{
	int	n;

	game->a.items = NULL;
	game->b.items = NULL;
	game->a.len = 0;
	game->b.len = 0;
	n = count_tokens(argc, argv);
	if (n <= 0)
		return (0);
	game->a.capacity = n;
	game->b.capacity = n;
	game->a.items = malloc(sizeof(int) * (size_t)n);
	game->b.items = malloc(sizeof(int) * (size_t)n);
	if (!game->a.items || !game->b.items)
		return (0);
	return (read_values(game, argc, argv));
}

void	free_game(t_game *game)
{
	free(game->a.items);
	free(game->b.items);
	game->a.items = NULL;
	game->b.items = NULL;
}

void	print_error(void)
{
	write(2, "Error\n", 6);
}

int	is_sorted(const t_stack *stack)
{
	int	i;

	i = 1;
	while (i < stack->len)
	{
		if (stack->items[i - 1] > stack->items[i])
			return (0);
		i++;
	}
	return (1);
}
