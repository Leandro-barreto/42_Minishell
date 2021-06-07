#include "minishell.h"

t_tokens	*read_quotes(char *text, t_tokens *tok, t_lex *lex, t_lexpar *par)
{
	int	i;
	int	end;
	int	quote;

	i = -1;
	quote = text[0];
	end = 0;
	while (text[++i] != '\0')
	{
		if (i == 0 || (text[i] != quote || text[i - 1] == '\\'))
			tok->data[par->j++] = text[i];
		else
		{
			tok->data[par->j++] = text[i];
			end = i;
			tok->quote = quote;
			break ;
		}
	}
	if (end == 0)
		lex->error = -quote;
	par->i += end;
	par->textsize -= end;
	return (tok);
}

void	count_semis2(t_lex *lex, int flag)
{
	lex->nsemis -= flag;
	lex->npipes = (int *)malloc(sizeof(int) * (lex->nsemis + 1));
	flag = 0;
	while (flag < lex->nsemis + 1)
		lex->npipes[flag++] = 0;
}

void	count_semis(char *text, t_lex *lex)
{
	int		i;
	int		flag;
	int		ret;
	char	c;

	i = 0;
	ret = handlequote(text);
	flag = 0;
	while (text[i] && ret != -1)
	{
		if (text[i] && (text[i] == '\"' || text[i] == '\'')
			&& (i == 0 || text[i - 1] != '\\'))
		{
			c = text[i++];
			while (text[i] && !(text[i] == c && text[i - 1] != '\\'))
				i++;
		}
		if (text[i] && text[i] == ';' && ++lex->nsemis)
			flag = 1;
		if (text[i] && ft_isalnum(text[i]))
			flag = 0;
		i++;
	}
	count_semis2(lex, flag);
}

int	lasttoken(t_lex *lex, t_tokens *tok)
{
	while (tok)
	{
		if (!tok->next && tok->type == '|' && !lex->error)
		{
			lex->errmsg = ft_strdup("Minishell doesn't handle multilines");
			lex->error = -PIPE;
		}
		tok = tok->next;
	}
	return (lex->error);
}

int	checktokens(t_lex *lex, t_tokens *tok)
{
	while (tok->next)
	{
		if (tok->type == ';')
		{
			if (tok->next && tok->next->type == '|')
				lex->errmsg = ft_strdup("|\'\n");
			else if (tok->next && tok->next->type == ';')
				lex->errmsg = ft_strdup(";;\'\n");
		}
		else if (tok->type == '|')
		{
			if (tok->next && tok->next->type == '|')
				lex->errmsg = ft_strdup("||\'\n");
			else if (tok->next && tok->next->type == ';')
				lex->errmsg = ft_strdup(";\'\n");
		}
		else if (tok->type == '>' || tok->type == '<' || tok->type == GGREATER)
			if (tok->next && tok->next->type != 0)
				lex->errmsg = ft_strdup("redir\n");
		tok = tok->next;
	}
	if (lex->errmsg)
		lex->error = -2;
	return (lasttoken(lex, lex->data));
}
