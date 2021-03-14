/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoreira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 18:35:38 by dmoreira          #+#    #+#             */
/*   Updated: 2020/02/13 18:51:13 by dmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int letra)
{
	if (letra >= 48 && letra <= 57)
	{
		return (1);
	}
	return (0);
}