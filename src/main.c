/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lborges- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 09:59:55 by lborges-          #+#    #+#             */
/*   Updated: 2021/04/02 17:23:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler(int signum)
{
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

int		main2(t_lex *lex, char **m_envp)
{
	int			n;
	t_cmdtable	*cmdtable;
	int			aux;

	lex->curr = 0;
	if (lex->error == 0)
	{
		cmdtable = (t_cmdtable *)malloc(sizeof(t_cmdtable) * (lex->nsemis + 1));
		cmdtable[lex->curr] = start_cmdtable(lex, cmdtable[lex->curr]);
		parser_all(lex, cmdtable, m_envp);
		n = -1;
		g_run = 1;
		while (++n < (lex->nsemis + 1))
			if (cmdtable[n].nsimplecmd)
				execute_cmd(&cmdtable[n], m_envp, lex);
	}
	else
		cmdtable = NULL;
	lex->error = -errno;
	if (lex->error < 0 && lex->exit < 0)
		lex->exit = printerror(lex->error, 0, lex->errmsg, 0);
	aux = lex->exit;
	delete_table(cmdtable, lex);
	return (aux);
}

char	*readmini(char *line)
{
	ssize_t		r;
	char		*aux;

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
	int			aux;

	if (argc > 2)
		printf("Pra q tanto argumento? %s\n", argv[0]);
	aux = 0;
	m_envp = envp;
	signal(SIGQUIT, sighandler);
	signal(SIGINT, sighandler);
	while (1)
	{
		g_run = 0;
		lex = (t_lex *)malloc(sizeof(t_lex));
		*lex = start_lexer(lex);
		lex->exit = aux;
		write(1, "$mini> ", 7);
		ft_bzero(line, 4096);
		ft_strlcpy(line, readmini(line), 8192);
		lexer(line, lex, ft_strlen(line));
		aux = main2(lex, m_envp);
	}
	return (0);
}
