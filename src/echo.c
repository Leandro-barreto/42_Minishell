#include "minishell.h"

void	writeecho(char *text)
{
	int	i;
	int size;

	size = ft_strlen(text);
	i = 0;
	if ((size > 1) && ((text[0] == '\'' && text[size - 1] == '\'') ||
		(text[0] == '\"' && text[size - 1] == '\"'))) 
	{
		i++;
		size--;
	}
	while(i < size)
	{
		if (text[i] != '\\')
			write(1, &text[i], 1);	
		if (text[i] == '\\' && text[0] == '\'')
			write(1, &text[i], 1);	
		if (text[i] == '\\' && text[0] == '\"' && text[i + 1] != '$'
				&& text[i + 1] != '\"' && text[i + 1] != '\'')
			write(1, &text[i], 1);	
		i++;
	}
}	

int		miniecho(t_simpleCmd *scmd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while ((i <= scmd->nArgs) && !(ft_strncmp(scmd->args[i], "-n", 2)))
	{
		i++;
		flag++;
	}
	printf("Nargs: %i\n", scmd->nArgs);
	while (i <= scmd->nArgs)
	{
		writeecho(scmd->args[i]);
		if (i < scmd->nArgs)
			write(1, " ", 1);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
	return (0);
}
