/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoreira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:12:04 by dmoreira          #+#    #+#             */
/*   Updated: 2020/02/07 20:58:27 by dmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2, int fre)
{
	int		k;
	char	*newstr;
	int		i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	k = ft_strlen(s1) + ft_strlen(s2);
	newstr = (char *)malloc((k + 1) * sizeof(*newstr));
	if (!newstr)
		return (NULL);
	i = 0;
	while (*s1)
	{
		newstr[i++] = *s1;
		s1++;
	}
	while (*s2)
		newstr[i++] = *(s2++);
	newstr[i] = '\0';
	if (fre == 1 || fre == 3)
		free(s1);
	if (fre == 2 || fre == 3)
		free(s2);
	return (newstr);
}
