/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lborges- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:03:49 by lborges-          #+#    #+#             */
/*   Updated: 2020/01/21 19:04:33 by lborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	lex->data = malloc(sizeof(t_tokens));
	lex->size = 0;
	lex->npipes = NULL;
	lex->nsemis = 0;
	lex->curr = 0;
	lex->error = 0;
	lex->errmsg = NULL;
	return (*lex);
}
