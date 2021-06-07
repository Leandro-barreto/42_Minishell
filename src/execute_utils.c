#include "minishell.h"

char	*handleaux(char *source, int size, char c)
{
	char	*dest;
	int		i;
	int		j;

	dest = (char *)malloc(sizeof(char) * size);
	i = 1;
	j = 0;
	while (i < size && source[i])
	{
		if (source[i] == c && source[i - 1] != '\\')
			i++;
		if (source[i] == '\\' && source[i + 1] == '\"')
			i++;
		dest[j] = source[i];
		j++;
		i++;
	}
	while (j < size)
		dest[j++] = 0;
	return (dest);
}

t_simpleCmd	*handlequotes(t_simpleCmd *scmd)
{
	int		i;
	int		size;
	char	*dest;

	i = -1;
	while (++i <= scmd->nArgs)
	{
		size = ft_strlen(scmd->args[i]);
		if (size > 1 && (scmd->args[i][0] == '\"' || scmd->args[i][0] == '\''))
		{
			dest = handleaux(scmd->args[i], size, scmd->args[i][0]);
			free(scmd->args[i]);
			scmd->args[i] = dest;
		}
	}
	return (scmd);
}
