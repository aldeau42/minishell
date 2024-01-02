SRCS    = ft_isalpha.c\
	  ft_memchr.c\
	  ft_memset.c\
		ft_strlen.c\
		ft_tolower.c\
		ft_strrchr.c\
		ft_atoi.c\
		ft_isascii.c\
		ft_memcmp.c\
		ft_strchr.c\
		ft_strncmp.c\
		ft_toupper.c\
                ft_bzero.c\
		ft_isdigit.c\
		ft_memcpy.c\
		ft_strlcat.c\
		ft_strnstr.c\
		ft_isalnum.c\
                ft_isprint.c\
		ft_memmove.c\
		ft_memdel.c\
		ft_strlcpy.c\
		ft_calloc.c\
		ft_strdup.c\
		ft_substr.c\
                ft_itoa.c\
		ft_putchar_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_putstr_fd.c\
                ft_split.c\
		ft_striteri.c\
		ft_strmapi.c\
		ft_strtrim.c\
		ft_printf.c\
		ft_print_numbers.c\
		ft_print_words.c\
		get_next_line_bonus.c\
		get_next_line_utils_bonus.c\
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \

NAME	= libft.a

OBJS	= ${SRCS:.c=.o}

DIR_OBJ = ./obj

all : ${NAME}

.c.o	:
		gcc -Wall -Wextra -Werror -g -I . -c $< -o ${<:.c=.o}

${NAME} : ${OBJS}
		ar rc ${NAME} ${OBJS}
		ranlib ${NAME}
		mkdir -p obj
		mv *.o obj
clean :
		rm -f *.o
		rm -rf ${DIR_OBJ}

fclean : clean
		rm -f ${NAME}

re : fclean all
