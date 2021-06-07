#include "minishell.h"

int	printerror(int err, int func, char *auxstr, int fd)
{
	char	*msg;

	msg = NULL;
	if (err == -127 && func == 0)
		msg = ft_strjoin(g_global.line, ": command not found\n");
	else if (err == -2 && func == 0)
		msg = ft_strjoin("mini: syntax error near token `", auxstr);
	else if ((err == -SQUOTE || err == -DQUOTE) && func == 0)
		msg = ft_strjoin("Minishell doesn't handle multilines", "\n");
	else if (err == -PIPE && func == 0)
		msg = ft_strjoin(auxstr, "\n");
	else if (err == -1 && func == 2)
	{
		msg = ft_strjoin("mini: cd: ", auxstr);
		msg = ft_strjoin(msg, ": No such file or directory");
	}
	else if (err == -1 && func == 3)
		msg = ft_strdup("mini: export: not a valid identifier\n");
	ft_putstr_fd(msg, fd);
	free(msg);
	g_global.exit = -err;
	return (-err);
}
