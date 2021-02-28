/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lborges- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 09:59:55 by lborges-          #+#    #+#             */
/*   Updated: 2020/10/20 16:09:42 by lborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> 
#include <string.h> 
#include "./lexer/lex.h"
#include "./libft/libft.h"

int main(void)
{
	char		*line;
	int			n;
	t_lex		lex;
	t_tokens	*tok;

	start_lexer(&lex);
	//while (ft_strcmp(line, "exit"))
	//{
		write(1, "$> ", 3);
		get_next_line(0, &line);
		n = ft_strlen(line);
		if (n >= 0)
			n = lexer(line, &lex, n);
	//}
	if (lex.error < 0)
	{
		printf("Quote %c error\n", -lex.error); 
		//free(&lex);
		//destroy_structs(&lex, NULL);
	}	
	else
	{
		tok = lex.data;
		while (tok != NULL)
		{
			printf("\nTokens:\n");
			printf("Texto %s\n", tok->data);
			printf("Tipo %i\n", tok->type);
			printf("Quote %i\n", tok->quote);
			printf("Next %p\n", tok->next);
			tok = tok->next;
		}
		printf("Number %i\n", lex.size);
	}
	return 0;
}
