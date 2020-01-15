/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_btree_n_info.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <ftrujill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:47:57 by auguyon           #+#    #+#             */
/*   Updated: 2020/01/15 18:37:43 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

static void		free_btree_n_link(t_btree *groot)
{
	t_link	*tmp;

	if (groot->link)
	{
		while (groot->link->next != NULL)
		{
			tmp = groot->link->next;
			free(groot->link);
			groot->link = tmp;
		}
		free(groot->link);
	}
	free(groot->name);
	free(groot);
}

static void		btree_apply_postfix(t_btree *root)
{
	if (root)
	{
		if (root->left)
			btree_apply_postfix(root->left);
		if (root->right)
			btree_apply_postfix(root->right);
		if (root)
			free_btree_n_link(root);
	}
}

static void		free_info(t_info *info)
{
	t_map *tmp;

	if (info->map)
	{
		while (info->map->next != NULL)
		{
			tmp = info->map->next;
			free(info->map->line);
			free(info->map);
			info->map = tmp;
		}
		free(info->map->line);
		free(info->map);
	}
	free(info);
}

void			free_btree_n_info(t_info *info, t_btree *groot)
{
	btree_apply_postfix(groot);
	free_info(info);
}
