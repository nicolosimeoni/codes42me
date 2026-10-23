#include "philo.h"

static void	activate_threads(t_table *table)
{
	int	i;

	table->start = now_ms();
	i = 0;
	while (i < table->count)
	{
		table->philos[i].last_meal = table->start;
		i++;
	}
	pthread_mutex_lock(&table->state_lock);
	table->ready = 1;
	pthread_mutex_unlock(&table->state_lock);
}

static void	join_threads(t_table *table, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
}

int	run_simulation(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->count)
	{
		if (pthread_create(&table->philos[i].thread, NULL,
				philosopher_routine, &table->philos[i]) != 0)
		{
			pthread_mutex_lock(&table->state_lock);
			table->stopped = 1;
			table->ready = 1;
			pthread_mutex_unlock(&table->state_lock);
			join_threads(table, i);
			return (0);
		}
		i++;
	}
	activate_threads(table);
	monitor_simulation(table);
	join_threads(table, table->count);
	return (1);
}
