/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_to_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:47:57 by auguyon           #+#    #+#             */
/*   Updated: 2019/12/12 00:09:14 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

static void		fill_data(t_btree *groot, t_data *dt)
{
	t_btree		*branch;
	t_link		*link;


	dt->nbr[groot->nb] = 0;
	link = groot->link;
	branch = link->adr;
	while (link)
	{
		dt->tab[groot->nb][dt->nbr[groot->nb]] = branch->nb;
		dt->nbr[groot->nb] += 1;
		link = link->next;
		if (link)
			branch = link->adr;
	}
}

static void		count_link(t_btree *groot, int *count)
{
	t_link		*tmp;

	*(count) = 0;
	tmp = groot->link;
	while (tmp)
	{
		*(count) += 1;
		tmp = tmp->next;
	}
}

static void		btree_prefix_data(t_btree *g, t_data *dt)
{
	if (g)
	{
		count_link(g, &dt->nbr[g->nb]);
		if (!(dt->tab[g->nb] = (int*)malloc(sizeof(int) * dt->nbr[g->nb] + 1)))
			ft_malloc_error();
		ft_fill_nb(dt->tab[g->nb], -1, dt->nbr[g->nb] + 1);
		dt->x[g->nb] = g->x;
		dt->y[g->nb] = g->y;
		dt->name[g->nb] = ft_strdup(g->name);
		if (dt->nbr[g->nb])
			fill_data(g, dt);
	}
	if (g->left)
		btree_prefix_data(g->left, dt);
	if (g->right)
		btree_prefix_data(g->right, dt);
}

static void		btree_prefix_count(t_btree *root, t_info *info, int *nb)
{
	if (root && root != info->adr_start && root != info->adr_end)
	{
		root->nb = *(nb);
		*(nb) += 1;
	}
	if (root->left)
		btree_prefix_count(root->left, info, nb);
	if (root->right)
		btree_prefix_count(root->right, info, nb);
}


void			btree_to_data(t_btree *groot, t_info *info, t_data *dt)
{
	int i;

	i = 1;
	dt->nb_rooms = info->rooms;
	dt->ants = info->ants;
	info->adr_start->nb = 0;
	info->adr_end->nb = info->rooms - 1;
	btree_prefix_count(groot, info, &i);
	if (!(dt->tab = (int**)malloc(sizeof(int*) * dt->nb_rooms + 1)))
		ft_malloc_error();
	ft_bzero(dt->tab, sizeof(int*) * dt->nb_rooms + 1);
	if (!(dt->name = (char**)malloc(sizeof(char*) * dt->nb_rooms + 1)))
		ft_malloc_error();
	ft_bzero(dt->name, sizeof(char*) * dt->nb_rooms + 1);
	if (!(dt->x = (int*)malloc(sizeof(int) * dt->nb_rooms + 1)))
		ft_malloc_error();
	ft_fill_nb(dt->x, -1, dt->nb_rooms + 1);
	if (!(dt->y = (int*)malloc(sizeof(int) * dt->nb_rooms + 1)))
		ft_malloc_error();
	ft_fill_nb(dt->y, -1, dt->nb_rooms + 1);
	if (!(dt->nbr = (int*)malloc(sizeof(int) * dt->nb_rooms + 1)))
		ft_malloc_error();
	ft_bzero(dt->nbr, sizeof(int) * dt->nb_rooms + 1);
	btree_prefix_data(groot, dt);
}
