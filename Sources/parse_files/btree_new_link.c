/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_new_link.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:47:57 by auguyon           #+#    #+#             */
/*   Updated: 2019/11/12 22:50:38 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

static void	put_link(t_btree **adr_room, t_link **link, char *room) // ne pas faire de doublon
{
	t_link	*new;
	t_link	*current;

	current = *link;
	if (!(new = (t_link*)malloc(sizeof(t_link))))
		exit(0);
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
	printf("on ajoute{%s} {%s}\n", room, (*adr_room)->name);
}

void	btree_add_data(t_btree *start, t_btree *groot, char *find, char *room)
{
	static	t_btree *branch;
	static	short i = 0;

	if (groot == NULL)
		return ;
	if (ft_strcmp(groot->name, find) > 0)
		return (btree_add_data(start, groot->left, find, room));
	else if (ft_strcmp(groot->name, find) < 0)
		return (btree_add_data(start, groot->right, find, room));
	else
	{
		if (i == 0)
		{
			branch = groot;
			i = 1;
			return (btree_add_data(start, start, room, find));
		}
		else
		{
			printf("a -> %s\n", groot->name);
			put_link(&branch, &groot->link, room);
			printf("a -> %s\n", branch->name);
			put_link(&groot, &branch->link, find);
			i = 0;
		}
	}
}

void	get_info_link(t_parse *parse, char *line)
{
	int	i;

	i = ft_strclen(line, '-');
	// if (parse->f_room)
	// 	free(parse->f_room);
	// if (parse->s_room)
	// 	free(parse->s_room);
	parse->f_room = ft_strndup(line, i);
	parse->s_room = ft_strdup(line + i + 1);
}
