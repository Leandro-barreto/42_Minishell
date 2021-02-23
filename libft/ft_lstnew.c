/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lborges- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:52:16 by lborges-          #+#    #+#             */
/*   Updated: 2020/01/24 12:23:54 by lborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*root;

	root = (t_list *)malloc(sizeof(t_list) * sizeof(content));
	if (!root)
		return (NULL);
	if (!content)
	{
		root->content = NULL;
		root->next = NULL;
		return (root);
	}
	root->content = (void *)malloc(sizeof(content));
	if (!(root->content))
		return (NULL);
	root->content = content;
	root->next = NULL;
	return (root);
}
