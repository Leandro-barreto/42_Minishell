#include "minishell.h"

int	ispath(char *text)
{
	int	flag;

	flag = 0;
	if (text[0] == '/' || ft_strnstr(text, "~/", 2)
		|| ft_strnstr(text, "./", 2) || ft_strnstr(text, "../", 3))
		flag = 1;
	if (flag)
		return (flag + workingfile(text));
	return (0);
}

int	workingfile(char *file)
{
	int			fd;
	struct stat	buffer;

	fd = stat(file, &buffer);
	if (fd < 0)
		return (0);
	errno = 0;
	return (1);
}

char	*ft_returnenvvar(char *name, t_env *m_envp)
{
	int	x;
	int	y;

	x = -1;
	if (!name)
		return ("");
	name = ft_strjoin(name, "=");
	while (m_envp->env[++x])
	{
		if (ft_strnstr(m_envp->env[x], name, ft_strlen(name)))
		{
			y = ft_strlen(name);
			free(name);
			return (&m_envp->env[x][y]);
		}
	}
	if (name)
		free(name);
	return ("");
}

char	*checkpathvar2(char *aux, int *i, char *cmdnew)
{
	char	*aux2;
	char	*aux3;

	while (aux[i[0]])
	{
		if (aux[i[0]++] == ':')
		{
			aux2 = (char *)malloc(i[0] - i[1]);
			ft_strlcpy(aux2, &aux[i[1]], i[0] - i[1]);
			aux3 = ft_strjoin(aux2, cmdnew);
			free(aux2);
			if (workingfile(aux3))
			{
				free(cmdnew);
				return (aux3);
			}
			i[1] = i[0];
			free(aux3);
		}
	}
	aux3 = NULL;
	return (aux3);
}

char	*checkpathvar(char *var, char *cmd, t_env *m_envp)
{
	char	*aux;
	char	*aux2;
	char	*aux3;
	char	*cmdnew;
	int		i[2];

	cmdnew = ft_strjoin("/", cmd);
	aux = ft_returnenvvar(var, m_envp);
	i[0] = 0;
	i[1] = 0;
	aux3 = checkpathvar2(aux, i, cmdnew);
	if (aux3)
		return (aux3);
	aux2 = (char *)malloc(i[0] - i[1] + 1);
	ft_strlcpy(aux2, &aux[i[1]], i[0] - i[1] + 1);
	aux = ft_strjoin(aux2, cmdnew);
	free(aux2);
	if (workingfile(aux))
		return (aux);
	free(aux);
	free(cmdnew);
	return (NULL);
}
