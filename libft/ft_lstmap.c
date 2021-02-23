/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lborges- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:19:54 by lborges-          #+#    #+#             */
/*   Updated: 2020/01/28 16:38:13 by lborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_lstnew1(void *content)
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

static void		ft_lstclear1(t_list **lst, void (*del)(void*))
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

t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*new_fixed;

	if (!lst)
		return (NULL);
	new = ft_lstnew1(f(lst->content));
	if (!new)
		return (NULL);
	new_fixed = new;
	while (lst)
	{
		if (lst->next)
		{
			new->next = ft_lstnew1(f(lst->next->content));
			if (!(new->next))
			{
				ft_lstclear1(&lst, del);
				return (0);
			}
			new = new->next;
		}
		lst = lst->next;
	}
	new->next = NULL;
	return (new_fixed);
}
