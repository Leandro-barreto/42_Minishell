#include "minishell.h"

void	remove_env(t_env *m_envp, int pos)
{
	char	**aux;
	int		i;
	int		j;

	i = 0;
	j = 0;
	aux = ft_calloc(m_envp->size + 1, sizeof(char *));
	while (i < m_envp->size)
	{
		if (i != pos)
			aux[j++] = ft_strdup(m_envp->env[i]);
		i++;
	}
	delete_env(m_envp, 0);
	m_envp->env = aux;
	m_envp->size--;
}

void	delete_env(t_env *m_envp, int flag)
{
	int	i;

	i = 0;
	while (i < m_envp->size)
	{
		free(m_envp->env[i]);
		i++;
	}
	free(m_envp->env);
	if (flag)
		free(m_envp);
}

void	update_env(t_env *m_envp, char *var)
{
	char	**aux;
	int		i;

	if (!var)
		return ;
	i = 0;
	aux = ft_calloc(m_envp->size + 2, sizeof(char *));
	while (i < m_envp->size)
	{
		aux[i] = ft_strdup(m_envp->env[i]);
		i++;
	}
	aux[i] = ft_strdup(var);
	delete_env(m_envp, 0);
	m_envp->env = aux;
	m_envp->size++;
}

t_env	*start_env(char **envp, int aux)
{
	int		i;
	t_env	*m_envp;

	i = 0;
	m_envp = (t_env *)malloc(sizeof(t_env));
	while (envp[i])
		i++;
	m_envp->size = i;
	m_envp->env = ft_calloc(i + 1 + aux, sizeof(char *));
	i = 0;
	while (envp[i])
	{
		m_envp->env[i] = ft_strdup(envp[i]);
		i++;
	}
	if (aux)
		delete_env(m_envp, 0);
	return (m_envp);
}
