#include "minishell.h"

int		minicd(t_simpleCmd *scmd, char **m_envp)
{
	int		i;
	int		ret;
	char	buf[255];
	DIR		*dir;

	write(1, "cd\n", 3);
	dir = NULL;
	if (scmd->nArgs > 1)
		printf("minishell: cd: Pra q tudo isso?!\n");
	else
	{
		if (scmd->nArgs == 0)
			ret = chdir(ft_returnenvvar("HOME", m_envp)); 
		else
		{
			dir = opendir(scmd->args[1]);
			if (dir)
				ret = chdir(scmd->args[1]);
		}
		if (!dir || ret < 0)
			printf("Deu ruim");
	}
	i = -1;
	getcwd(buf, 255); 	
	while(m_envp[++i])
		if (ft_strnstr(m_envp[i], "PWD", 3))
		{
			m_envp[i] = ft_strjoin("PWD=", buf);
			break ;
		}
	fflush(stdout);
	return (ret);
}

int		minienv(t_simpleCmd *scmd, char **m_envp)
{
	int	i;

	i = -1;
	if (scmd->nArgs > 0)
	{
		printf("minishell: env: Pra q tudo isso?!\n");
		return (127);
	}
	else
	{
		while(m_envp[++i])
		{
			printf("%s\n", m_envp[i]);
			fflush(stdout);
		}
	}
	return (0);
}

int		miniexit(t_cmdTable *cmd, t_lex *lex, int i)
{
	int	j;
	int	exitvar;

	j = -1;
	exitvar = 0;
	if (cmd->sCmd[i]->nArgs > 0 && cmd->sCmd[i]->args[1][0] == '-')
	{
		printf("mini: exit: Invalid option %s\n", cmd->sCmd[i]->args[1]);
		exitvar = 1;
	}
	else if (cmd->sCmd[i]->nArgs > 0)
		while (cmd->sCmd[i]->args[1][++j])
        	if (cmd->sCmd[i]->args[1][j] < '0' || cmd->sCmd[i]->args[1][j] > '9')
			{
            	printf("minishell: exit: Illegal number: %s\n", cmd->sCmd[i]->args[1]);
				exitvar = 2;
			}
	if (exitvar)
		exit(lex->exit = exitvar);
	if (cmd->sCmd[i]->nArgs > 0)
	{
		j = ft_atoi(cmd->sCmd[i]->args[1]);
		delete_table(cmd, lex);
		exit(lex->exit = j);
	}
	else
	{
		delete_table(cmd, lex);
		exit(0);
	}
	return (0);
}

int		minipwd(t_simpleCmd *scmd)
{
	char	buf[255];
//	DIR		*dir;

	write(1, "wd\n", 3);
	if (scmd->nArgs > 0 && scmd->args[1][0] == '-')
	{
		printf("mini: pwd: Invalid option %s\n", scmd->args[1]);
		return (1);
	}
	else
	{
		//dir = opendir();
		//if (dir)
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

