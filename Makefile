NAME = minishell.a
EX = minishell

FLAGS = -Wall -Werror -Wextra -ltermcap

SRCS = src/main.c		\
	   src/cd.c	\
	   src/delete.c	\
	   src/echo.c	\
	   src/erro.c		\
	   src/execbuiltin.c		\
	   src/execute.c		\
	   src/execute_utils.c		\
	   src/export.c		\
	   src/lex.c		\
	   src/lex_utils.c		\
	   src/lex_utils2.c		\
	   src/parse_aux.c\
	   src/parse_dollar.c\
	   src/parse.c\
	   src/paths.c\
	   src/unset.c\
	   src/termcap.c\
	   src/termcap_utils.c\
	   src/termcap_utils2.c\
	   src/ft_exit.c\
	   src/ft_isin.c\
	   src/environment.c

OBJS = $(SRCS:.s=.o)

UTILS = src/libft/libft.a 
		#src/libft/ft_printf/libftprintf.a

all: $(NAME)

$(NAME): $(OBJS)
	@cd src/libft && make
	@ar rc $(NAME) $(OBJS) 
	@clang $(FLAGS) $(OBJS) $(UTILS) -o $(EX)

%.o: %.c
	@clang $(FLAGS) $<

clean:
	@rm -f $(O)

fclean: clean
	@rm -f $(NAME) $(EX)

re: fclean all

.PHONY: all clean fclean
.PRECIOUS: minishell
