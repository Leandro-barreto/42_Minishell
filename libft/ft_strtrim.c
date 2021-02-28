/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lborges- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 14:58:23 by lborges-          #+#    #+#             */
/*   Updated: 2020/01/28 13:52:07 by lborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s1, char const *set)
{
	size_t		l;
	char const	*begin;
	char const	*end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	l = 0;
	begin = s1;
	end = s1 + (ft_strlen(s1) - 1);
	while (*(set + l) && (begin <= end))
	{
		if (*begin == *(set + l) || *end == *(set + l))
		{
			if (*begin == *(set + l))
				begin++;
			if (*end == *(set + l))
				end--;
			l = 0;
		}
		else
			l++;
	}
	while (begin + l <= end)
		l++;
	return (ft_substr(begin, 0, l));
}
