#include "minishell.h"

char	*replaceword(char *phrase, char *old, char *new)
{
	char	*rep;
	int		size;
	int		i;
	int		j;

	if (!old)
		return (phrase);
	size = ft_strlen(phrase) + ft_strlen(new) - ft_strlen(old); 
	rep = (char *)malloc(size + 1);
	i = -1;
	while (phrase[++i] != '$')
		rep[i] = phrase[i];
	j = -1;
	while (new[++j])
		rep[i + j] = new[j];
	size = ft_strlen(old); 
	while (phrase[i + size + 1])
	{
 		rep[i + j] = phrase[i + size + 1];
		i++;
	}
	rep[i + j] = '\0';
	return (rep);
}

void	checkdollar(t_tokens *tok, t_lex *lex, char **m_envp)
{
	char	*var;
	char	*new;
	int		i;
	int		j;

	i = -1;
	while (tok->data[++i] && tok->quote != '\'')
	{	
		var = NULL;
		if (tok->data[i] == '$' && tok->data[i + 1] != '=' && tok->data[i + 1]
			&& tok->data[i + 1] != '\"' &&
			(i == 0 || (i > 0 && tok->data[i - 1] != '\\')))
		{
			j = i + 1;
			while (ft_isalnum(tok->data[j]) || tok->data[j] == '_')
				j++;
			if (tok->data[j] == '?')
				tok->data = replaceword(tok->data, "?", ft_itoa(lex->exit));
			else
				var = ft_substr(tok->data, i + 1, j - i - 1);
			new = ft_returnenvvar(var, m_envp);
			tok->data = replaceword(tok->data, var, new); 
			i = -1;
		}
	}
}

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

int		parse_files(t_tokens *tok, t_cmdTable *cmd, int type)
{
	int	fd;

	if (type == '<')
		cmd->infile = ft_strdup(tok->data);	
	else
	{
		cmd->outfile = ft_strdup(tok->data);
		cmd->outtype = type;
		if (type == '>')
			fd = open(tok->data, O_WRONLY|O_CREAT, 0666);
		else
			fd = open(tok->data, O_WRONLY|O_APPEND|O_CREAT, 0666);
		close(fd);
	}
	return (0);
}

int		insertargs(t_tokens *tok, t_cmdTable *cmd, int j)
{
	int	i;

	i = cmd->sCmd[j]->nArgs;
	if (i >= cmd->sCmd[j]->nAvalArg)
		return (-1);
	cmd->sCmd[j]->args[++i] = ft_strdup(tok->data);
	cmd->sCmd[j]->nArgs++;
	return (0);
}
