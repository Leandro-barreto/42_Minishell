SRC = lex.c lex_utils.c lex_utils2.c get_next_line.c delete.c parse.c\
	  parse_aux.c paths.c unset.c erro.c execute.c execbuiltin.c\
	  export_utils.c echo.c export.c 
NAME = minishell
LIBRARY=minishell.a
HEADER = minishell.h
NUM = $(expr $(cat map.cub | wc -l) - 11)
OBJS = $(SRC:.c=.o)
all : $(NAME)

$(NAME): 
	(cd gnl/ ; cp get_next_line.c ../)
	(cd libft/ ; make ; cp libft.a ../$(LIBRARY))
	gcc -g -Wall -Wextra -Werror -c $(SRC)
	ar rcs $(LIBRARY) $(OBJS)
	(rm get_next_line.c)
	gcc -g main.c $(LIBRARY) -o $(NAME)
clean:	
	if [ $(VERO)=1 ]; then rm $(OBJS); VERO=0; fi
	(cd libft ; make clean)

fclean: clean
	if [ $(VERA)=1 ]; then rm $(LIBRARY) $(NAME); VERA=0; fi
	(cd libft/ ; make fclean)

re: fclean all


#-g -fsanitize=address 
