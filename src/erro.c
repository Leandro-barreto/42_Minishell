#include "minishell.h"

int		printerror(int err, int func, char *auxstr, int fd)
{
	char *msg;

	msg = NULL;
	if (err == -127 && func == 0)
		msg = ft_strjoin(&auxstr[1], ": command not found\n");
	else if (err == -2 && func == 0)
		msg = ft_strjoin("bash: syntax error near unexpected token `", auxstr);
	else if (err == -1 && func == 2)
	{
		msg = ft_strjoin("mini: cd: ", auxstr);
		msg = ft_strjoin(msg, ": No such file or directory");
	}
	ft_putstr_fd(msg, fd);
	return (-err);
}
