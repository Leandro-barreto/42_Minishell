/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lborges- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 17:12:28 by lborges-          #+#    #+#             */
/*   Updated: 2020/01/30 16:51:49 by lborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t destsize)
{
	size_t	i;
	size_t	d_len;
	size_t	s_len;

	i = 0;
	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	if (destsize < d_len)
		return (s_len + destsize);
	while (src[i] && ((d_len + i + 1) < destsize))
	{
		dst[d_len + i] = ((char *)src)[i];
		i++;
	}
	dst[d_len + i] = '\0';
	return (s_len + d_len);
}
