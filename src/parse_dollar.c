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

int	dollarconditions(t_tokens *tok, int i)
{
	if (tok->data[i] == '$' && tok->data[i + 1] != '=' && tok->data[i + 1]
		&& tok->data[i + 1] != '\"'
		&& (i == 0 || (i > 0 && tok->data[i - 1] != '\\')))
		return (1);
	return (0);
}

void	replacequestion(t_tokens *tok)
{
	char	*aux;
	char	*new;

	new = ft_itoa(g_global.exit);
	aux = replaceword(tok->data, "?", new);
	free(new);
	if (tok->data)
		free(tok->data);
	tok->data = aux;
}

void	checkdollaraux(t_tokens *tok, char *var, t_env *m_envp)
{
	char	*new;
	char	*aux;

	new = ft_returnenvvar(var, m_envp);
	aux = replaceword(tok->data, var, new);
	if (tok->data)
		free(tok->data);
	if (var)
		free(var);
	tok->data = aux;
}

void	checkdollar(t_tokens *tok, t_env *m_envp)
{
	char	*var;
	int		i;
	int		j;

	i = -1;
	while (tok->data[++i] && tok->quote != '\'')
	{	
		if (dollarconditions(tok, i))
		{
			var = NULL;
			j = i + 1;
			while (ft_isalnum(tok->data[j]) || tok->data[j] == '_')
				j++;
			if (tok->data[j] == '?')
				replacequestion(tok);
			else
			{
				var = ft_substr(tok->data, i + 1, j - i - 1);
				checkdollaraux(tok, var, m_envp);
			}
			i = -1;
		}
	}
}
