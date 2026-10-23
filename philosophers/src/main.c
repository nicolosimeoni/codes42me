#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;
	int		ok;

	memset(&table, 0, sizeof(table));
	if (!parse_arguments(argc, argv, &table))
	{
		write(2, "Error: expected 4 or 5 positive integer arguments\n", 50);
		return (1);
	}
	if (!init_table(&table))
	{
		write(2, "Error: unable to initialize simulation\n", 39);
		destroy_table(&table);
		return (1);
	}
	ok = run_simulation(&table);
	destroy_table(&table);
	if (!ok)
		write(2, "Error: unable to start threads\n", 31);
	return (!ok);
}
