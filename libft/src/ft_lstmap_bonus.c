/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 07:47:30 by malja-fa          #+#    #+#             */
/*   Updated: 2024/09/01 07:47:31 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	q_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		new->next = NULL;
	}
	else
	{
		last = *lst;
		while (last->next != NULL)
		{
			last = last->next;
		}
		last->next = new;
		new->next = NULL;
	}
}

static void	q_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;
	t_list	*temp;

	if (!lst || !*lst)
		return ;
	ptr = *lst;
	while (ptr != NULL)
	{
		temp = ptr->next;
		del(ptr->content);
		free(ptr);
		ptr = temp;
	}
	*lst = NULL;
}

static t_list	*q_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ptr;
	t_list	*p;
	void	*temp;

	if (!lst || !f)
		return (NULL);
	ptr = NULL;
	while (lst)
	{
		temp = f(lst->content);
		p = q_lstnew(temp);
		if (!p)
		{
			if (temp)
				del(temp);
			q_lstclear(&ptr, del);
			return (NULL);
		}
		q_lstadd_back(&ptr, p);
		lst = lst->next;
	}
	return (ptr);
}
