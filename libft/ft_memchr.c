/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lborges- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 12:56:14 by lborges-          #+#    #+#             */
/*   Updated: 2020/01/30 16:35:36 by lborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int			index;
	const char	*new_s;

	new_s = s;
	index = -1;
	while (n--)
	{
		index++;
		if (*new_s++ == c)
			return ((void *)s + index);
	}
	return (NULL);
}
