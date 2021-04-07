/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lborges- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:03:49 by lborges-          #+#    #+#             */
/*   Updated: 2020/01/21 19:04:33 by lborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	verifychar(char *c, t_lexpar *par, t_lex *lex)
{
	if (*c == '\'')
		return (SQUOTE);
	else if (*c == '\"')
		return (DQUOTE);
	else if (*c == '|' && lex->npipes[lex->curr]++ >= 0)
		return (PIPE);
	else if (*c == ';' && lex->curr++ >= 0)
		return (SEMICOLON);
	else if (*c == '>')
	{
		c++;
		if (*c == '>' && par->i++ >= 0 && par->textsize-- >= 0)
			return (GGREATER);
		return (GREATER);
	}
	else if (*c == '<')
		return (LESSER);
	else if (*c == '\\' && (*(c + 1) == '\'' || *(c + 1) == '\"'))
	{
		par->i++;
		return (1);
	}
	else if (ft_iswhitespace(*c))
		return (WHITESPACE);
	return (0);
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

t_tokens	*lexer2(char *text, t_tokens *tokens, t_lex *lex, t_lexpar *par)
{
	if (par->c == SQUOTE || par->c == DQUOTE)
	{
		if ((tokens = read_quotes(text, tokens, lex, par)) && (lex->error < 0))
			lex->error = -par->c;
	}
	else if (par->c == 0)
		tokens->data[par->j++] = *text;
	else if (par->c == WHITESPACE && par->j > 0)
		tokens = end_current(tokens, lex, par, par->textsize);
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
	else if (par->c == 1)
		tokens->data[par->j++] = *text;
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
	while (text[par->i] != '\0' && par->textsize >= 0)
	{
		par->c = verifychar(&text[par->i], par, lex);
		tok = lexer2(&text[par->i], tok, lex, par);
		if (lex->error < 0)
			return (destroy_structs(lex, par));
		par->i++;
		par->textsize--;
	}
	tok = end_current(tok, lex, par, 0);
	free(par);
	if (lex->data->type == '|' || lex->data->type == ';')
		lex->errmsg = ft_strdup(ft_strjoin(lex->data->data, "\'\n"));
	tok = lex->data;
	//// Descomnetar para imprimir tokens.
	// while (tok)
	// {
	// 	printf("Data %s\n", tok->data);
	// 	tok = tok->next;
	// }
	// return (checktokens(lex, lex->data));
}
