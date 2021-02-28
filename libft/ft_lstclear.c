/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lborges- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 11:43:49 by lborges-          #+#    #+#             */
/*   Updated: 2020/01/27 12:14:47 by lborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*aux;

	if (!lst)
		return ;
	temp = *lst;
	while (temp)
	{
		aux = temp->next;
		del(temp->content);
		free(temp);
		temp = aux;
	}
	*lst = NULL;
}
