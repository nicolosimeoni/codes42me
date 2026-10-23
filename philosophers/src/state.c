#include "philo.h"

int	is_stopped(t_table *table)
{
	int	stopped;

	pthread_mutex_lock(&table->state_lock);
	stopped = table->stopped;
	pthread_mutex_unlock(&table->state_lock);
	return (stopped);
}

void	stop_simulation(t_table *table)
{
	pthread_mutex_lock(&table->print_lock);
	pthread_mutex_lock(&table->state_lock);
	table->stopped = 1;
	pthread_mutex_unlock(&table->state_lock);
	pthread_mutex_unlock(&table->print_lock);
}

void	report_death(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->print_lock);
	pthread_mutex_lock(&table->state_lock);
	if (!table->stopped)
	{
		table->stopped = 1;
		printf("%ld %d died\n", now_ms() - table->start, philo->id);
	}
	pthread_mutex_unlock(&table->state_lock);
	pthread_mutex_unlock(&table->print_lock);
}

int	log_action(t_philo *philo, const char *message)
{
	t_table	*table;
	int		active;

	table = philo->table;
	pthread_mutex_lock(&table->print_lock);
	active = !is_stopped(table);
	if (active)
		printf("%ld %d %s\n", now_ms() - table->start, philo->id, message);
	pthread_mutex_unlock(&table->print_lock);
	return (active);
}
