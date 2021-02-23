/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lborges- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 19:14:42 by lborges-          #+#    #+#             */
/*   Updated: 2020/02/01 10:43:29 by lborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*needle)
		return ((char *)haystack);
	i = 0;
	j = 0;
	while (haystack[i] && i < len)
	{
		while (haystack[i] == needle[j] && i < len)
		{
			i++;
			j++;
			if (!needle[j])
				return ((char *)&haystack[i - j]);
			if (haystack[i] != needle[j])
				j = 0;
		}
		i++;
	}
	return (NULL);
}
