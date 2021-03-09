#include "parse.h"
#include "libft/libft.h"
#include "lexer/lex.h"
#include <stdio.h> 
#include <string.h> 

int		ft_isin(const char *haystack, const char *needle)
{
	int	i;
	int	j;

	write(1, "Isin\n", 5);
	if (!*needle)
		return (0);
	i = ft_strlen(haystack) - 1;
	j = ft_strlen(needle) - 1;
	while (haystack[i] == needle[j] && j >= 0)
	{
		i--;
		j--;
	}
	if (j == -1)
		return (1);
	return (0);
}

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

int		insertcommand(t_tokens *tok, int size, t_cmdTable *cmd, int j)
{
	write(1, "Insert cmd\n", 11);
	printf("J: %i\nSize: %i\n", j, size);
	fflush(stdout);
	cmd->sCmd[j]->args = (char **)malloc((size + 1) * sizeof(char *));
	write(1, "A1\n", 3);
	cmd->sCmd[j]->nAvalArg = size;
	cmd->sCmd[j]->nArgs = 0;
	write(1, "A2\n", 3);
	printf("P: %p\nSize: %s\n", cmd->sCmd[j]->args, tok->data);
	cmd->sCmd[j]->args[0] = ft_strdup(tok->data);
	write(1, "A3\n", 3);
	return (1);
}

int		parse_cmd(t_lex *lex, t_tokens *tok, t_cmdTable *cmd, int j)
{
	write(1, "Parse cmd\n", 10);
	int			count;
	t_tokens	*tok_aux;

	tok_aux = tok;
	if (ft_isin(tok->data, "echo"))
	{
		count = 0;
		while (tok_aux->next && tok_aux->type == 0)
		{
			count++;
			tok_aux = tok_aux->next;
		}
		return (insertcommand(tok, count, cmd, j));
	}
	else if (ft_isin(tok->data, "cd") || ft_isin(tok->data, "export") ||
			ft_isin(tok->data, "unset"))
		return (insertcommand(tok, 2, cmd, j));
	else if (ft_isin(tok->data, "pwd") || ft_isin(tok->data, "env") ||
			ft_isin(tok->data, "exit"))
		return (insertcommand(tok, 1, cmd, j));
	lex->error = -5;
	return (-1);
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

int	parser_cmds(t_lex *lex, t_cmdTable *cmdtable)
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
		write(1, "While \n", 7);
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
