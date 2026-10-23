#include "philo.h"

void	destroy_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->meals_initialized)
		pthread_mutex_destroy(&table->philos[i++].meal_lock);
	i = 0;
	while (i < table->forks_initialized)
		pthread_mutex_destroy(&table->forks[i++]);
	if (table->print_initialized)
		pthread_mutex_destroy(&table->print_lock);
	if (table->state_initialized)
		pthread_mutex_destroy(&table->state_lock);
	free(table->philos);
	free(table->forks);
}
