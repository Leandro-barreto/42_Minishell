#include "minishell.h"

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

void	add_char(char c, int size)
{
	char	*aux;

	if (!ft_isprint(c))
		return ;
	aux = (char *)malloc(size + 2);
	ft_strcpy(aux, g_global.line);
	aux[size] = c;
	aux[size + 1] = 0;
	free(g_global.line);
	g_global.line = aux;
	write(1, &c, 1);
}

void	dellines(int size)
{
	if (!g_global.line)
		return ;
	while (--size > 0)
		g_global.line[size] = 0;
	g_global.line[0] = 0;
	free(g_global.line);
	g_global.line = 0;
	if (!g_global.tmpline)
		return ;
	size = ft_strlen(g_global.tmpline);
	if (size)
	{
		while (--size > 0)
			g_global.tmpline[size] = 0;
		g_global.tmpline[0] = 0;
	}
	free(g_global.tmpline);
	g_global.tmpline = 0;
}

int	write_cmd(char **history, int size, int flag)
{
	static int	last;
	int			n;

	if (flag)
		return (last);
	if (size)
	{
		n = ft_strlen(g_global.line);
		if ((!last) || (last > 0
				&& ft_memcmp(history[last - 1], g_global.line, 0)))
		{
			history[last] = (char *)malloc((size + 1) * sizeof(char));
			ft_strcpy(history[last], g_global.line);
			last++;
		}
	}
	write(1, "\n", 1);
	return (-1);
}
