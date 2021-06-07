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
	if (signum == 2 && signum == SIGINT)
	{
		write(1, "\n", 1);
		if (!g_global.run)
		{
			ft_bzero(g_global.line, ft_strlen(g_global.line));
			write(1, "$mini> ", 7);
		}
	}
	if (signum == 3 && signum == SIGQUIT)
	{
		if (g_global.run)
			ft_putstr_fd("Quit\n", 1);
		else
			ft_putstr_fd("", 1);
	}
}

void	main2(t_lex *lex, t_env *m_envp)
{
	int			n;
	t_tokens	*tok;
	t_cmdTable	*cmdtable;

	cmdtable = NULL;
	if (!lex->error)
	{
		tok = lex->data;
		lex->curr = 0;
		cmdtable = (t_cmdTable *)malloc(sizeof(t_cmdTable) * (lex->nsemis + 1));
		cmdtable[lex->curr] = start_cmdtable(lex, cmdtable[lex->curr]);
		parser_all(lex, cmdtable, m_envp);
		if (!lex->error)
		{
			n = -1;
			g_global.run = 1;
			while (++n < (lex->nsemis + 1))
				if (cmdtable[n].nSimpleCmd)
					execute_cmd(cmdtable, m_envp, lex, n);
		}
	}
	if (lex->error != 0)
		g_global.exit = printerror(lex->error, 0, lex->errmsg, 0);
	delete_table(cmdtable, lex);
	dellines(ft_strlen(g_global.line));
}

int	main(int argc, char *argv[], char **envp)
{
	t_lex			*lex;
	t_env			*m_envp;
	char			**history;

	if (argc > 2)
		printf("Pra q tanto argumento? %s", argv[0]);
	m_envp = start_env(envp, 0);
	signal(SIGQUIT, sighandler);
	signal(SIGINT, sighandler);
	history = (char **)malloc(1000 * sizeof(char *));
	g_global.exit = 0;
	while (1)
	{
		g_global.run = 0;
		read_line(history);
		tcsetattr(STDIN_FILENO, TCSAFLUSH, g_global.save);
		free(g_global.save);
		g_global.save = NULL;
		lex = (t_lex *)malloc(sizeof(t_lex));
		*lex = start_lexer(lex);
		lexer(g_global.line, lex, ft_strlen_mini(g_global.line));
		main2(lex, m_envp);
	}
	delete_env(m_envp, 1);
	return (0);
}
