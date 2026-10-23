NAME := push_swap
BONUS := checker
CC := cc
CFLAGS := -Wall -Wextra -Werror -Iinclude
COMMON := src/parse.c src/operations.c
SORT := src/sort_small.c src/sort_greedy.c
OBJS := $(COMMON:.c=.o) $(SORT:.c=.o) src/main.o
BONUS_OBJS := $(COMMON:.c=.o) bonus/checker.o

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(BONUS): $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) -o $@

bonus: $(BONUS)

%.o: %.c include/push_swap.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS)

re: fclean all

test: all bonus
	python3 tests/test_push_swap.py

.PHONY: all bonus clean fclean re test
