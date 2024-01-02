NAME=libmem.a
TEST=test
CC=gcc
CFLAGS=-Wall -Werror -Wextra
AR=ar rcs
RM=rm -f

SRCS=mem.c
OBJS=$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
	$(RM) $(OBJS)
	$(RM) $(TEST)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
