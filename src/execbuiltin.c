/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execbuiltin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lborges- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:03:49 by lborges-          #+#    #+#             */
/*   Updated: 2021/04/02 17:00:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			minicd(t_simplecmd *scmd, char **m_envp)
{
	int		i;
	int		ret;
	char	buf[255];
	DIR		*dir;

	dir = NULL;
	if (scmd->nargs > 1)
		return (ft_putstr_fd("minishell: cd: wrong options\n", 1));
	if (scmd->nargs == 0)
		ret = chdir(ft_returnenvvar("HOME", m_envp));
	else
	{
		ret = -1;
		dir = opendir(scmd->args[1]);
		if (dir)
			ret = chdir(scmd->args[1]);
	}
	if (!dir || ret < 0)
		ret = printerror(-1, 2, scmd->args[1], 1);
	i = -1;
	getcwd(buf, 255);
	while (m_envp[++i])
		if (ft_strnstr(m_envp[i], "PWD", 3))
			m_envp[i] = ft_strjoin("PWD=", buf);
	return (ret);
}

int			minienv(t_simplecmd *scmd, char **m_envp)
{
	int		i;

	i = -1;
	if (scmd->nargs > 0)
	{
		ft_putstr_fd("minishell: env: Pra q tudo isso?!\n", 1);
		return (127);
	}
	else
	{
		while (m_envp[++i])
		{
			ft_putstr_fd(m_envp[i], 1);
			write(1, "\n", 1);
		}
	}
	return (0);
}

int			miniexit(t_cmdtable *cmd, t_lex *lex, int i)
{
	int		j;
	int		exitvar;

	j = -1;
	exitvar = 0;
	if (cmd->scmd[i]->nargs > 0 && cmd->scmd[i]->args[1][0] == '-')
	{
		printf("mini: exit: Invalid option %s\n", cmd->scmd[i]->args[1]);
		exitvar = 1;
	}
	else if (cmd->scmd[i]->nargs > 0)
		while (cmd->scmd[i]->args[1][++j])
			if (cmd->scmd[i]->args[1][j] < 48 || cmd->scmd[i]->args[1][j] > 57)
			{
				printf("exit: Illegal number: %s\n", cmd->scmd[i]->args[1]);
				exitvar = 2;
			}
	j = 0;
	if (exitvar)
		exit(lex->exit = exitvar);
	if (cmd->scmd[i]->nargs > 0)
		j = ft_atoi(cmd->scmd[i]->args[1]);
	delete_table(cmd, lex);
	exit(lex->exit = j);
	return (0);
}

int			minipwd(t_simplecmd *scmd)
{
	char	buf[255];

	if (scmd->nargs > 0 && scmd->args[1][0] == '-')
	{
		printf("mini: pwd: Invalid option %s\n", scmd->args[1]);
		return (1);
	}
	else
	{
		getcwd(buf, 255);
		if (*buf)
			printf("%s\n", buf);
		else
		{
			printf("mini: pwd: error getting working dir");
			return (2);
		}
	}
	return (0);
}
