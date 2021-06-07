#include "minishell.h"

int	exec_builtin(t_cmdTable *cmd, t_exec *exec, t_env *m_envp, t_lex *lex)
{
	int	i;
	int	n;

	i = exec->i;
	n = exec->n;
	if (!ft_strncmp(cmd[n].sCmd[i]->args[0], "echo", 4))
		return (miniecho(cmd[n].sCmd[i]));
	else if (!ft_strncmp(cmd[n].sCmd[i]->args[0], "cd", 2))
		return (minicd(cmd[n].sCmd[i], m_envp));
	else if (!ft_strncmp(cmd[n].sCmd[i]->args[0], "pwd", 3))
		return (minipwd(cmd[n].sCmd[i]));
	else if (!ft_strncmp(cmd[n].sCmd[i]->args[0], "env", 3))
		return (minienv(cmd[n].sCmd[i], m_envp));
	else if (!ft_strncmp(cmd[n].sCmd[i]->args[0], "unset", 5))
		return (miniunset(cmd[n].sCmd[i], m_envp));
	else if (!ft_strncmp(cmd[n].sCmd[i]->args[0], "export", 6))
		return (miniexport(cmd[n].sCmd[i], m_envp));
	else if (!ft_strncmp(cmd[n].sCmd[i]->args[0], "exit", 4))
		return (miniexit(cmd, lex, n, i));
	return (12);
}

void	handle_fd(t_exec *exec, t_cmdTable *cmd)
{
	dup2(exec->fdin, 0);
	close(exec->fdin);
	if (exec->i == cmd[exec->n].nSimpleCmd - 1)
	{
		if (cmd[exec->n].outfile && cmd[exec->n].outtype == '>')
			exec->fdout = open(cmd[exec->n].outfile, O_WRONLY
					| O_TRUNC | O_CREAT, 0664);
		else if (cmd[exec->n].outfile && cmd[exec->n].outtype == GGREATER)
			exec->fdout = open(cmd[exec->n].outfile, O_WRONLY
					| O_APPEND | O_CREAT, 0664);
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

void	handle_exec(t_exec *exec, t_cmdTable *cmd, t_env *m_envp, t_lex *lex)
{
	int		i;
	int		n;
	int		status;

	i = exec->i;
	n = exec->n;
	if (cmd[n].sCmd[i]->builtin == 1)
		lex->error = exec_builtin(cmd, exec, m_envp, lex);
	else
	{
		exec->ret = fork();
		if (exec->ret == 0)
		{
			cmd[n].sCmd[i] = handlequotes(cmd[n].sCmd[i]);
			execve(cmd[n].sCmd[i]->args[0], cmd[n].sCmd[i]->args, m_envp->env);
			exit(EXIT_FAILURE);
		}
		waitpid(exec->ret, &status, 0);
		g_global.exit = status;
		if (WIFEXITED(status))
			g_global.exit = WEXITSTATUS(status);
	}
}

int	execute_cmd(t_cmdTable *cmd, t_env *m_envp, t_lex *lex, int n)
{
	t_exec	*exec;

	exec = (t_exec *)malloc(sizeof(t_exec));
	*exec = (t_exec){0};
	exec->tmpin = dup(STDIN_FILENO);
	exec->tmpout = dup(STDOUT_FILENO);
	exec->fdin = dup(exec->tmpin);
	exec->n = n;
	if (cmd[n].infile)
		exec->fdin = open(cmd[n].infile, O_RDONLY);
	exec->i = 0;
	while (exec->i < cmd[n].nSimpleCmd)
	{
		handle_fd(exec, cmd);
		handle_exec(exec, cmd, m_envp, lex);
		exec->i++;
	}
	dup2(exec->tmpin, 0);
	dup2(exec->tmpout, 1);
	close(exec->tmpin);
	close(exec->tmpout);
	free(exec);
	return (0);
}
