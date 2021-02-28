/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lborges- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 12:39:07 by lborges-          #+#    #+#             */
/*   Updated: 2020/01/31 16:03:43 by lborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	const char	*aux1;
	char		*aux2;
	size_t		i;

	if (!dst && !src)
		return (NULL);
	aux1 = src;
	aux2 = dst;
	i = 0;
	if (aux2 > aux1)
	{
		i = n;
		while (i > 0)
		{
			aux2[i - 1] = aux1[i - 1];
			i--;
		}
	}
	else
		while (i < n)
		{
			aux2[i] = aux1[i];
			i++;
		}
	return (dst);
}
