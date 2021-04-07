/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lborges- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:03:49 by lborges-          #+#    #+#             */
/*   Updated: 2020/01/21 19:04:33 by lborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <dirent.h>

# define PIPE '|'
# define SQUOTE '\''
# define DQUOTE '\"'
# define SEMICOLON ';'
# define GREATER '>'
# define GGREATER 1240
# define LESSER	'<'
# define WHITESPACE ' '
# define WORD -1

typedef struct s_tokens	t_tokens;
int						g_run;

typedef struct	s_lexpar
{
	int		c;
	int		i;
	int		j;
	int		textsize;
}				t_lexpar;

struct			s_tokens
{
	char		*data;
	int			type;
	int			quote;
	t_tokens	*next;
};

typedef struct	s_lex
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

typedef struct	s_simplecmd
{
	int		navalarg;
	int		nargs;
	char	**args;
	int		builtin;

}				t_simplecmd;

typedef struct	s_cmdtable
{
	int			navalsimplecmd;
	int			nsimplecmd;
	t_simplecmd	**scmd;
	char		*outfile;
	char		*infile;
	char		*errfile;
	int			outtype;
}				t_cmdtable;

typedef struct	s_exec
{
	int			tmpin;
	int			tmpout;
	int			fdin;
	int			fdout;
	int			ret;
	int			i;
	int			fdpipe[2];
}				t_exec;

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
int				destroy_structs(t_lex *lex, t_lexpar *par);
void			start_tokens(t_tokens *tok, int length);
int				destroy_tokens(t_tokens *tok);
void			start_lexpar(t_lexpar *par, int textsize);
t_lex			start_lexer(t_lex *lex);

/*
** Lex_utils2.c
*/
int				checktokens(t_lex *lex, t_tokens *tok);
void			count_semis(char *text, t_lex *lex);
t_tokens		*read_quotes(char *txt, t_tokens *t, t_lex *lex, t_lexpar *par);

/*
** Parse.c
*/
void			parser_all(t_lex *lex, t_cmdtable *cmdtable, char **m_envp);
t_cmdtable		start_cmdtable(t_lex *lex, t_cmdtable ct);
int				parse_cmd(t_lex *l, t_tokens *t, t_cmdtable *cmd, char **m_env);
int				insertcommand(char *text, int size, t_cmdtable *cmd, int j);

/*
** Parse_aux
*/
char			*replaceword(char *phrase, char *oldword, char *newword);
int				insertargs(t_tokens *tok, t_cmdtable *cmd, int j);
int				parse_files(t_tokens *tok, t_cmdtable *cmd, int type);
char			*checkdollar(char *tok, t_lex *lex, char **m_envp);
int				checkminicmd(char *cmd);

/*
** Path.c
*/
int				ft_isin(const char *haystack, const char *needle);
char			*checkpathvar(char *var, char *cmd, char **envp);
char			*ft_returnenvvar(char *name, char **m_envp);
int				workingfile(char *file);
int				ispath(char *text);

/*
** Execute.c
*/
int				exec_builtin(t_cmdtable *cmd, int i, char **m_envp, t_lex *lex);
int				execute_cmd(t_cmdtable *cmd, char **m_envp, t_lex *lex);

/*
** Execbuiltin.c
*/
int				minicd(t_simplecmd *scmd, char **m_envp);
int				minienv(t_simplecmd *scmd, char **m_envp);
int				miniexit(t_cmdtable *cmd, t_lex *lex, int i);
int				minipwd(t_simplecmd *scmd);

/*
** echo.c
*/
int				miniecho(t_simplecmd *scmd);

/*
** Export.c
*/
char			*remove_quotes(char *var);
int				miniexport(t_simplecmd *scmd, char **m_envp);

/*
** Unset.c
*/
int				miniunset(t_simplecmd *scmd, char **m_envp);

/*
** Delete.c
*/
void			delete_table(t_cmdtable *cmdtable, t_lex *lex);

/*
** Error.c
*/
int				printerror(int err, int func, char *auxstr, int fd);

#endif
