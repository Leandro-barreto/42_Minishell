/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoreira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 11:10:59 by dmoreira          #+#    #+#             */
/*   Updated: 2020/02/07 18:23:14 by dmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*alocador(int n, int cont)
{
	int		vetor[2];
	char	*ptr;

	vetor[0] = n;
	vetor[1] = n;
	ptr = (char *)ft_calloc(cont + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	if (n < 0)
	{
		ptr[0] = '-';
		while (--cont)
		{
			vetor[0] = vetor[1] / 10;
			ptr[cont] = 48 + (-vetor[1] + (vetor[0] * 10));
			vetor[1] = vetor[1] / 10;
		}
	}
	while (n >= 0 && --cont >= 0)
	{
		vetor[0] = vetor[1] / 10;
		ptr[cont] = 48 + (vetor[1] - (vetor[0] * 10));
		vetor[1] = vetor[1] / 10;
	}
	return (ptr);
}

char	*ft_itoa(int n)
{
	int		cont;
	int		numb;
	char	*aux;

	numb = n;
	cont = 0;
	if (n == 0)
	{
		aux = malloc((2 * sizeof(char *)));
		aux[0] = '0';
		aux[1] = 0;
		return (aux);
	}
	while (numb != 0 && ++cont)
		numb = numb / 10;
	if (n < 0)
		++cont;
	return (alocador(n, cont));
}
