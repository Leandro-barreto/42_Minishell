#include "minishell.h"

int		exec_builtin(t_simpleCmd *scmd, char **m_envp, t_lex *lex)
{
	if (!ft_strncmp(scmd->args[0], "echo", 4))
		return(miniecho(scmd));
	else if (!ft_strncmp(scmd->args[0], "cd", 2))
		return(minicd(scmd, m_envp));
	else if (!ft_strncmp(scmd->args[0], "pwd", 3))
		return(minipwd(scmd));
	else if (!ft_strncmp(scmd->args[0], "env", 3))
		return(minienv(scmd, m_envp));
	else if (!ft_strncmp(scmd->args[0], "unset", 5))
		return(miniunset(scmd, m_envp));
	else if (!ft_strncmp(scmd->args[0], "export", 6))
		return(miniexport(scmd, m_envp));
	else if (!ft_strncmp(scmd->args[0], "exit", 4))
		return(miniexit(scmd, lex));
	return (12);
}

void	handle_fd(t_exec *exec, t_cmdTable cmd, t_lex *lex)
{
	dup2(exec->fdin, 0);
	close(exec->fdin);
	if (exec->i == cmd.nSimpleCmd - 1)
	{
		if (cmd.outfile && cmd.outtype == '>')
			exec->fdout = open(cmd.outfile, O_WRONLY|O_CREAT, 0666);
		else if (cmd.outfile && cmd.outtype == GGREATER)
			exec->fdout = open(cmd.outfile, O_WRONLY|O_APPEND|O_CREAT, 0666);
		else
			exec->fdout = dup(tmpout);
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

void	handle_exec(t_exec *exec, t_cmdTable cmd, char **m_envp, t_lex *lex)
{
	if (cmd.sCmd[i]->builtin == 1)
		lex->exit = exec_builtin(cmd.sCmd[i], m_envp, lex);
	else
	{
		exec->ret = fork();
		if (exec->ret == 0)
		{
			
			lex->exit = execve(cmd.sCmd[i]->args[0], cmd.sCmd[i]->args, m_envp);
			if (lex->exit < 0)
				lex->exit = printerror(-127, 0, cmd.sCmd[i]->args[0], 0);	
			exit(0);
		}
	}
}

int		execute_cmd(t_cmdTable cmd, char **m_envp, t_lex *lex)
{
	t_exec	*exec;

	exec = (t_exec *)malloc(sizeof(t_exec));
	exec = {0};
	exec->tmpin = dup(0);
	exec->tmpout = dup(1);
	exec->fdin = dup(0);
	if (cmd.infile)
		exec->fdin = open(cmd.infile, O_RDONLY);
	exec->i = 0;
	while (exec->i < cmd.nSimpleCmd)
	{
		handle_fd(exec, cmd, lex);
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

