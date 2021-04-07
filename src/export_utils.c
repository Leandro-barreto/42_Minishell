/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lborges- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:03:49 by lborges-          #+#    #+#             */
/*   Updated: 2020/01/21 19:04:33 by lborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(char *var)
{
	int	writer;
	int	reader;

	writer = 0;
	reader = 0;
	while (var[reader])
	{
		if (var[reader] != '\'' && var[reader] != '\"')
			var[writer++] = var[reader];
		reader++;
	}
	var[writer] = 0;
	return (var);
}
