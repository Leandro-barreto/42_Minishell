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

#include "parse.h"
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
	t_cmdTable	*cmdtable;

	start_lexer(&lex);
	//while (ft_strcmp(line, "exit"))
	//{
		write(1, "$> ", 3);
		get_next_line(0, &line);
		n = ft_strlen(line);
		if (n >= 0)
			n = lexer(line, &lex, n);
	//}
	printf("\n----------------Testando tokens------------\n");
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
		printf("Number %i\n", lex.npipes[0]);
		printf("Number %i\n", lex.nsemis);
	}
	lex.curr = 0;
	cmdtable = (t_cmdTable *)malloc(sizeof(t_cmdTable) *(lex.nsemis + 1));
	cmdtable[lex.curr] = start_cmdtable(&lex, cmdtable[lex.curr]);
	parser_cmds(&lex, cmdtable);
	if (lex.error < 0)
		printf("ERROR!!\n");
	printf("\n--------Testando tabela de comandos-----------\n");
	for (int j = 0; (j < (lex.nsemis + 1) && lex.error >= 0); j++)
	{
		printf("\n---------Cmds Tabela %i:----------\n", j);
		for (int k = 0; k < cmdtable[j].nAvalSimpleCmd; k++)
		{
			printf("Comando %i: %s\n", k, cmdtable[j].sCmd[k]->args[0]); 
		}
		printf("Arquivos Tabela %i:\n", j);
		printf("Infile: %s\nOutfile: %s\n", cmdtable[j].infile, cmdtable[j].outfile);
	}
	return 0;
}
