#include "minishell.h"

void	delete_table(t_cmdTable *cmdtable, t_lex *lex)
{
    int i;
    int j;
    int k;

    i = lex->nsemis;
    while (i >= 0)
    {
		j = 0;
        while (j < cmdtable[i].nSimpleCmd)
        {
            k = 0;
            while (k < cmdtable[i].sCmd[j]->nAvalArg)
			{
                free(cmdtable[i].sCmd[j]->args[k++]);
			}
            free(cmdtable[i].sCmd[j]);
			j++;
        }
        i--;
    }
    free(cmdtable);
	destroy_structs(lex, NULL);
	free(lex);
}
