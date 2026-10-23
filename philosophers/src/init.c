#include "philo.h"

static int	init_forks(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->count);
	if (!table->forks)
		return (0);
	i = 0;
	while (i < table->count)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (0);
		table->forks_initialized++;
		i++;
	}
	return (1);
}

static int	init_philosophers(t_table *table)
{
	int		i;
	t_philo	*p;

	table->philos = malloc(sizeof(t_philo) * table->count);
	if (!table->philos)
		return (0);
	i = 0;
	while (i < table->count)
	{
		p = &table->philos[i];
		memset(p, 0, sizeof(*p));
		p->id = i + 1;
		p->left_fork = i;
		p->right_fork = (i + 1) % table->count;
		p->table = table;
		if (pthread_mutex_init(&p->meal_lock, NULL) != 0)
			return (0);
		table->meals_initialized++;
		i++;
	}
	return (1);
}

int	init_table(t_table *table)
{
	if (pthread_mutex_init(&table->state_lock, NULL) != 0)
		return (0);
	table->state_initialized = 1;
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
		return (0);
	table->print_initialized = 1;
	if (!init_forks(table))
		return (0);
	if (!init_philosophers(table))
		return (0);
	return (1);
}
