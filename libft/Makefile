# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pleal-ca <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/20 18:08:31 by pleal-ca          #+#    #+#              #
#    Updated: 2020/01/28 13:59:39 by lborges-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = libft.a
SRC     = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c\
		  ft_memcmp.c ft_strlcpy.c ft_strlcat.c ft_strrchr.c ft_atoi.c \
		  ft_strncmp.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c\
		  ft_isprint.c ft_toupper.c ft_tolower.c ft_strnstr.c\
		  ft_split.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c\
		  ft_putnbr_fd.c ft_itoa.c ft_strtrim.c ft_strmapi.c ft_iswhitespace.c\
		  get_next_line.c get_next_line_utils.c
		
BONUS	=  ft_lstnew.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstadd_front.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJS    = $(SRC:.c=.o)
OBJSB	= $(BONUS:.c=.o)
RM      = rm -f
CFLAGS  = -Wall -Werror -Wextra

$(NAME): $(OBJS) 
	@gcc $(CFLAGS) $(SRC) -c
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

all: $(NAME)

clean:
	@$(RM) $(OBJS) $(OBJSB)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

bonus: $(OBJSB) 
	@gcc $(CFLAGS) $(SRC) $(BONUS) -c
	@ar rc $(NAME) $(OBJS) $(OBJSB) 
	@ranlib $(NAME)
