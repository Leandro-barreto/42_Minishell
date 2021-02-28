/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lborges- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 17:57:01 by lborges-          #+#    #+#             */
/*   Updated: 2020/01/22 18:22:20 by lborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;
	char	c;

	nb = n;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb *= -1;
	}
	if (nb > 10)
	{
		ft_putnbr_fd(nb / 10, fd);
		c = nb % 10 + '0';
		ft_putchar_fd(c, fd);
	}
	else
	{
		c = nb + '0';
		ft_putchar_fd(c, fd);
	}
}
