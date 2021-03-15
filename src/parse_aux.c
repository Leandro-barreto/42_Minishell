#include "minishell.h"

int		checkminicmd(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", 2) || !ft_strncmp(cmd, "export", 6) ||                           
		!ft_strncmp(cmd, "unset", 5) ||  !ft_strncmp(cmd, "pwd", 3) ||
		!ft_strncmp(cmd, "env", 3) || !ft_strncmp(cmd, "exit", 4) ||
		!ft_strncmp(cmd, "echo", 4))                                             
	{
		return (1);
	}
	return (0);
}
