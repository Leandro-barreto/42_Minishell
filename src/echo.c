/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lborges- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:03:49 by lborges-          #+#    #+#             */
/*   Updated: 2020/01/21 19:04:33 by lborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	writeecho(char *text)
{
	int	i;
	int size;

	size = ft_strlen(text);
	i = 0;
	if ((size > 1) && ((text[0] == '\'' && text[size - 1] == '\'') ||
				(text[0] == '\"' && text[size - 1] == '\"')))
	{
		i++;
		size--;
	}
	while (i < size)
	{
		if (text[i] != '\\')
			write(1, &text[i], 1);
		if (text[i] == '\\' && text[0] == '\'')
			write(1, &text[i], 1);
		if (text[i] == '\\' && text[0] == '\"' && text[i + 1] != '$'
				&& text[i + 1] != '\"' && text[i + 1] != '\'')
			write(1, &text[i], 1);
		i++;
	}
}

int		miniecho(t_simplecmd *scmd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while ((i <= scmd->nargs) && !(ft_strncmp(scmd->args[i], "-n", 2)))
	{
		i++;
		flag++;
	}
	printf("nargs: %i\n", scmd->nargs);
	while (i <= scmd->nargs)
	{
		writeecho(scmd->args[i]);
		if (i < scmd->nargs)
			write(1, " ", 1);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
	return (0);
}
