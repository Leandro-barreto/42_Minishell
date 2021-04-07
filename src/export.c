/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lborges- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:03:49 by lborges-          #+#    #+#             */
/*   Updated: 2020/01/21 19:04:33 by lborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		split_once(char *source, char sep, char **var, char **value)
{
	int		ret;
	int		i;
	char	*matrix[2];
	int		size;

	matrix[1] = NULL;
	i = 0;
	size = ft_strlen(source);
	ret = 0;
	while (source[i] != sep && source[i])
		i++;
	if (i > 0 && source[i - 1] == '+')
		ret = 1;
	if (i < size)
	{
		matrix[0] = ft_substr(source, 0, i + 1);
		matrix[1] = ft_substr(source, i + 1, size);
	}
	else
		matrix[0] = ft_strdup(source);
	*var = matrix[0];
	*value = matrix[1];
	return (ret);
}

void	exportall(char **m_envp, char **var, char **value)
{
	int		j;

	j = -1;
	while (m_envp[++j])
	{
		split_once(m_envp[j], '=', var, value);
		write(1, "declare -x ", 11);
		ft_putstr_fd(*var, 1);
		write(1, "=\"", 2);
		ft_putstr_fd(*value, 1);
		write(1, "\"\n", 2);
	}
}

int		add_envp(char **m_envp, char *var, char *value, int i)
{
	int	j;

	var = remove_quotes(var);
	value = remove_quotes(value);
	j = 0;
	while (var[j])
	{
		if (ft_isdigit(var[0]) || !(ft_isalnum(var[j]) || var[j] == '_' ||
					var[j] == '=' || var[j] == '+'))
		{
			write(1, "mini: export: not a valid identifier\n", 37);
			return (1);
		}
		j++;
	}
	m_envp[i] = ft_strjoin(var, value);
	i++;
	m_envp[i] = 0;
	return (0);
}

int		exportnorm(char *var, char *value, char **m_envp, int flag)
{
	var = remove_quotes(var);
	value = remove_quotes(value);
	if (ft_strnstr(*m_envp, var, ft_strlen(var)))
	{
		if (!flag)
			*m_envp = ft_strjoin(var, value);
		else
			*m_envp = ft_strjoin(*m_envp, value);
		flag = 2;
	}
	return (flag);
}

int		miniexport(t_simplecmd *scmd, char **m_envp)
{
	char	*var;
	char	*value;
	int		i;
	int		j;
	int		flag;

	i = 0;
	if (!scmd->nargs)
		exportall(m_envp, &var, &value);
	while (++i <= scmd->nargs)
	{
		flag = split_once(scmd->args[i], '=', &var, &value);
		j = -1;
		while (m_envp[++j] && flag < 2)
			flag = exportnorm(var, value, &m_envp[j], flag);
		if (flag != 2)
			flag = add_envp(m_envp, var, value, j);
	}
	return (flag);
}
