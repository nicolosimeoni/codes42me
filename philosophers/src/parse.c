#include "philo.h"

static int	positive_number(const char *s, int *result)
{
	long	n;
	int		i;

	n = 0;
	i = 0;
	if (s[i] == '+')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		n = n * 10 + s[i++] - '0';
		if (n > INT_MAX)
			return (0);
	}
	if (n == 0)
		return (0);
	*result = (int)n;
	return (1);
}

int	parse_arguments(int argc, char **argv, t_table *table)
{
	int	values[5];
	int	i;

	if (argc != 5 && argc != 6)
		return (0);
	i = 0;
	while (i < argc - 1)
	{
		if (!positive_number(argv[i + 1], &values[i]))
			return (0);
		i++;
	}
	table->count = values[0];
	table->time_die = values[1];
	table->time_eat = values[2];
	table->time_sleep = values[3];
	if (argc == 6)
		table->meal_goal = values[4];
	return (1);
}
