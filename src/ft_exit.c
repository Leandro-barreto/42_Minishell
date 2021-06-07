#include "minishell.h"

int	ft_exit(t_lex *lex, t_cmdTable *cmdtable, int exitval)
{
	if (g_global.save)
	{
		tcsetattr(STDIN_FILENO, TCSAFLUSH, g_global.save);
		free(g_global.save);
		g_global.save = NULL;
	}
	if (g_global.line)
		dellines(ft_strlen(g_global.line));
	delete_table(cmdtable, lex);
	exit(exitval);
}
