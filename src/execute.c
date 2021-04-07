/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lborges- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:03:49 by lborges-          #+#    #+#             */
/*   Updated: 2021/04/02 18:55:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			exec_builtin(t_cmdtable *cmd, int i, char **m_envp, t_lex *lex)
{
	if (!ft_strncmp(cmd->scmd[i]->args[0], "echo", 4))
		return (miniecho(cmd->scmd[i]));
	else if (!ft_strncmp(cmd->scmd[i]->args[0], "cd", 2))
		return (minicd(cmd->scmd[i], m_envp));
	else if (!ft_strncmp(cmd->scmd[i]->args[0], "pwd", 3))
		return (minipwd(cmd->scmd[i]));
	else if (!ft_strncmp(cmd->scmd[i]->args[0], "env", 3))
		return (minienv(cmd->scmd[i], m_envp));
	else if (!ft_strncmp(cmd->scmd[i]->args[0], "unset", 5))
		return (miniunset(cmd->scmd[i], m_envp));
	else if (!ft_strncmp(cmd->scmd[i]->args[0], "export", 6))
		return (miniexport(cmd->scmd[i], m_envp));
	else if (!ft_strncmp(cmd->scmd[i]->args[0], "exit", 4))
		return (miniexit(cmd, lex, i));
	return (12);
}

void		handle_fd(t_exec *exec, t_cmdtable *cmd)
{
	dup2(exec->fdin, 0);
	close(exec->fdin);
	if (exec->i == cmd->nsimplecmd - 1)
	{
		if (cmd->outfile && cmd->outtype == '>')
			exec->fdout = open(cmd->outfile, O_WRONLY | O_CREAT |
					O_TRUNC, 0666);
		else if (cmd->outfile && cmd->outtype == GGREATER)
			exec->fdout = open(cmd->outfile, O_WRONLY | O_APPEND |
					O_CREAT, 0666);
		else
			exec->fdout = dup(exec->tmpout);
	}
	else
	{
		pipe(exec->fdpipe);
		exec->fdout = exec->fdpipe[1];
		exec->fdin = exec->fdpipe[0];
	}
	dup2(exec->fdout, 1);
	close(exec->fdout);
}

t_simplecmd	*handlequotes(t_simplecmd *scmd)
{
	int		i;
	int		j;
	int		size;

	i = -1;
	while (++i <= scmd->nargs)
	{
		if (scmd->args[i][0] == '\"' || scmd->args[i][0] == '\'')
		{
			size = ft_strlen(scmd->args[i]);
			j = 0;
			while (j < size - 2)
			{
				scmd->args[i][j] = scmd->args[i][j + 1];
				j++;
			}
			scmd->args[i][size - 2] = '\0';
		}
	}
	return (scmd);
}

void		handle_exec(t_exec *ex, t_cmdtable *cmd, char **m_envp, t_lex *lex)
{
	int		i;
	char	*cmdtext;
	int		j;

	j = -1;
	i = ex->i;
	while (++j <= cmd->scmd[i]->nargs)
		cmd->scmd[i]->args[j] = checkdollar(cmd->scmd[i]->args[j], lex, m_envp);
	if (cmd->scmd[i]->builtin == 1)
		lex->exit = exec_builtin(cmd, i, m_envp, lex);
	else
	{
		ex->ret = fork();
		if (ex->ret == 0)
		{
			signal(SIGINT, NULL);
			cmdtext = ft_strdup(cmd->scmd[i]->args[0]);
			cmd->scmd[i] = handlequotes(cmd->scmd[i]);
			lex->exit = execve(cmdtext, cmd->scmd[i]->args, m_envp);
			exit(lex->exit);
		}
	}
}

int			execute_cmd(t_cmdtable *cmd, char **m_envp, t_lex *lex)
{
	t_exec	*exec;

	exec = (t_exec *)malloc(sizeof(t_exec));
	*exec = (t_exec) {0};
	exec->tmpin = dup(0);
	exec->tmpout = dup(1);
	exec->fdin = dup(0);
	if (cmd->infile)
		exec->fdin = open(cmd->infile, O_RDONLY);
	exec->i = 0;
	while (exec->i < cmd->nsimplecmd)
	{
		handle_fd(exec, cmd);
		handle_exec(exec, cmd, m_envp, lex);
		exec->i++;
	}
	dup2(exec->tmpin, 0);
	dup2(exec->tmpout, 1);
	close(exec->tmpin);
	close(exec->tmpout);
	waitpid(exec->ret, NULL, 0);
	return (0);
}
