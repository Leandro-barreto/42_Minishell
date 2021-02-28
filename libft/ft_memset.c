/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lborges- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 11:19:30 by lborges-          #+#    #+#             */
/*   Updated: 2020/01/31 15:59:18 by lborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*aux;
	unsigned char	ca;

	ca = (unsigned char)c;
	aux = (unsigned char *)b;
	while (len)
	{
		*aux = ca;
		aux++;
		len--;
	}
	return (b);
}
