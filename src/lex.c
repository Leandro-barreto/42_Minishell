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
	tok->next = (t_tokens *)malloc(sizeof(t_tokens));
	if (length > 0)
	{
		start_tokens(tok->next, length);
		tok = tok->next;
		tok->next = NULL;
		lex->size++;
		par->j = 0;
	}
	else
	{
		lex->size++;
		tok->next = NULL;
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
			tok = end_current(tok, lex, par, par->textsize);
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

int			lexer(char *text, t_lex *lex, int textsize) 
{
	t_lexpar	*par;
	t_tokens	*tok;

	count_semis(text, lex);
	par = (t_lexpar *)malloc(sizeof(t_lexpar));
	start_lexpar(par, textsize);
	lex->data = (t_tokens *)malloc(sizeof(t_tokens));
	tok = lex->data;
	start_tokens(tok, textsize);	
	while(text[par->i] != '\0' && par->textsize >= 0)
	{
		par->c = verifychar(&text[par->i], par, lex);
		tok = lexer2(&text[par->i], tok, lex, par);
		if (lex->error < 0 )
			return (destroy_structs(lex, par));
		par->i++;
		par->textsize--;
	}
	if (par->j > 0)
		tok = end_current(tok, lex, par, 0);
	free(par);
	if (lex->data->type == '|' || lex->data->type == ';')
		lex->errmsg = ft_strdup(ft_strjoin(lex->data->data, "\'\n"));
	return (checktokens(lex, lex->data));
}

