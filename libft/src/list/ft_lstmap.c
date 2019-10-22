/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 14:11:47 by auguyon           #+#    #+#             */
/*   Updated: 2018/11/23 12:14:32 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*dup;
	t_list	*tmp;
	t_list	*elem;

	if (!lst || !f)
		return (0);
	elem = f(lst);
	dup = ft_lstnew(elem->content, elem->content_size);
	tmp = dup;
	lst = lst->next;
	while (lst)
	{
		elem = f(lst);
		tmp->next = ft_lstnew(elem->content, elem->content_size);
		lst = lst->next;
		tmp = tmp->next;
	}
	return (dup);
}
