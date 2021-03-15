NAME = minishell
LIB = ./libft/libft.a
LEXER = ./lexer
PARSER = ./parser
TREE = ./tree
CMD	 = ./cmd
EXEC = ./exec

SRCS = minishell.c parse.c\
	   $(LEXER)/lex.c $(LEXER)/lex_utils.c\

OBJS = $(SRCS:.c=.o)
RM = rm -f
CFLAGS = -Wall -Werror -Wextra

$(NAME): $(OBJS)
	@cd libft && make
	@cd lexer && clang $(CFLAGS) -c *.c 
	@clang $(CFLAGS) $(OBJS) $(LIB) -o $(NAME) 
all: $(NAME)

clean:
	$(RM) $(OBJS) 

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean
