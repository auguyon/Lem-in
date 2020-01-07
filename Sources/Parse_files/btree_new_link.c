/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_new_link.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:47:57 by auguyon           #+#    #+#             */
/*   Updated: 2020/01/03 15:50:01 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

static void	put_link(t_btree **adr_room, t_link **link)
{
	t_link	*new;
	t_link	*current;

	current = *link;
	if (!(new = (t_link*)malloc(sizeof(t_link))))
		ft_malloc_error();
	ft_bzero(new, sizeof(t_link));
	new->adr = *adr_room;
	new->name = (*adr_room)->name;
	new->next = NULL;
	if (link == NULL || *link == NULL)
		*link = new;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

void		btree_add_link(t_btree *start, t_btree *groot, char *f, char *room)
{
	static t_btree	*branch;
	static short	i = 0;

	if (groot == NULL)
		return ;
	if (ft_strcmp(groot->name, f) > 0)
		return (btree_add_link(start, groot->left, f, room));
	else if (ft_strcmp(groot->name, f) < 0)
		return (btree_add_link(start, groot->right, f, room));
	else
	{
		if (i == 0)
		{
			branch = groot;
			i = 1;
			return (btree_add_link(start, start, room, f));
		}
		else
		{
			put_link(&branch, &groot->link);
			put_link(&groot, &branch->link);
			i = 0;
		}
	}
}
