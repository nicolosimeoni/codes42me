#include "philo.h"

static int	wait_for_start(t_table *table)
{
	int	ready;

	while (1)
	{
		pthread_mutex_lock(&table->state_lock);
		ready = table->ready;
		pthread_mutex_unlock(&table->state_lock);
		if (ready)
			return (!is_stopped(table));
		usleep(200);
	}
}

static int	lock_forks(t_philo *p, int *first, int *second)
{
	*first = p->left_fork;
	*second = p->right_fork;
	if (*first > *second)
	{
		*first = p->right_fork;
		*second = p->left_fork;
	}
	pthread_mutex_lock(&p->table->forks[*first]);
	if (!log_action(p, "has taken a fork"))
	{
		pthread_mutex_unlock(&p->table->forks[*first]);
		return (0);
	}
	pthread_mutex_lock(&p->table->forks[*second]);
	if (!log_action(p, "has taken a fork"))
	{
		pthread_mutex_unlock(&p->table->forks[*second]);
		pthread_mutex_unlock(&p->table->forks[*first]);
		return (0);
	}
	return (1);
}

static int	eat(t_philo *p)
{
	int	first;
	int	second;
	int	finished;

	if (!lock_forks(p, &first, &second))
		return (0);
	pthread_mutex_lock(&p->meal_lock);
	p->last_meal = now_ms();
	pthread_mutex_unlock(&p->meal_lock);
	if (log_action(p, "is eating"))
		wait_ms(p->table, p->table->time_eat);
	finished = is_stopped(p->table);
	pthread_mutex_lock(&p->meal_lock);
	if (!finished)
		p->meals++;
	finished = (p->table->meal_goal > 0
			&& p->meals >= p->table->meal_goal);
	pthread_mutex_unlock(&p->meal_lock);
	pthread_mutex_unlock(&p->table->forks[second]);
	pthread_mutex_unlock(&p->table->forks[first]);
	return (!is_stopped(p->table) && !finished);
}

static void	one_philosopher(t_philo *p)
{
	pthread_mutex_lock(&p->table->forks[p->left_fork]);
	log_action(p, "has taken a fork");
	while (!is_stopped(p->table))
		usleep(200);
	pthread_mutex_unlock(&p->table->forks[p->left_fork]);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (!wait_for_start(p->table))
		return (NULL);
	if (p->table->count == 1)
		return (one_philosopher(p), NULL);
	if (p->id % 2 == 0)
		wait_ms(p->table, p->table->time_eat / 2);
	while (!is_stopped(p->table))
	{
		if (!eat(p))
			break ;
		if (!log_action(p, "is sleeping"))
			break ;
		wait_ms(p->table, p->table->time_sleep);
		if (!log_action(p, "is thinking"))
			break ;
		if (p->table->count % 2 && p->table->time_eat * 2
			> p->table->time_sleep)
			wait_ms(p->table, (p->table->time_eat * 2
					- p->table->time_sleep) / 2);
	}
	return (NULL);
}
