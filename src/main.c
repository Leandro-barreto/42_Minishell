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
	//printf("Quit: %d\n", signum);;
	if (signum == 2 && signum == SIGINT)
	{
		write(1, "\n", 1);
		if (!g_run)
			write(1, "$mini> ", 7);
	}
	if (signum == 3 && signum == SIGQUIT)
	{
		if (g_run)
			printf("Quit: %d\n", signum);
		else
			ft_putstr_fd("\b \b\b \b", 1);
	}
}

void	main2(t_lex *lex, char **m_envp)
{
	int		n;
	t_tokens *tok;
	t_cmdTable	*cmdtable;

	tok = lex->data;
	lex->curr = 0;
	if (lex->error == 0)
	{
		cmdtable = (t_cmdTable *)malloc(sizeof(t_cmdTable) * (lex->nsemis + 1));
		cmdtable[lex->curr] = start_cmdtable(lex, cmdtable[lex->curr]);
		parser_all(lex, cmdtable, m_envp);
		n = -1;
		g_run = 1;
		while (++n < (lex->nsemis + 1))
			if (cmdtable[n].nSimpleCmd)
				execute_cmd(&cmdtable[n], m_envp, lex);
	}
	else
		cmdtable = NULL;
	if (lex->error < 0)
		lex->exit = printerror(lex->error, 0, lex->errmsg, 0);
	delete_table(cmdtable, lex);
}

char	*readmini(char *line)
{
	ssize_t	r;
	char	*aux;

	r = 1;
	while (1)
	{
		if (!(*line))
			r = read(1, line, 4096);
		if (r < 0 || *line == '\0')
			exit(1);
		if (line[ft_strlen(line) - 1] == '\n')
			return (line);
		else
		{
			aux = malloc(4096);
			r = read(1, aux, 4096);
			line = ft_strjoin(line, aux);	
		}
	}
	return (line);
}

int		main(int argc, char *argv[], char **envp)
{
	char		line[4097];
	t_lex		*lex;
	char		**m_envp;

	if (argc > 2)
		printf("Pra q tanto argumento? %s", argv[0]);
	m_envp = envp; 
	signal(SIGQUIT, sighandler);
	signal(SIGINT, sighandler);
	while (1)
	{
		g_run = 0;
		lex = (t_lex *)malloc(sizeof(t_lex));
		*lex = start_lexer(lex);
		write(1, "$mini> ", 7);
		ft_bzero(line, 4096);
		ft_strlcpy(line, readmini(line), 8192);
		printf("LLLine: %s \n\n", line);
		lexer(line, lex, ft_strlen(line));
		main2(lex, m_envp);
	}
	return (0);
}
