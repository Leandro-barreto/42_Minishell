#include "minishell.h"

int		exec_builtin(t_cmdTable *cmd, int i, char **m_envp, t_lex *lex)
{
	if (!ft_strncmp(cmd->sCmd[i]->args[0], "echo", 4))
		return(miniecho(cmd->sCmd[i]));
	else if (!ft_strncmp(cmd->sCmd[i]->args[0], "cd", 2))
		return(minicd(cmd->sCmd[i], m_envp));
	else if (!ft_strncmp(cmd->sCmd[i]->args[0], "pwd", 3))
		return(minipwd(cmd->sCmd[i]));
	else if (!ft_strncmp(cmd->sCmd[i]->args[0], "env", 3))
		return(minienv(cmd->sCmd[i], m_envp));
	else if (!ft_strncmp(cmd->sCmd[i]->args[0], "unset", 5))
		return(miniunset(cmd->sCmd[i], m_envp));
	else if (!ft_strncmp(cmd->sCmd[i]->args[0], "export", 6))
		return(miniexport(cmd->sCmd[i], m_envp));
	else if (!ft_strncmp(cmd->sCmd[i]->args[0], "exit", 4))
		return(miniexit(cmd, lex, i));
	return (12);
}

void	handle_fd(t_exec *exec, t_cmdTable *cmd)
{
	dup2(exec->fdin, 0);
	close(exec->fdin);
	if (exec->i == cmd->nSimpleCmd - 1)
	{
		if (cmd->outfile && cmd->outtype == '>')
			exec->fdout = open(cmd->outfile, O_WRONLY|O_CREAT, 0666);
		else if (cmd->outfile && cmd->outtype == GGREATER)
			exec->fdout = open(cmd->outfile, O_WRONLY|O_APPEND|O_CREAT, 0666);
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

void	handle_exec(t_exec *exec, t_cmdTable *cmd, char **m_envp, t_lex *lex)
{
	int		i;
	char	*cmdtext;

	i = exec->i;
	if (cmd->sCmd[i]->builtin == 1)
		lex->exit = exec_builtin(cmd, i, m_envp, lex);
	else
	{
		exec->ret = fork();
		if (exec->ret == 0)
		{
			signal(SIGINT, NULL);
			cmdtext = ft_strdup(cmd->sCmd[i]->args[0]);
			lex->exit = execve(cmdtext, cmd->sCmd[i]->args, m_envp);
			if (lex->exit < 0)
				lex->exit = printerror(-127, 0, cmd->sCmd[i]->args[0], 0);	
			exit(0);
		}
	}
}

int		execute_cmd(t_cmdTable *cmd, char **m_envp, t_lex *lex)
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
	while (exec->i < cmd->nSimpleCmd)
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

