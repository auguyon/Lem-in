/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:47:57 by auguyon           #+#    #+#             */
/*   Updated: 2019/11/12 22:50:38 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

void	btree_apply_postfix_lr(t_btree *root, void (*applyf)(t_btree *))
{
	if (root && applyf)
	{
		if (root->left)
			btree_apply_postfix_lr(root->left, applyf);
		if (root->right)
			btree_apply_postfix_lr(root->right, applyf);
		if (root)
			applyf(root);
	}
}

t_btree	*btree_search(t_btree *groot, char *find)
{
	if (groot == NULL)
		return (NULL);
	if (ft_strcmp(groot->name, find) > 0)
		return (btree_search(groot->left, find));
	else if (ft_strcmp(groot->name, find) < 0)
		return (btree_search(groot->right, find));
	return (groot);
}
