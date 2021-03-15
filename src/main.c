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

#include "minishell.h"

int main(int argc, char *argv[], char **envp)
{
	char		*line;
	int			n;
	t_lex		lex;
	// t_tokens	*tok;
	t_cmdTable	*cmdtable;

	if (argc > 2)
		printf("Pra q tanto argumento? %s", argv[0]);
	g_envp = envp; 
	while (1)
	{
		start_lexer(&lex);
		write(1, "$> ", 3);
		get_next_line(0, &line);
		n = ft_strlen(line);
		if (n == 0)
			continue ;
		if (n >= 0)
			n = lexer(line, &lex, n);
		lex.curr = 0;
		cmdtable = (t_cmdTable *)malloc(sizeof(t_cmdTable) *(lex.nsemis + 1));
		cmdtable[lex.curr] = start_cmdtable(&lex, cmdtable[lex.curr]);
		parser_all(&lex, cmdtable);
		if (lex.error < 0)
			printf("ERROR!! %i\n", lex.error);
		printf("\n--------Testando tabela de comandos-----------\n");
		for (int j = 0; (j < (lex.nsemis + 1) && lex.error >= 0); j++)
		{
			printf("\n---------Cmds Tabela %i:----------\n", j);
			for (int k = 0; k < cmdtable[j].nAvalSimpleCmd; k++)
			{
				printf("Comando %i: %s\n", k, cmdtable[j].sCmd[k]->args[0]);
				printf("Builtin %i\n", cmdtable[j].sCmd[k]->builtin); 
			}
			printf("Arquivos Tabela %i:\n", j);
			printf("Infile: %s\nOutfile: %s\n", cmdtable[j].infile, cmdtable[j].outfile);
		}
		printf("\n----------Testando comandos-------------\n");
		for (int j = 0; (j < (lex.nsemis + 1) && lex.error >= 0); j++)
		{
			if (cmdtable[j].nAvalSimpleCmd)
				execute_cmd(&cmdtable[j]);
		}
		delete_table(cmdtable, &lex);
	}
	return 0;
}
