/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lborges- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 18:32:06 by lborges-          #+#    #+#             */
/*   Updated: 2020/01/31 18:46:24 by lborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*n_s1;
	const unsigned char	*n_s2;

	n_s1 = s1;
	n_s2 = s2;
	if (n == 0)
		return (0);
	while (--n && *n_s1 == *n_s2)
	{
		n_s1++;
		n_s2++;
	}
	return (*n_s1 - *n_s2);
}
