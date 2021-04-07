NAME = minishell.a

FLAGS = -Wall -Werror -Wextra 

SRCS = src/main.c		\
	   src/delete.c	\
	   src/echo.c	\
	   src/erro.c		\
	   src/execbuiltin.c		\
	   src/execute.c		\
	   src/export.c		\
	   src/export_utils.c		\
	   src/lex.c		\
	   src/lex_utils.c		\
	   src/lex_utils2.c		\
	   src/parse_utils.c		\
	   src/parse.c			\
	   src/paths.c	\
	   src/unset.c		\

OBJS = $(SRCS:.s=.o)

UTILS = src/libft/libft.a 
		#src/libft/ft_printf/libftprintf.a

all: $(NAME)

$(NAME): $(OBJS)
	@cd src/libft && make
	@ar rc $(NAME) $(OBJS) 
	@clang $(FLAGS) $(OBJS) $(UTILS) -o minishell

%.o: %.c
	@clang $(FLAGS) $<

clean:
	@rm -f $(O)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean
.PRECIOUS: minishell
