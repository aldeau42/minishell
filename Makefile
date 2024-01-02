
NAME =	minishell

SRCS =	minishell.c \
		minishell2.c \
		signal.c \
		ft_utils/ft_putendl_fd.c \
		ft_utils/ft_putstr_fd.c \
		ft_utils/ft_split.c \
		ft_utils/ft_strjoin.c \
		ft_utils/ft_strnstr.c \
		ft_utils/ft_strdup.c \
		ft_utils/ft_gcstrdup.c \
		ft_utils/skipSpace.c \
		ft_utils/ft_strcmp.c \
		ft_utils/ft_strncmp.c \
		ft_utils/ft_strcat.c \
		ft_utils/ft_atoi.c \
		builtins/builtin_base.c \
		builtins/builtin_utils.c \
		builtins/cd.c \
		builtins/echo.c \
		builtins/env.c \
		builtins/exit.c \
		builtins/export.c \
		builtins/pwd.c \
		builtins/unset.c \
		parsing/parsing.c \
		parsing/quoteCheck.c \
		parsing/varEnvChang.c \
		parsing/put_maillon_str.c \
		parsing/check_pipe_at_start.c \
		parsing/add_list_exec.c \
		parsing/check_var.c \
		parsing/put_entry.c \
		parsing/put_sortie.c \
		parsing/listeExecution.c \
		parsing/path.c \
		exec/start.c \
		exec/start_utils.c \
		exec/exec.c \
		exec/exec2.c \
		exec/pipes.c \
		exec/pipe_at_end.c \
       	exec/redirections.c \
        exec/utils.c \
        exec/utils2.c \
        exec/utils3.c \

LIBMEMDIR = mem
LIBMEM = libmem.a
LIBMEMFLAGS = -L $(LIBMEMDIR) -l:$(LIBMEM)

LIBFTDIR = libft
LIBFT = libft.a
LIBFTFLAGS = -L $(LIBFTDIR) -l:$(LIBFT)
#DEBUG = -fsanitize=address
CC = gcc

CFLAGS = -Wall -Wextra -Werror -D_XOPEN_SOURCE=700 -lreadline -lhistory -g3

OBJS = $(SRCS:.c=.o)

$(NAME):        $(OBJS)
		@make -C $(LIBMEMDIR)
		@make -C $(LIBFTDIR)
		@$(CC) $(OBJS) -o $(NAME) $(CFLAGS) $(DEBUG) $(LIBMEMFLAGS) $(LIBFTFLAGS)

all:    $(NAME)


clean:
		@rm -f $(OBJS)

fclean:
		@rm -f $(OBJS) $(NAME)
		@make -C ${LIBMEMDIR} fclean

re:		fclean $(NAME)

.PHONY:	all clean fclean re

.SILENT:
