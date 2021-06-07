#include "minishell.h"

int	checkminicmd(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", 3) || !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "unset", 6) || !ft_strncmp(cmd, "pwd", 4)
		|| !ft_strncmp(cmd, "env", 4) || !ft_strncmp(cmd, "exit", 5)
		|| !ft_strncmp(cmd, "echo", 5))
	{
		return (1);
	}
	return (0);
}

int	parse_files(t_tokens *tok, t_cmdTable *cmd, int type)
{
	int	fd;

	if (type == '<')
		cmd->infile = ft_strdup(tok->data);
	else
	{
		cmd->outfile = ft_strdup(tok->data);
		cmd->outtype = type;
		if (type == '>')
			fd = open(tok->data, O_WRONLY | O_CREAT, 0666);
		else
			fd = open(tok->data, O_WRONLY | O_APPEND | O_CREAT, 0666);
		close(fd);
	}
	return (0);
}

int	insertargs(t_tokens *tok, t_cmdTable *cmd, int j)
{
	int	i;

	i = cmd->sCmd[j]->nArgs;
	if (i >= cmd->sCmd[j]->nAvalArg)
		return (-1);
	cmd->sCmd[j]->args[++i] = ft_strdup(tok->data);
	cmd->sCmd[j]->nArgs++;
	return (0);
}
