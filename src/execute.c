#include "minishell.h"

void	minicd(t_simpleCmd *scmd)
{
	int	i;
	char buf[255];

	if (scmd->nArgs > 1)
		printf("minishell: cd: Pra q tudo isso?!\n");
	else
	{
		if (scmd->nArgs == 0)
			i = chdir(ft_returnenvvar("HOME")); 
		else
			i = chdir(scmd->args[1]);
		if (i < 0)
			printf("Deu ruim");
		printf("%i\n", i);
	}
	i = -1;
	getcwd(buf, 255); 	
	while(g_envp[++i])
		if (ft_strnstr(g_envp[i], "PWD", 3))
		{
			write(1, "Aqui\n", 5);
			g_envp[i] = ft_strjoin("PWD=", buf);
			printf("%s\n", g_envp[i]);
			break ;
		}
}

void	minienv(t_simpleCmd *scmd)
{
	int	i;

	i = -1;
	if (scmd->nArgs > 0)
		printf("minishell: env: Pra q tudo isso?!\n");
	else
	{
		while(g_envp[++i])
		{
			printf("%s\n", g_envp[i]);
			fflush(stdout);
		}
	}
}

void	minipwd(t_simpleCmd *scmd)
{
	char buf[255];

	if (scmd->nArgs > 0 && scmd->args[1][0] == '-')
		printf("minishell: pwd: Invalid option %s\n", scmd->args[1]);
	else
		printf("%s\n", getcwd(buf, 255)); 	
}

void	miniecho(t_simpleCmd *scmd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if ((scmd->nArgs > 0) && !(ft_strncmp(scmd->args[i], "-n", 2)))
	{
		i++;
		flag++;
	}
	while (i < scmd->nArgs)
		printf("%s ", scmd->args[i++]);
	if (i == scmd->nArgs)
		printf("%s", scmd->args[i]);
	if (!flag)
		printf("\n");
}

void	exec_builtin(t_simpleCmd *scmd)
{
	if (!ft_strncmp(scmd->args[0], "echo", 4))
		miniecho(scmd);
	else if (!ft_strncmp(scmd->args[0], "cd", 2))
		minicd(scmd);
	else if (!ft_strncmp(scmd->args[0], "pwd", 3))
		minipwd(scmd);
	else if (!ft_strncmp(scmd->args[0], "env", 3))
		minienv(scmd);
//	else if (!ft_strncmp(scmd->args[0], "unset", 5))
//		miniunset(scmd);
//	else if (!ft_strncmp(scmd->args[0], "export", 6))
//		miniexport(scmd);
}

void	execute_cmd(t_cmdTable *cmd)
{
	int	tmpin;
	int	tmpout;
	int	fdin;
	int	fdout;
	int	ret;
	int	i;
	int	fdpipe[2];

	write(1, "Execute\n", 8);
	tmpin = dup(0);
	tmpout = dup(1);
	fdin = dup(0);
	if (cmd->infile)
		fdin = open(cmd->infile, O_RDONLY);
	i = 0;
	while(i < cmd->nAvalSimpleCmd)
	{
		printf("Exec: %s\n Aval: %i\n", cmd->sCmd[i]->args[0], cmd->nAvalSimpleCmd);
		fflush(stdout);
		dup2(fdin, 0);
		close(fdin);
		if (i == cmd->nAvalSimpleCmd - 1)
		{
			if (cmd->outfile && cmd->outtype == '>')
				fdout = open(cmd->outfile, O_WRONLY|O_CREAT, 0666);
			else if (cmd->outfile && cmd->outtype == GGREATER)
				fdout = open(cmd->outfile, O_WRONLY|O_APPEND|O_CREAT, 0666);
			else
				fdout = dup(tmpout);
		}
		else 
		{
			pipe(fdpipe);
			fdout = fdpipe[1];	
			fdin = fdpipe[0];	
		}
		dup2(fdout, 1);
		close(fdout);
		if (cmd->sCmd[i]->builtin == 1)
			exec_builtin(cmd->sCmd[i]);
		else
		{
			ret = fork();
			if (ret == 0)
			{
				execve(cmd->sCmd[i]->args[0], cmd->sCmd[i]->args, g_envp);
				exit(0);
			}
		}
		i++;
	}
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	waitpid(ret, NULL, 0);
}

