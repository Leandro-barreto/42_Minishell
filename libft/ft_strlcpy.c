/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lborges- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 18:23:08 by lborges-          #+#    #+#             */
/*   Updated: 2020/01/31 18:23:43 by lborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	source_size;
	size_t	i;

	if (!dest)
		return (0);
	source_size = ft_strlen((char *)src);
	i = 0;
	if (!dstsize)
		return (source_size);
	while ((src[i] != '\0') && (i < dstsize - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (source_size);
}
