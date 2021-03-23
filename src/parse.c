#include "minishell.h"

int		insertcommand(char *text, int size, t_cmdTable *cmd, int j)
{
	cmd->sCmd[j]->args = (char **)malloc((size + 1) * sizeof(char *));
	cmd->sCmd[j]->nAvalArg = size + 1;
	cmd->sCmd[j]->nArgs = 0;
	cmd->sCmd[j]->args[0] = ft_strdup(text);
	cmd->nSimpleCmd++;
	return (1);
}

int		parse_cmd(t_lex *lex, t_tokens *tok, t_cmdTable *cmd, char **m_envp)
{
	int			count;
	t_tokens	*tok_aux;
	char		*text;

	tok_aux = tok;
	text = ft_strdup(tok->data);
	cmd->sCmd[lex->j]->builtin = 0;
	if (ispath(tok->data))
		text = ft_strdup(tok->data);
	else if (checkminicmd(tok->data))
		cmd->sCmd[lex->j]->builtin = 1;
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
	return(insertcommand(text, count, cmd, lex->j));
}

t_cmdTable	start_cmdtable(t_lex *lex, t_cmdTable ct)
{
	int	aux;
	int	j;
	
	lex->j = 0;
	aux = 1 + lex->npipes[lex->curr];	
	ct.nAvalSimpleCmd = aux;
	ct.nSimpleCmd = 0;
	ct.sCmd = (t_simpleCmd **)malloc(sizeof(t_simpleCmd *) * aux);
	j = 0;
	while (j < aux)
		ct.sCmd[j++] = (t_simpleCmd *)malloc(sizeof(t_simpleCmd));
	ct.outfile = NULL;
	ct.infile = NULL;
	ct.errfile = NULL;
	ct.outtype = 0;
	return (ct);
}	

void	parser_all(t_lex *lex, t_cmdTable *cmdtable, char **m_envp)
{
	t_tokens	*tok;
	int			cmd;
	int			redir;

	lex->j = 0;
	tok = lex->data;
	cmd = 0;
	redir = 0;
	while (tok && !lex->error && checkdollar(tok, lex, m_envp))
	{
		if (tok->type == 0 && !cmd && !redir)
			cmd = parse_cmd(lex, tok, &cmdtable[lex->curr], m_envp);
		else if (tok->type == 0 && cmd && !redir)
			insertargs(tok, &cmdtable[lex->curr], lex->j);
		else if (tok->type == '>' || tok->type == '<' || tok->type == GGREATER)
			redir = tok->type;
		else if (tok->type == 0 && redir)
			redir = parse_files(tok, &cmdtable[lex->curr], redir);
		else if (tok->type == '|')
			cmd = (lex->j++) * 0;
		else if (tok->type == ';' && lex->curr++ && !(cmd = 0))
			cmdtable[lex->curr] = start_cmdtable(lex, cmdtable[lex->curr]);
		tok = tok->next;
	}
}
