#include "minishell.h"

int	insertcommand(char *text, int size, t_cmdTable *cmd, int j)
{
	if (checkminicmd(text))
		cmd->sCmd[j]->builtin = 1;
	cmd->sCmd[j]->args = (char **)malloc((size + 2) * sizeof(char *));
	cmd->sCmd[j]->nAvalArg = size + 1;
	cmd->sCmd[j]->nArgs = 0;
	cmd->sCmd[j]->args[0] = ft_strdup(text);
	free(text);
	cmd->sCmd[j]->args[size + 1] = NULL;
	cmd->nSimpleCmd++;
	return (1);
}

int	parse_cmd(t_lex *lex, t_tokens *tok, t_cmdTable *cmd, t_env *m_envp)
{
	int			count;
	t_tokens	*t2;
	char		*text;

	t2 = tok;
	text = NULL;
	cmd->sCmd[lex->j]->builtin = 0;
	if (ispath(tok->data) == 2 && lex->error != -127)
		text = ft_strdup(tok->data);
	else if (checkminicmd(tok->data))
		text = ft_strdup(tok->data);
	else if (!ispath(tok->data))
		text = checkpathvar("PATH", tok->data, m_envp);
	if (!text)
		return (lex->error = -127);
	count = 0;
	while (t2->next && t2->type != '|' && t2->type != ';')
	{
		if (t2->type == 0 && t2->next->type == 0)
			count++;
		t2 = t2->next;
	}
	return (insertcommand(text, count, cmd, lex->j));
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
	{
		ct.sCmd[j] = (t_simpleCmd *)malloc(sizeof(t_simpleCmd));
		ct.sCmd[j++]->args = NULL;
	}
	ct.outfile = NULL;
	ct.infile = NULL;
	ct.outtype = 0;
	ct.error = 0;
	return (ct);
}	

int	parser_normfdp(t_lex *lex, t_cmdTable *cmdtable, int cmd)
{
	cmd = 0;
	lex->j = 0;
	lex->curr++;
	if (lex->curr > lex->nsemis)
		return (-5);
	cmdtable[lex->curr] = start_cmdtable(lex, cmdtable[lex->curr]);
	return (cmd);
}

void	parser_all(t_lex *lex, t_cmdTable *cmdtable, t_env *m_envp)
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
		checkdollar(tok, m_envp);
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
		else if (tok->type == ';' && tok->next)
			cmd = parser_normfdp(lex, cmdtable, cmd);
		tok = tok->next;
	}
}
