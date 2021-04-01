/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lborges- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:03:49 by lborges-          #+#    #+#             */
/*   Updated: 2020/01/21 19:04:33 by lborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_envvar(char **m_envp, char *var)
{
	int	j;

	j = -1;
	while (m_envp[++j])
	{
		if (ft_strnstr(m_envp[j], var, ft_strlen(var)))
		{
			if (!m_envp[j + 1])
				m_envp[j] = 0;
			else
			{
				while (m_envp[j])
				{
					m_envp[j] = m_envp[j + 1];
					j++;
				}
				break ;
			}
		}
	}
}

int		miniunset(t_simpleCmd *scmd, char **m_envp)
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
				printf("mini: unset: %s: ", scmd->args[i]);
				printf("not a valid identifier\n");
				fflush(stdout);
				return (1);
			}
		}
		var = ft_strjoin(scmd->args[i], "=");
		delete_envvar(m_envp, var);
	}
	return (0);
}
