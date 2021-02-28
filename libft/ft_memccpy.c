/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lborges- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 12:06:46 by lborges-          #+#    #+#             */
/*   Updated: 2020/01/31 15:58:54 by lborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*n_dst;
	const unsigned char	*n_src;

	n_dst = (unsigned char *)dst;
	n_src = (const unsigned char *)src;
	while (n)
	{
		if (*n_src == (unsigned char)c)
		{
			*n_dst = *n_src;
			return (n_dst + 1);
		}
		*n_dst++ = *n_src++;
		n--;
	}
	return (NULL);
}
