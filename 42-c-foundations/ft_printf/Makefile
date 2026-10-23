CC = cc
AR = ar
CFLAGS = -Wall -Wextra -Werror -std=c99 -O2
CPPFLAGS =
NAME = libftprintf.a
SRC = ft_printf.c
OBJ = $(SRC:.c=.o)
all: $(NAME)
$(NAME): $(OBJ)
	$(AR) rcs $@ $^
%.o: %.c $(wildcard *.h) ../libft/libft.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o
fclean: clean
	rm -f $(NAME) libgnl_bonus.a
re:
	$(MAKE) fclean
	$(MAKE) all

bonus: all

.PHONY: all clean fclean re bonus
