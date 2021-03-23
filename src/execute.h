#ifndef EXECUTE_H
# define EXECUTE_H

# include "./libft/libft.h"
# include "./lexer/lex.h"
# include <sys/wait.h>

typedef struct	s_simpleCmd
{
	int		nAvalArg;
	int		nArgs;
	char	**args;
	int		builtin;

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

char 	**g_envp;

//Parse.c
int				parser_all(t_lex *lex, t_cmdTable *cmdtable);
t_cmdTable		start_cmdtable(t_lex *lex, t_cmdTable ct);
int				parse_cmd(t_lex *lex, t_tokens *tok, t_cmdTable *cmd, int j);
int				insertcommand(char *text, int size, t_cmdTable *cmd, int j);
int				insertargs(t_tokens *tok, t_cmdTable *cmd, int j);
int				parse_files(t_tokens *tok, t_cmdTable *cmd, int type);

// Parse_aux
int				checkminicmd(char *cmd);

//Path.c
int				ft_isin(const char *haystack, const char *needle);
char			*checkpathvar(char *var, char *cmd);
char			*ft_returnenvvar(char *name);
int				workingfile(char *file);
int				ispath(char *text);

//Execute.c
void	minicd(t_simpleCmd *scmd);
void	minienv(t_simpleCmd *scmd);
void	minipwd(t_simpleCmd *scmd);
void	miniecho(t_simpleCmd *scmd);
void	miniexit(t_simpleCmd *scmd);
void	exec_builtin(t_simpleCmd *scmd);
void	execute_cmd(t_cmdTable *cmd);

//Delete.c
void	delete_table(t_cmdTable *cmdTable, t_lex *lex);

#endif
