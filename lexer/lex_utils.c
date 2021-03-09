#include "lex.h"

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

void	start_lexer(t_lex* lex)
{
	lex->data = malloc(sizeof(t_tokens));
	lex->size = 0;
	lex->npipes = NULL;
	lex->nsemis = 0;
	lex->curr = 0;
	lex->error = 0;
}

int		destroy_tokens(t_tokens* tok)
{
	if (tok != NULL)
	{
		free(tok->data);
		destroy_tokens(tok->next);
		free(tok);
	}
	return (0);
}

int		destroy_structs(t_lex *lex, t_lexpar *par)
{
	if (par != NULL)
		free(par);
	if (lex == NULL)
		return (0);
	destroy_tokens(lex->data);
	return (0);
}

