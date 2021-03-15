#include "minishell.h"

int		parse_files(t_tokens *tok, t_cmdTable *cmd, int type)
{
	write(1, "Insert Fil\n", 11);
	if (type == '<')
		cmd->infile = ft_strdup(tok->data);	
	else
	{
		cmd->outfile = ft_strdup(tok->data);
		cmd->outtype = type;
	}
	return (0);
}

int		insertargs(t_tokens *tok, t_cmdTable *cmd, int j)
{
	int	i;

	write(1, "Insert Arg\n", 11);
	i = cmd->sCmd[j]->nArgs;
	if (i >= cmd->sCmd[j]->nAvalArg)
		return (-1);
	cmd->sCmd[j]->args[++i] = ft_strdup(tok->data);
	cmd->sCmd[j]->nArgs++;
	return (0);
}

int		insertcommand(char *text, int size, t_cmdTable *cmd, int j)
{
	write(1, "Insert cmd\n", 11);
	printf("Args: %i\n", size);
	printf("Args: %i\n", size);
	cmd->sCmd[j]->args = (char **)malloc((size + 1) * sizeof(char *));
	cmd->sCmd[j]->nAvalArg = size;
	cmd->sCmd[j]->nArgs = 0;
	cmd->sCmd[j]->args[0] = ft_strdup(text);
	return (1);
}

int		parse_cmd(t_lex *lex, t_tokens *tok, t_cmdTable *cmd, int j)
{
	int			count;
	t_tokens	*tok_aux;
	char		*text;

	tok_aux = tok;
	text = ft_strdup(tok->data);
	cmd->sCmd[j]->builtin = 0;
	if (ispath(tok->data))
		text = ft_strdup(tok->data);
	else if (checkminicmd(tok->data))
		cmd->sCmd[j]->builtin = 1;
	else
		text = checkpathvar("PATH", tok->data);
	if (text == NULL)
	{
		write(1, "Aqui!!!", 6);
		lex->error = -15; 	
		return (lex->error);
	}
	count = 0;
	while (tok_aux->next && tok_aux->type == 0)
	{
		count++;
		tok_aux = tok_aux->next;
	}
	return(insertcommand(text, count, cmd, j));
}

t_cmdTable	start_cmdtable(t_lex *lex, t_cmdTable ct)
{
	int	aux;
	int	j;
	
	write(1, "Start cmdtable\n", 15);
	aux = 1 + lex->npipes[lex->curr];	
	ct.nAvalSimpleCmd = aux;
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

int	parser_all(t_lex *lex, t_cmdTable *cmdtable)
{
	t_tokens	*tok;
	int			cmd;
	int			redir;
	int			j;

	j = 0;
	tok = lex->data;
	cmd = 0;
	redir = 0;
	write(1, "Parser\n", 7);
	while (tok->next && !lex->error)
	{
		if (tok->type == 0 && !cmd && !redir)
		{
			cmd = parse_cmd(lex, tok, &cmdtable[lex->curr], j);
		}
		else if (tok->type == 0 && cmd && !redir)
			insertargs(tok, cmdtable, j);
		else if (tok->type == '>' || tok->type == '<' || tok->type == GGREATER)
		{
			redir = tok->type;
			cmd = 0;
		}
		else if (tok->type == 0 && !cmd && redir)
		{
			redir = parse_files(tok, &cmdtable[lex->curr], redir);
		}
		else if (tok->type == '|')
		{	
			cmd = 0;
			j++;
		}
		else if (tok->type == ';')
		{	
			cmd = 0;
			j = 0;
			lex->curr++;
			cmdtable[lex->curr] = start_cmdtable(lex, cmdtable[lex->curr]);
		}
		tok = tok->next;
	}
	if (redir && !lex->error)
		lex->error = -171;
	return (0);
}
