#ifndef LEX_H
# define LEX_H

# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <stdio.h>
# define PIPE '|'
# define SQUOTE '\''
# define DQUOTE '\"'
# define SEMICOLON ';'
# define GREATER '>'
# define GGREATER 1240
# define LESSER	'<'
# define DASH	'-'
# define WHITESPACE ' '
# define WORD -1

typedef struct s_tokens t_tokens;

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
	int			error;
}				t_lex;

int				destroy_structs(t_lex *lex, t_lexpar *par);
void			start_tokens(t_tokens *tok, int length);
int				destroy_tokens(t_tokens* tok);
void			start_lexpar(t_lexpar *par, int textsize);
void			start_lexer(t_lex* lex);
int				lexer(char *text, t_lex *lex, int textsize); 

#endif
