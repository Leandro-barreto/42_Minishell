#include "minishell.h"

int	destroy_tokens(t_tokens *tok)
{
	if (tok != NULL)
	{
		free(tok->data);
		destroy_tokens(tok->next);
		free(tok);
	}
	return (0);
}

int	destroy_structs(t_lex *lex, t_lexpar *par)
{
	if (par != NULL)
		free(par);
	if (lex == NULL)
		return (0);
	free(lex->npipes);
	if (lex->errmsg)
		free(lex->errmsg);
	destroy_tokens(lex->data);
	free(lex);
	return (0);
}

void	deletecmdtable(t_cmdTable *table)
{
	if (table)
	{
		if (table->outfile)
			free(table->outfile);
		if (table->infile)
			free(table->infile);
	}
}

void	delete_table(t_cmdTable *table, t_lex *lex)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	if (lex)
		i = lex->nsemis;
	while (i >= 0 && table)
	{
		j = 0;
		while (j < table[i].nAvalSimpleCmd)
		{
			k = 0;
			while (table[i].sCmd[j]->args && k <= table[i].sCmd[j]->nArgs)
				free(table[i].sCmd[j]->args[k++]);
			if (table[i].sCmd[j]->args)
				free(table[i].sCmd[j]->args);
			free(table[i].sCmd[j]);
			j++;
		}
		free(table[i].sCmd);
		deletecmdtable(&table[i--]);
	}
	free(table);
	destroy_structs(lex, NULL);
}
