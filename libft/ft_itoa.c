/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lborges- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 18:22:52 by lborges-          #+#    #+#             */
/*   Updated: 2020/01/27 11:05:12 by lborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	checkdigits(long nb)
{
	int		digits;

	digits = 0;
	while (nb > 0)
	{
		digits++;
		nb = nb / 10;
	}
	return (digits);
}

static char	*nzero(void)
{
	char	*str;

	str = (char *)malloc(2 * sizeof(*str));
	if (!str)
		return (NULL);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

char		*ft_itoa(int n)
{
	long	nb;
	char	*str;
	int		digits;
	int		sign;

	if (n == 0)
		return (nzero());
	nb = n;
	sign = (nb < 0) ? 1 : 0;
	nb = (sign) ? nb * -1 : nb;
	digits = checkdigits(nb);
	str = (char *)malloc((digits + 1 + sign) * sizeof(*str));
	if (!str)
		return (NULL);
	str[digits + sign] = '\0';
	digits--;
	while (nb > 0)
	{
		str[digits + sign] = nb % 10 + '0';
		digits--;
		nb /= 10;
	}
	if (sign)
		str[0] = '-';
	return (str);
}
