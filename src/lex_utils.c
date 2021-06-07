#include "minishell.h"

int	ft_strlen_mini(char *text)
{
	int	i;

	i = ft_strlen(text);
	while (i && ft_iswhitespace(text[i - 1]))
		i--;
	return (i);
}

int	handlequote(char *text)
{
	int		i;
	int		count1;
	int		count2;

	i = 0;
	count1 = 0;
	count2 = 0;
	while (text[i])
	{
		if (text[i] && text[i] == '\'' && (i == 0 || text[i - 1] != '\\'))
			count1++;
		if (text[i] && text[i] == '\"' && (i == 0 || text[i - 1] != '\\'))
			count2++;
		i++;
	}
	if (count1 % 2 != 0 || count2 % 2 != 0)
		return (-1);
	return (0);
}

void	start_lexpar(t_lexpar *par, int textsize)
{
	par->i = 0;
	par->j = 0;
	par->textsize = textsize;
	par->c = 0;
}

void	start_tokens(t_tokens *tok, int length)
{
	tok->data = (char *)malloc(length + 1);
	tok->next = NULL;
	tok->type = 0;
	tok->quote = 0;
}

t_lex	start_lexer(t_lex *lex)
{
	lex->data = NULL;
	lex->size = 0;
	lex->npipes = NULL;
	lex->nsemis = 0;
	lex->curr = 0;
	lex->error = 0;
	lex->exit = 0;
	lex->errmsg = NULL;
	return (*lex);
}
