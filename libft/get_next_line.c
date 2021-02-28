/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lborges- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 09:59:55 by lborges-          #+#    #+#             */
/*   Updated: 2020/02/06 16:09:42 by lborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_calloc(size_t count, size_t size)
{
	char	*p;
	int		len;
	int		i;

	i = 0;
	p = (char *)malloc(count * size);
	len = count * size;
	if (!p)
		return (NULL);
	while (len)
	{
		*(p + i) = 0;
		i++;
		len--;
	}
	return (p);
}

void	ft_delstr(char **c)
{
	if (c != NULL)
	{
		free(*c);
		*c = NULL;
	}
}

int		copy_line(char **line, char **s, int fd)
{
	int		i;
	char	*aux;

	i = 0;
	while (s[fd][i] != '\n' && s[fd][i] != '\0')
		i++;
	if (s[fd][i] == '\n')
	{
		*line = ft_substr(s[fd], 0, i);
		aux = ft_strdup(&s[fd][i + 1]);
		free(s[fd]);
		s[fd] = aux;
		if (s[fd][0] == '\0')
			ft_delstr(&s[fd]);
	}
	else
	{
		*line = ft_strdup(s[fd]);
		ft_delstr(&s[fd]);
		return (0);
	}
	return (1);
}

int		check_read(int ret, char **line, char **s, int fd)
{
	if (ret < 0)
		return (-1);
	if (ret == 0 && s[fd] == NULL)
	{
		*line = ft_calloc(1, 1);
		return (0);
	}
	return (copy_line(line, s, fd));
}

int		get_next_line(int fd, char **line)
{
	char		*buff;
	static char	*s[10];
	char		*aux;
	int			ret;

	if (fd < 0 || line == NULL || BUFFER_SIZE < 1 || read(fd, NULL, 0) < 0)
		return (-1);
	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(*buff));
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (s[fd] == NULL)
			s[fd] = ft_strdup(buff);
		else
		{
			aux = ft_strjoin(s[fd], buff);
			free(s[fd]);
			s[fd] = aux;
		}
		if (ft_strchr(s[fd], '\n'))
			break ;
	}
	ft_delstr(&buff);
	return (check_read(ret, line, s, fd));
}
