#include "minishell.h"

//char	**sortenv(char **str, int count)
//{
//	int		i;
//	int		j;
//	char	*temp;
//
//	while (i <= count)
//	{
//		j = i + 1;
//		while (j <= count)
//		{
//			if (ft_memcmp(str[i], str[j]) > 0)
//			{
//				ft_memcpy(temp, str[i]);
//				ft_memcpy(str[i], str[j]);
//				ft_memcpy(str[j], temp);
//			}
//			j++;
//		}
//		i++;
//	}
//	return (str);
//}

void	split_once(char *source, char sep, char **var, char **value)
{
	int		i;
	char	*matrix[2];
	int		size;

	matrix[1] = NULL;
	i= 0;
	size = ft_strlen(source);
	while (source[i] != sep && source[i])
		i++;
	if (i < size)
	{
		matrix[0] = ft_substr(source, 0, i + 1);
		matrix[1] = ft_substr(source, i + 1, size); 
	}
	else
		matrix[0] = ft_strdup(source);
	*var = matrix[0];
	*value = matrix[1];
}

void	exportall(char **m_envp, char **var, char **value)
{
	//char	**sorted;
	int		j;

	//sorted = sortenv(n_envp);
	j = -1;
	while(m_envp[++j])
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

	j = 0;
	while (var[j])
	{
		if (!(ft_isalnum(var[j]) || var[j] == '_' || var[j] == '='))
		{
			printf("mini: export: not a valid identifier");
			fflush(stdout);
			return (1);
		}
		j++;
	}
	m_envp[i] = ft_strjoin(var, value);
	i++;
	m_envp[i] = 0;
	return (0);
}

int		miniexport(t_simpleCmd *scmd, char **m_envp)
{
	char	*var;
	char	*value;
	int		i;
	int		j;
	int		flag;

	i = 0;
	if (!scmd->nArgs)
		exportall(m_envp, &var, &value);
	flag = 0;
	while (++i <= scmd->nArgs)
	{
		split_once(scmd->args[i], '=', &var, &value);
		j = -1;
		while(m_envp[++j])
		{
			if (ft_strnstr(m_envp[j], var, ft_strlen(var)))
			{
				m_envp[j] = ft_strjoin(var, value);
				flag = 1;
				break ;
			}
		}
		if (!flag)
			return (add_envp(m_envp, var, value, j));
	}
	return (0);
}
