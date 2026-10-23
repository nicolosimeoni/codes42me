CC = cc
AR = ar
CFLAGS = -Wall -Wextra -Werror -std=c99 -O2
CPPFLAGS =
NAME = libgnl.a
SRC = get_next_line.c get_next_line_utils.c
OBJ = $(SRC:.c=.o)
all: $(NAME)
$(NAME): $(OBJ)
	$(AR) rcs $@ $^
%.o: %.c $(wildcard *.h) 
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o
fclean: clean
	rm -f $(NAME) libgnl_bonus.a
re:
	$(MAKE) fclean
	$(MAKE) all

bonus: libgnl_bonus.a
libgnl_bonus.a: get_next_line_bonus.o get_next_line_utils.o
	$(AR) rcs $@ $^

.PHONY: all clean fclean re bonus
