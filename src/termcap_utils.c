#include "minishell.h"

void	deleteline(int size, int col)
{
	if (size > 0)
	{
		if (((size + 7) % (col - 1) == 0))
		{
			tputs(tgetstr("up", NULL), 1, &ft_putchar);
			tputs(tgoto(tgetstr("ch", NULL), 0, col), 0, &ft_putchar);
			tputs(tgetstr("dc", NULL), 1, &ft_putchar);
		}
		tputs(tgetstr("le", NULL), 1, &ft_putchar);
		tputs(tgetstr("dc", NULL), 1, &ft_putchar);
		g_global.line[size - 1] = '\0';
	}
}

void	dow_arrow(char **history, int *present)
{
	int	last;

	last = write_cmd(NULL, 0, 1);
	if (*present < last - 1)
	{
		*present += 1;
		while (g_global.line[0])
			deleteline(ft_strlen(g_global.line), tgetnum("col"));
		ft_putstr_fd(history[*present], 1);
		free(g_global.line);
		g_global.line = ft_strdup(history[*present]);
	}
	else if (*present == last - 1 && g_global.line)
	{
		while (g_global.line[0])
			deleteline(ft_strlen(g_global.line), tgetnum("col"));
		if (g_global.tmpline)
		{
			ft_putstr_fd(g_global.tmpline, 1);
			free(g_global.line);
			g_global.line = ft_strdup(g_global.tmpline);
		}
		*present = last;
	}
}

void	up_arrow(char **history, int *present)
{
	int	last;

	last = write_cmd(NULL, 0, 1);
	if (*present == last && g_global.line[0])
		g_global.tmpline = ft_strdup(g_global.line);
	if (*present > 0)
	{	
		*present -= 1;
		while (g_global.line && g_global.line[0])
			deleteline(ft_strlen(g_global.line), tgetnum("col"));
		ft_putstr_fd(history[*present], 1);
		free(g_global.line);
		g_global.line = ft_strdup(history[*present]);
	}
}

int	handle_event(char *buf, char **history, int *present)
{
	int	size;
	int	col;

	col = tgetnum("col");
	size = ft_strlen(g_global.line);
	if (buf[0] == LF)
		return (write_cmd(history, size, 0));
	else if (buf[0] == DEL)
		deleteline(size, col);
	else if (buf[0] == ESC && buf[1] == SQ_BR && buf[2] == UP)
		up_arrow(history, present);
	else if (buf[0] == ESC && buf[1] == SQ_BR && buf[2] == DOWN)
		dow_arrow(history, present);
	else
		add_char(buf[0], size);
	return (0);
}
