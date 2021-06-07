#include "minishell.h"

int	split_once(char *source, char sep, char **var, char **value)
{
	int		ret;
	int		i;
	char	*matrix[2];
	int		size;

	matrix[0] = NULL;
	matrix[1] = NULL;
	i = 0;
	size = ft_strlen(source);
	ret = 0;
	while (source[i] && source[i] != sep)
		i++;
	if (i > 0 && source[i - 1] == '+')
		ret = 1;
	if (i < size)
	{
		matrix[0] = ft_substr(source, 0, i + 1);
		matrix[1] = ft_substr(source, i + 1, size);
	}
	else
		ret = 0;
	*var = matrix[0];
	*value = matrix[1];
	return (ret);
}

void	exportall(t_env *m_envp, char **var, char **value)
{
	int		j;

	j = -1;
	while (m_envp->env[++j])
	{
		split_once(m_envp->env[j], '=', var, value);
		write(1, "declare -x ", 11);
		ft_putstr_fd(*var, 1);
		write(1, "=\"", 2);
		ft_putstr_fd(*value, 1);
		write(1, "\"\n", 2);
		free(*var);
		free(*value);
	}
}

int	add_envp(t_env *m_envp, char *var, char *value)
{
	int		j;
	char	*aux;

	j = 0;
	if (!var || !value)
		return (0);
	while (var[j])
	{
		if (ft_isdigit(var[0]) || !(ft_isalnum(var[j]) || var[j] == '_'
				|| var[j] == '=' || var[j] == '+'))
		{
			printerror(-1, 3, NULL, 1);
			return (-1);
		}
		j++;
	}
	aux = ft_strjoin(var, value);
	update_env(m_envp, aux);
	free(aux);
	return (0);
}

int	exportnorm(char *var, char *value, char **m_envp, int flag)
{
	char	*aux;
	char	*aux2;

	aux = NULL;
	if (!var || !value)
		return (flag);
	aux2 = ft_strdup(var);
	if (flag)
		aux2[ft_strlen(aux2) - 2] = 0;
	if (ft_strnstr(*m_envp, aux2, ft_strlen(aux2)))
	{
		if (!flag)
			aux = ft_strjoin(var, value);
		else
			aux = ft_strjoin(*m_envp, value);
		flag = 2;
	}
	if (aux)
	{
		free (*m_envp);
		*m_envp = aux;
	}
	free(aux2);
	return (flag);
}

int	miniexport(t_simpleCmd *scmd, t_env *m_envp)
{
	char	*var;
	char	*value;
	int		i;
	int		j;
	int		flag;

	i = 0;
	g_global.exit = 0;
	if (!scmd->nArgs)
		exportall(m_envp, &var, &value);
	while (++i <= scmd->nArgs)
	{
		flag = split_once(scmd->args[i], '=', &var, &value);
		j = -1;
		while (m_envp->env[++j] && flag < 2)
			flag = exportnorm(var, value, &(m_envp->env[j]), flag);
		if (flag != 2)
			flag = add_envp(m_envp, var, value);
		if (var)
			free(var);
		if (value)
			free(value);
	}
	return (flag);
}
