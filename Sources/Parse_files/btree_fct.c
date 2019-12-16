/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Aurelien <Aurelien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:47:57 by auguyon           #+#    #+#             */
/*   Updated: 2019/12/15 19:16:17 by Aurelien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

int			btree_search_name(t_btree *groot, int *j, char *find)
{
	if (groot)
	{
		if (groot->left)
			btree_search_name(groot->left, j, find);
		if (groot)
			if (ft_strcmp(groot->name, find) == 0)
				*(j) = 1;
		if (groot->right)
			btree_search_name(groot->right, j, find);
	}
	return (1);
}

static int	cmp_int(int cmp_a, int cmp_b, int a, int b)
{
	if (cmp_a == a && cmp_b == b)
		return (0);
	return (1);
}

int			btree_search_pos(t_btree *groot, int *j, int x, int y)
{
	if (groot)
	{
		if (groot->left)
			btree_search_pos(groot->left, j, x, y);
		if (groot)
			if (!(cmp_int(groot->x, groot->y, x, y)))
				*(j) = 1;
		if (groot->right)
			btree_search_pos(groot->right, j, x, y);
	}
	return (1);
}
