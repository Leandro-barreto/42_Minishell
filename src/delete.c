#include "minishell.h"

void	delete_table(t_cmdTable *cmdtable, t_lex *lex)
{
    int i;
    int j;
    int k;

    i = lex->nsemis;
    j = -1;
    k = -1;
    while (i > 0)
    {
        while (++j < cmdtable[i].nAvalSimpleCmd)
        {
            while (++k < cmdtable[i].sCmd[j]->nArgs)
                free(cmdtable[i].sCmd[j]->args[k]);
            k = -1;
            free(cmdtable[i].sCmd[j]);
        }
        j = -1;
        i--;
    }
    free(cmdtable);
}
