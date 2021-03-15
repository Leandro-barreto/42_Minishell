#include "minishell.h"

static int	verifychar(char *c, t_lexpar *par, t_lex *lex)
{
	if (*c ==  '\'')
		return (SQUOTE);
	else if (*c == '\"')
		return (DQUOTE);
	else if (*c == '|' && lex->npipes[lex->curr]++ >= 0)
		return (PIPE);
	else if (*c == ';' && lex->curr++ >=0)
		return (SEMICOLON);
	else if (*c == '>') 
	{
		c++;
		if (*c == '>' && par->i++ >= 0 && par->textsize-- >= 0)
			return GGREATER;
		return GREATER;
	}
	else if (*c == '<')
		return LESSER;
	else if (ft_iswhitespace(*c))
		return WHITESPACE;
    return 0;
}

t_tokens	*end_current(t_tokens *tok, t_lex *lex, t_lexpar *par, int length)
{
	tok->data[par->j] = '\0';
	tok->next = malloc(sizeof(t_tokens));
	if (length > 0)
	{
		start_tokens(tok->next, length);
		tok = tok->next;
		par->j = 0;
		lex->size++;
	}
	return (tok);
}

t_tokens	*read_quotes(char *text, t_tokens *tok, t_lex *lex, t_lexpar *par)
{
	int i;
	int	end;
	int	quote;

	i = 0;
	quote = text[i];
	end = 0;
	while(text[++i] != '\0')
	{
		if (text[i] != quote)
			tok->data[par->j++] = text[i];
		else
		{
			end = i;
			tok->quote = quote;
			tok = end_current(tok, lex, par, par->textsize - i);
			break ;
		}
	}
	if (end == 0)
		lex->error = -quote;
	par->i += end;
	par->textsize -= end;
	return (tok);
}

t_tokens	*lexer2(char *text, t_tokens *tokens, t_lex *lex, t_lexpar *par)
{
	if (par->c == SQUOTE || par->c == DQUOTE)
	{		
		if ((tokens = read_quotes(text, tokens, lex, par)) && (lex->error < 0)) 
			lex->error = -par->c;
	}
	else if (par->c == 0)
		tokens->data[par->j++] = *text;
	else if (par->c == WHITESPACE)
	{
		if (par->j > 0)
			tokens = end_current(tokens, lex, par, par->textsize);
	}
	else if (par->c == PIPE || par->c == GREATER || par->c == GGREATER ||
					par->c == SEMICOLON || par->c == LESSER)
	{
		if (par->j > 0)
			tokens = end_current(tokens, lex, par, 3);
		tokens->data[par->j++] = *text;
		if (par->c == 1240)
			tokens->data[par->j++] = '>';
		tokens->type = par->c;
		tokens = end_current(tokens, lex, par, par->textsize);
	}
	return (tokens);
}

void		count_semis(char *text, t_lex *lex)
{
	int	i;

	i = 0;
	while (text[i])
	{
		if (text[i++] == ';')
			lex->nsemis++;
	}
	lex->npipes = (int *)malloc(sizeof(*lex->npipes) * (lex->nsemis + 1));
	lex->npipes[0] = 0;
}

int			lexer(char *text, t_lex *lex, int textsize) 
{
	t_lexpar	*par;
	t_tokens	*tokens;
	
	count_semis(text, lex);
	if (lex == NULL)
		return -1;
	par = (t_lexpar *)malloc(sizeof(t_lexpar));
	start_lexpar(par, textsize);
	lex->data = malloc(sizeof(t_tokens));
	tokens = lex->data;
	start_tokens(tokens, textsize);	
	while(text[par->i] != '\0' && par->textsize >= 0)
	{
		par->c = verifychar(&text[par->i], par, lex);

		tokens = lexer2(&text[par->i], tokens, lex, par);
		if (lex->error < 0 )
			return (destroy_structs(lex, par));
		par->i++;
		par->textsize--;
	}
	if (par->j > 0)

		tokens = end_current(tokens, lex, par, 0);

	free(par);
	return (0);
}

