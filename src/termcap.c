#include "minishell.h"

int	get_input_user(char **history)
{
	char	buffer[3];
	int		send_line;
	int		present;

	present = write_cmd(history, 0, 1);
	g_global.line = ft_calloc(sizeof(char), 2);
	send_line = 0;
	while (send_line == 0)
	{
		ft_bzero(buffer, 3);
		read(0, &buffer, 3);
		if (buffer[0] == EOT && g_global.line[0] == '\0')
			ft_exit(NULL, NULL, 1);
		send_line = handle_event(buffer, history, &present);
	}
	return (1);
}

void	init_terminal(void)
{
	struct termios	term;
	char			*termtype;

	termtype = ft_strdup("xterm-256color");
	ft_bzero(&term, sizeof(struct termios));
	g_global.save = ft_calloc(1, sizeof(struct termios));
	tgetent(NULL, termtype);
	tcgetattr(STDIN_FILENO, &term);
	ft_memcpy(g_global.save, &term, sizeof(term));
	term.c_lflag &= ~(ECHO | ICANON);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
	free(termtype);
}

int	read_line(char **history)
{	
	write(1, "$mini> ", 7);
	init_terminal();
	if (get_input_user(history) == 0 && g_global.save)
		return (0);
	return (1);
}
