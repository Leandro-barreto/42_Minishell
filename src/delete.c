/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lborges- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:03:49 by lborges-          #+#    #+#             */
/*   Updated: 2020/01/21 19:04:33 by lborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		destroy_tokens(t_tokens *tok)
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

void	delete_table(t_cmdtable *cmdtable, t_lex *lex)
{
	int	i;
	int	j;
	int	k;

	i = lex->nsemis;
	if (!cmdtable)
		return ;
	while (i >= 0)
	{
		j = 0;
		while (j < cmdtable[i].nsimplecmd)
		{
			k = 0;
			while (k < cmdtable[i].scmd[j]->nargs)
			{
				free(cmdtable[i].scmd[j]->args[k++]);
			}
			free(cmdtable[i].scmd[j]);
			j++;
		}
		i--;
	}
	free(cmdtable);
	destroy_structs(lex, NULL);
	free(lex);
}
