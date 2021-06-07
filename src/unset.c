#include "minishell.h"

void	delete_envvar(t_env *m_envp, char *var)
{
	int	j;

	j = -1;
	while (m_envp->env[++j])
	{
		if (ft_strnstr(m_envp->env[j], var, ft_strlen(var)))
		{
			remove_env(m_envp, j);
			break ;
		}
	}
}

int	miniunset(t_simpleCmd *scmd, t_env *m_envp)
{
	char	*var;
	int		i;
	int		j;
	char	c;

	i = 0;
	while (++i <= scmd->nArgs)
	{
		j = -1;
		while (scmd->args[i][++j])
		{
			c = scmd->args[i][j];
			if (!(ft_isalnum(c) || c == '_'))
			{
				ft_putstr_fd("mini: unset:", 1);
				ft_putstr_fd(scmd->args[i], 1);
				ft_putstr_fd(" not a valid identifier\n", 1);
				return (g_global.exit = 1);
			}
		}
		var = ft_strjoin(scmd->args[i], "=");
		delete_envvar(m_envp, var);
		free(var);
	}
	return (g_global.exit = 0);
}
