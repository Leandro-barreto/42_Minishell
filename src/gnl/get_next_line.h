/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lborges- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 10:44:48 by lborges-          #+#    #+#             */
/*   Updated: 2020/02/06 11:33:02 by lborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <limits.h>
#include "../libft/libft.h"
# include <limits.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>

int		get_next_line(int fd, char **line);

#endif

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif
