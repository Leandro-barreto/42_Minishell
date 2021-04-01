/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lborges- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:03:49 by lborges-          #+#    #+#             */
/*   Updated: 2020/01/21 19:04:33 by lborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_isin(const char *haystack, const char *needle)
{
	int	i;
	int	j;

	if (!*needle)
		return (0);
	i = ft_strlen(haystack) - 1;
	j = ft_strlen(needle) - 1;
	while (haystack[i] == needle[j] && j >= 0)
	{
		i--;
		j--;
	}
	if (j == -1)
		return (1);
	return (0);
}

int			ispath(char *text)
{
	if (text[0] == '/' || ft_strnstr(text, "~/", 2) ||
			ft_strnstr(text, "./", 2) || ft_strnstr(text, "../", 3))
		return (1);
	return (0);
}

int			workingfile(char *file)
{
	int		fd;
	int		ret;

	ret = 1;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ret--;
	close(fd);
	return (ret);
}

char		*ft_returnenvvar(char *name, char **m_envp)
{
	int		x;

	x = -1;
	if (!name)
		return ("");
	name = ft_strjoin(name, "=");
	while (m_envp[++x])
		if (ft_strnstr(m_envp[x], name, ft_strlen(name)))
			return (&m_envp[x][ft_strlen(name)]);
	return ("");
}

char		*checkpathvar(char *var, char *cmd, char **m_envp)
{
	char	*aux;
	char	*aux2;
	int		i[2];

	cmd = ft_strjoin("/", cmd);
	aux = ft_returnenvvar(var, m_envp);
	i[0] = 0;
	i[1] = 0;
	while (aux[i[0]])
	{
		if (aux[i[0]++] == ':')
		{
			aux2 = (char *)malloc(i[0] - i[1]);
			ft_strlcpy(aux2, &aux[i[1]], i[0] - i[1]);
			aux2 = ft_strjoin(aux2, cmd);
			if (workingfile(aux2))
				return (aux2);
			i[1] = i[0];
		}
	}
	aux2 = (char *)malloc(i[0] - i[1] + 1);
	ft_strlcpy(aux2, &aux[i[1]], i[0] - i[1] + 1);
	aux2 = ft_strjoin(aux2, cmd);
	if (workingfile(aux2))
		return (aux2);
	return (cmd);
}
