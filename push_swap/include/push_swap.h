#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

typedef struct s_stack
{
	int	*items;
	int	len;
	int	capacity;
} t_stack;

typedef struct s_game
{
	t_stack	a;
	t_stack	b;
} t_game;

typedef enum e_op
{
	SA, SB, SS, PA, PB, RA, RB, RR, RRA, RRB, RRR, INVALID
} t_op;

typedef struct s_plan
{
	int	steps_a;
	int	steps_b;
	int	cost;
} t_plan;

int		parse_args(t_game *game, int argc, char **argv);
void	free_game(t_game *game);
void	print_error(void);
int		is_sorted(const t_stack *stack);
void	perform(t_game *game, t_op operation, int output);
t_op	parse_op(const char *line);
void	sort_stack(t_game *game);
void	sort_small(t_game *game);
void	sort_three(t_game *game);
void	rotate_min_to_top(t_game *game);

#endif
