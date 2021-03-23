#include "minishell.h"

void		count_semis(char *text, t_lex *lex)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (text[++i])
	{
		if (text[i] == ';')
		{
			lex->nsemis++;
			flag = 1; 
		}
		if (ft_isalnum(text[i]))
			flag = 0;
	}
	lex->nsemis -= flag;
	lex->npipes = (int *)malloc(sizeof(int) * (lex->nsemis + 1));
	lex->npipes[0] = 0;
}

int			checktokens(t_lex *lex, t_tokens *tok)
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
		else if (tok->type == '>' || tok->type == '<'|| tok->type == GGREATER)
			if (tok->next && tok->next->type != 0)
				lex->errmsg = ft_strdup("redir\n"); 
		tok = tok->next;
	}
	if (lex->errmsg)
		lex->error = -2;
	return (lex->error);
}
