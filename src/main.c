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

void	sighandler(int signum)
{
	if (signum == 2)
		write(1, "\n$mini> ", 8);
	if (signum == 3)
		exit(signum);
}

int		main2(t_lex *lex, t_cmdTable *cmdtable, char **m_envp, char *line)
{
	int		n;

	n = lexer(line, lex, n);
	lex->curr = 0;
	cmdtable = (t_cmdTable *)malloc(sizeof(t_cmdTable) *(lex->nsemis + 1));
	cmdtable[lex->curr] = start_cmdtable(lex, cmdtable[lex->curr]);
	parser_all(lex, cmdtable, m_envp);
	n = -1;
	while (++n < (lex->nsemis + 1))
		if (cmdtable[n].nSimpleCmd)
			execute_cmd(cmdtable[n], m_envp, lex);
	if (lex->error < 0)
		lex->exit = printerror(lex->error, 0, lex->errmsg, 0);
	delete_table(cmdtable, lex);
}

int		main(int argc, char *argv[], char **envp)
{
	char		*line;
	int			n;
	t_lex		*lex;
	t_cmdTable	*cmdtable;
	char		**m_envp;

	if (argc > 2)
		printf("Pra q tanto argumento? %s", argv[0]);
	m_envp = envp; 
	signal(SIGQUIT, sighandler);
	signal(SIGINT, sighandler);
	lex = (t_lex *)malloc(sizeof(t_lex));
	while (1)
	{
		g_run = 0;
		*lex = start_lexer(lex);
		write(1, "$mini> ", 7);
		get_next_line(0, &line);
		n = ft_strlen(line);
		if (n == 0)
			continue ;
		main2(lex, cmdtable, m_envp, line);
	}
	return 0;
}
