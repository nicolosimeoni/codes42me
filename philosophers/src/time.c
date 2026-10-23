#include "philo.h"

long	now_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000L + time.tv_usec / 1000L);
}

void	wait_ms(t_table *table, long duration)
{
	long	end;
	long	remaining;

	end = now_ms() + duration;
	while (!is_stopped(table))
	{
		remaining = end - now_ms();
		if (remaining <= 0)
			break ;
		if (remaining > 2)
			usleep(1000);
		else
			usleep(200);
	}
}
