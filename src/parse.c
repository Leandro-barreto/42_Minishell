/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lborges- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:03:49 by lborges-          #+#    #+#             */
/*   Updated: 2021/04/02 17:28:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			insertcommand(char *text, int size, t_cmdtable *cmd, int j)
{
	cmd->scmd[j]->args = (char **)malloc((size + 2) * sizeof(char *));
	cmd->scmd[j]->navalarg = size + 1;
	cmd->scmd[j]->nargs = 0;
	cmd->scmd[j]->args[0] = ft_strdup(text);
	cmd->scmd[j]->args[size + 1] = NULL;
	cmd->nsimplecmd++;
	return (1);
}

int			parse_cmd(t_lex *lex, t_tokens *tok, t_cmdtable *cmd, char **m_envp)
{
	int			count;
	t_tokens	*tok_aux;
	char		*text;

	tok_aux = tok;
	text = ft_strdup(tok->data);
	cmd->scmd[lex->j]->builtin = 0;
	if (ispath(tok->data))
		text = ft_strdup(tok->data);
	else if (checkminicmd(tok->data))
		cmd->scmd[lex->j]->builtin = 1;
	else
		text = checkpathvar("PATH", tok->data, m_envp);
	if (text == NULL && (lex->error = -127) < 0)
		return (lex->error);
	count = 0;
	while (tok_aux->next && tok_aux->type != '|' && tok_aux->type != ';')
	{
		if (tok_aux->type == 0)
			count++;
		tok_aux = tok_aux->next;
	}
	errno = 0;
	return (insertcommand(text, count, cmd, lex->j));
}

t_cmdtable	start_cmdtable(t_lex *lex, t_cmdtable ct)
{
	int			aux;
	int			j;

	lex->j = 0;
	aux = 1 + lex->npipes[lex->curr];
	ct.navalsimplecmd = aux;
	ct.nsimplecmd = 0;
	ct.scmd = (t_simplecmd **)malloc(sizeof(t_simplecmd *) * aux);
	j = 0;
	while (j < aux)
		ct.scmd[j++] = (t_simplecmd *)malloc(sizeof(t_simplecmd));
	ct.outfile = NULL;
	ct.infile = NULL;
	ct.errfile = NULL;
	ct.outtype = 0;
	return (ct);
}

int			parser_normfdp(t_lex *lex, t_cmdtable *cmdtable, int cmd)
{
	cmd = 0;
	lex->j = 0;
	lex->curr++;
	cmdtable[lex->curr] = start_cmdtable(lex, cmdtable[lex->curr]);
	return (cmd);
}

void		parser_all(t_lex *lex, t_cmdtable *cmdtable, char **m_envp)
{
	t_tokens	*tok;
	int			cmd;
	int			redir;

	lex->j = 0;
	tok = lex->data;
	cmd = 0;
	redir = 0;
	while (tok && !lex->error)
	{
		if (tok->type == 0 && !cmd && !redir)
			cmd = parse_cmd(lex, tok, &cmdtable[lex->curr], m_envp);
		else if (tok->type == 0 && cmd && !redir && tok->data[0] != '\0')
			insertargs(tok, &cmdtable[lex->curr], lex->j);
		else if (tok->type == '>' || tok->type == '<' || tok->type == GGREATER)
			redir = tok->type;
		else if (tok->type == 0 && redir)
			redir = parse_files(tok, &cmdtable[lex->curr], redir);
		else if (tok->type == '|')
			cmd = (lex->j++) * 0;
		else if (tok->type == ';')
			cmd = parser_normfdp(lex, cmdtable, cmd);
		tok = tok->next;
	}
}
