#include "philo.h"

static int	check_philosopher(t_philo *p, int *finished)
{
	long	last;
	int		meals;

	pthread_mutex_lock(&p->meal_lock);
	last = p->last_meal;
	meals = p->meals;
	pthread_mutex_unlock(&p->meal_lock);
	if (p->table->meal_goal == 0 || meals < p->table->meal_goal)
	{
		*finished = 0;
		if (now_ms() - last >= p->table->time_die)
		{
			report_death(p);
			return (0);
		}
	}
	return (1);
}

void	monitor_simulation(t_table *table)
{
	int	i;
	int	finished;

	while (!is_stopped(table))
	{
		i = 0;
		finished = (table->meal_goal != 0);
		while (i < table->count)
		{
			if (!check_philosopher(&table->philos[i++], &finished))
				return ;
		}
		if (finished)
		{
			stop_simulation(table);
			return ;
		}
		usleep(500);
	}
}
