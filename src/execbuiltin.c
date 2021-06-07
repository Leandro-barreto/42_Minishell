#include "minishell.h"

int	minienv(t_simpleCmd *scmd, t_env *m_envp)
{
	int	i;

	i = -1;
	if (scmd->nArgs > 0)
	{
		ft_putstr_fd("minishell: env: Wrong Args\n", 1);
		return (g_global.exit = 127);
	}
	else
	{
		while (m_envp->env[++i])
		{
			ft_putstr_fd(m_envp->env[i], 1);
			ft_putstr_fd("\n", 1);
		}
	}
	return (g_global.exit = 0);
}

int	miniexit(t_cmdTable *cmd, t_lex *lex, int i, int n)
{
	int	j;

	j = -1;
	if (cmd[n].sCmd[i]->nArgs > 0 && cmd[n].sCmd[i]->args[1][0] == '-')
	{
		printf("mini: exit: Invalid option %s\n", cmd[n].sCmd[i]->args[1]);
		ft_exit(lex, cmd, 1);
	}
	else if (cmd[n].sCmd[i]->nArgs > 0)
	{
		while (cmd[n].sCmd[i]->args[1][++j])
		{
			if (cmd[n].sCmd[i]->args[1][j] < '0'
			|| cmd[n].sCmd[i]->args[1][j] > '9')
			{
				printf("mini: exit: Illegal: %s\n", cmd[n].sCmd[i]->args[1]);
				ft_exit(lex, cmd, 2);
			}
		}
	}
	if (cmd[n].sCmd[i]->nArgs > 0)
		ft_exit(lex, cmd, ft_atoi(cmd[n].sCmd[i]->args[1]));
	else
		ft_exit(lex, cmd, 0);
	return (0);
}

int	minipwd(t_simpleCmd *scmd)
{
	char	buf[255];

	if (scmd->nArgs > 0 && scmd->args[1][0] == '-')
	{
		printf("mini: pwd: Invalid option %s\n", scmd->args[1]);
		return (g_global.exit = 1);
	}
	else
	{
		getcwd(buf, 255);
		if (*buf)
			printf("%s\n", buf);
		else
		{
			ft_putstr_fd("mini: pwd: error getting working dir", 1);
			return (g_global.exit = 2);
		}
	}
	return (g_global.exit = 0);
}
