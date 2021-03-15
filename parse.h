#ifndef PARSER_H
# define PARSER_H

# include "./libft/libft.h"
# include "./lexer/lex.h"


typedef struct	s_simpleCmd
{
	int		nAvalArg;
	int		nArgs;
	char	**args;

}				t_simpleCmd;

typedef struct s_cmdTable
{
	int			nAvalSimpleCmd;
	int			nSimpleCmd;
	t_simpleCmd	**sCmd;
	char		*outfile;
	char		*infile;
	char		*errfile;
	int			outtype;
}				t_cmdTable;

int				parser_cmds(t_lex *lex, t_cmdTable *cmdtable);
t_cmdTable		start_cmdtable(t_lex *lex, t_cmdTable ct);
#endif
