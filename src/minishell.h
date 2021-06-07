#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <dirent.h>
# include <curses.h>
# include <term.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# define PIPE '|'
# define SQUOTE '\''
# define DQUOTE '\"'
# define SEMICOLON ';'
# define GREATER '>'
# define GGREATER 1240
# define LESSER	'<'
# define WHITESPACE ' '
# define WORD -1
# define LF '\n'
# define DEL 127
# define ESC 27
# define SQ_BR '['
# define UP 'A'
# define DOWN 'B'
# define EOT 4

typedef struct s_tokens	t_tokens;

typedef struct s_global
{
	char			*line;
	char			*tmpline;
	int				exit;
	int				run;
	struct termios	*save;
}				t_global;

t_global				g_global;

typedef struct s_history
{
	char				*cmd_line;
	struct s_history	*next;
	struct s_history	*prev;
}				t_history;

typedef struct s_lexpar
{
	int		c;
	int		i;
	int		j;
	int		textsize;
}				t_lexpar;

struct s_tokens
{
	char		*data;
	int			type;
	int			quote;
	t_tokens	*next;
};

typedef struct s_lex
{
	t_tokens	*data;
	int			size;
	int			*npipes;
	int			nsemis;
	int			curr;
	int			error;
	char		*errmsg;
	int			exit;
	int			j;
}				t_lex;

typedef struct s_simpleCmd
{
	int			nAvalArg;
	int			nArgs;
	char		**args;
	int			builtin;

}				t_simpleCmd;

typedef struct s_cmdTable
{
	int			nAvalSimpleCmd;
	int			nSimpleCmd;
	t_simpleCmd	**sCmd;
	char		*outfile;
	char		*infile;
	int			outtype;
	int			error;
}				t_cmdTable;

typedef struct s_exec
{
	int			tmpin;
	int			tmpout;
	int			fdin;
	int			fdout;
	int			ret;
	int			i;
	int			n;
	int			fdpipe[2];
}				t_exec;

typedef struct s_env
{
	char		**env;
	int			size;
}				t_env;

/*
** main
*/
void			sighandler(int signum);

/*
** Lex.c
*/
int				lexer(char *text, t_lex *lex, int textsize);
t_tokens		*end_current(t_tokens *tok, t_lex *lex, t_lexpar *par, int len);

/*
** lex_utils.c
*/
void			start_tokens(t_tokens *tok, int length);
int				handlequote(char *text);
void			start_lexpar(t_lexpar *par, int textsize);
t_lex			start_lexer(t_lex *lex);
int				ft_strlen_mini(char *text);

/*
** Lex_utils2.c
*/
int				checktokens(t_lex *lex, t_tokens *tok);
void			count_semis(char *text, t_lex *lex);
t_tokens		*read_quotes(char *txt, t_tokens *t, t_lex *lex, t_lexpar *par);

/*
** Parse.c
*/
void			parser_all(t_lex *lex, t_cmdTable *cmdtable, t_env *m_envp);
t_cmdTable		start_cmdtable(t_lex *lex, t_cmdTable ct);
int				parse_cmd(t_lex *l, t_tokens *t, t_cmdTable *cmd, t_env *m_env);
int				insertcommand(char *text, int size, t_cmdTable *cmd, int j);

/*
**  Parse_aux
*/
char			*replaceword(char *phrase, char *oldword, char *newword);
int				insertargs(t_tokens *tok, t_cmdTable *cmd, int j);
int				parse_files(t_tokens *tok, t_cmdTable *cmd, int type);
void			checkdollar(t_tokens *tok, t_env *m_envp);
int				checkminicmd(char *cmd);

/*
** Path.c
*/
int				ft_isin(const char *haystack, const char *needle);
char			*checkpathvar(char *var, char *cmd, t_env *m_envp);
char			*ft_returnenvvar(char *name, t_env *m_envp);
int				workingfile(char *file);
int				ispath(char *text);

/*
** Execute.c
*/
int				exec_builtin(t_cmdTable *c, t_exec *e, t_env *m_enp, t_lex *l);
int				execute_cmd(t_cmdTable *cmd, t_env *m_envp, t_lex *lex, int n);

/*
** Execute.c
*/
t_simpleCmd		*handlequotes(t_simpleCmd *scmd);

/*
** Exebuiltin.c
*/
int				minicd(t_simpleCmd *scmd, t_env *m_envp);
int				minienv(t_simpleCmd *scmd, t_env *m_envp);
int				miniexit(t_cmdTable *cmd, t_lex *lex, int i, int n);
int				minipwd(t_simpleCmd *scmd);

/*
** echo.c
*/
int				miniecho(t_simpleCmd *scmd);

/*
** Export.c
*/
int				miniexport(t_simpleCmd *scmd, t_env *m_envp);

/*
** Unset.c
*/
int				miniunset(t_simpleCmd *scmd, t_env *m_envp);

/*
** Delete.c
*/
void			delete_table(t_cmdTable *cmdTable, t_lex *lex);
int				destroy_tokens(t_tokens *tok);
int				destroy_structs(t_lex *lex, t_lexpar *par);

/*
** Erro.c
*/
int				printerror(int err, int func, char *auxstr, int fd);

/*
**	Termcap.c
*/
int				get_input_user(char **history);
int				read_line(char **history);

/*
**	Termcap_utils.c
*/
void			deleteline(int size, int col);
void			dow_arrow(char **history, int *present);
void			up_arrow(char **history, int *present);
int				handle_event(char *buf, char **history, int *present);

/*
**	Termcap_utils2.c
*/
int				ft_putchar(int c);
void			add_char(char c, int size);
void			init_terminal(void);
void			dellines(int size);
int				write_cmd(char **history, int size, int flag);

/*
**	ft_exit.c
*/
int				ft_exit(t_lex *lex, t_cmdTable *cmdtable, int exit);

/*
**	environment.c
*/
t_env			*start_env(char **envp, int aux);
void			delete_env(t_env *envp, int flag);
void			update_env(t_env *m_envp, char *var);
void			remove_env(t_env *m_envp, int pos);

#endif
