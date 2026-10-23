#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc == 1)
		return (0);
	if (!parse_args(&game, argc, argv))
	{
		print_error();
		free_game(&game);
		return (1);
	}
	sort_stack(&game);
	free_game(&game);
	return (0);
}
