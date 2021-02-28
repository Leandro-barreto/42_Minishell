/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lborges- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:09:56 by lborges-          #+#    #+#             */
/*   Updated: 2020/01/28 13:36:37 by lborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*aux;
	char			*newstr;
	int				k;
	unsigned int	i;

	if (!f || !s)
		return (NULL);
	aux = (char *)s;
	k = ft_strlen((char *)s);
	newstr = (char *)malloc((k + 1) * sizeof(*newstr));
	if (!newstr)
		return (0);
	i = 0;
	while (*aux)
	{
		*(newstr + i) = f(i, *aux);
		aux++;
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
