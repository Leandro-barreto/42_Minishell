#include "minishell.h"

int		minicd(t_simpleCmd *scmd, char **m_envp)
{
	int	i;
	int	ret;
	char buf[255];

	if (scmd->nArgs > 1)
		printf("minishell: cd: Pra q tudo isso?!\n");
	else
	{
		if (scmd->nArgs == 0)
			ret = chdir(ft_returnenvvar("HOME", m_envp)); 
		else
			ret = chdir(scmd->args[1]);
		if (ret < 0)
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

int		miniexit(t_simpleCmd *scmd, t_lex *lex)
{
	int	i;
	int	exitvar;

	i = -1;
	exitvar = 0;
	if (scmd->nArgs > 0 && scmd->args[1][0] == '-')
	{
		printf("mini: exit: Invalid option %s\n", scmd->args[1]);
		exitvar = 1;
	}
	else if (scmd->nArgs > 0)
		while (scmd->args[1][++i])
        	if (scmd->args[1][i] < '0' || scmd->args[1][i] > '9')
			{
            	printf("minishell: exit: Illegal number: %s\n", scmd->args[1]);
				exitvar = 2;
			}
	if (exitvar)
		exit(lex->exit = exitvar);
	if (scmd->nArgs > 0)
		exit(lex->exit = ft_atoi(scmd->args[1]));
	else
		exit(0);
    return (0);
}

int		minipwd(t_simpleCmd *scmd)
{
	char buf[255];

	if (scmd->nArgs > 0 && scmd->args[1][0] == '-')
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

int		miniecho(t_simpleCmd *scmd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while ((i <= scmd->nArgs) && !(ft_strncmp(scmd->args[i], "-n", 2)))
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
	fflush(stdout);
	return (0);
}
