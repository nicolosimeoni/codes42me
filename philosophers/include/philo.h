#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	meal_lock;
	long			last_meal;
	int			meals;
	int			id;
	int			left_fork;
	int			right_fork;
	t_table			*table;
} t_philo;

struct s_table
{
	int			count;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	int			meal_goal;
	long			start;
	int			ready;
	int			stopped;
	pthread_mutex_t	state_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	int			state_initialized;
	int			print_initialized;
	int			forks_initialized;
	int			meals_initialized;
};

int		parse_arguments(int argc, char **argv, t_table *table);
int		init_table(t_table *table);
void	destroy_table(t_table *table);
int		run_simulation(t_table *table);
void	monitor_simulation(t_table *table);
void	*philosopher_routine(void *arg);
long	now_ms(void);
void	wait_ms(t_table *table, long duration);
int		is_stopped(t_table *table);
void	stop_simulation(t_table *table);
void	report_death(t_philo *philo);
int		log_action(t_philo *philo, const char *message);

#endif
