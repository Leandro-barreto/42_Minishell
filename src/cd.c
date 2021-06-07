#include "minishell.h"

void	updtepwd(t_env *m_envp)
{
	int			i;
	char		buf[255];
	static int	aux;

	i = -1;
	getcwd(buf, 255);
	while (m_envp->env[++i])
	{
		if (ft_strnstr(m_envp->env[i], "PWD", 3))
		{
			free(m_envp->env[i]);
			m_envp->env[i] = ft_strjoin("PWD=", buf);
			break ;
		}
	}
	aux = 1;
}

char	*handlequotecd(t_simpleCmd *scmd)
{
	char	*aux;
	int		i;
	int		len;
	int		j;

	i = 1;
	j = 0;
	len = ft_strlen(scmd->args[1]);
	if (scmd->args[1][0] == '\"' || scmd->args[1][0] == '\'' )
	{
		aux = malloc(sizeof(char) * (len - 2 + 1));
		while (i < len - 1)
			aux[j++] = scmd->args[1][i++];
		aux[j] = 0;
		return (aux);
	}
	return (ft_strdup(scmd->args[1]));
}

int	minicdnorm(t_simpleCmd *scmd)
{
	DIR		*dir;
	char	*aux;
	int		ret;

	dir = NULL;
	aux = handlequotecd(scmd);
	dir = opendir(aux);
	if (dir)
		ret = chdir(aux);
	else
		ret = -1;
	free(aux);
	free(dir);
	return (ret);
}

int	minicd(t_simpleCmd *scmd, t_env *m_envp)
{
	int		ret;

	ret = -1;
	if (scmd->nArgs > 1)
		ft_putstr_fd("minishell: cd: wrong args\n", 1);
	else
	{
		if (scmd->nArgs == 0)
			ret = chdir(ft_returnenvvar("HOME", m_envp));
		else
			ret = minicdnorm(scmd);
		if (ret < 0)
			ft_putstr_fd("Wrong dir\n", 1);
	}
	updtepwd(m_envp);
	return (g_global.exit = -ret);
}
