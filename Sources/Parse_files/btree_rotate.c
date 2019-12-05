/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:47:57 by auguyon           #+#    #+#             */
/*   Updated: 2019/11/12 22:50:38 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

int				height(t_btree *n)
{
	if (n == NULL)
		return (0);
	return (n->height);
}

static int		get_balance(t_btree *n)
{
	if (n == NULL)
		return (0);
	return (height(n->left) - height(n->right));
}

static t_btree	*right_rotate(t_btree *t)
{
	t_btree	*tmp_l;
	t_btree	*tmp;

	tmp_l = t->left;
	tmp = tmp_l->right;
	tmp_l->right = t;
	t->left = tmp;
	t->height = ft_max(height(t->left), height(t->right)) + 1;
	tmp_l->height = ft_max(height(tmp_l->left), height(tmp_l->right)) + 1;
	return (tmp_l);
}

static t_btree	*left_rotate(t_btree *t)
{
	t_btree	*tmp_r;
	t_btree	*tmp;

	tmp_r = t->right;
	tmp = tmp_r->left;
	tmp_r->left = t;
	t->right = tmp;
	t->height = ft_max(height(t->left), height(t->right)) + 1;
	tmp_r->height = ft_max(height(tmp_r->left), height(tmp_r->right)) + 1;
	return (tmp_r);
}

t_btree			*btree_rotate(t_btree *t, char *name)
{
	int	balance;

	balance = get_balance(t);
	if (balance > 1 && ft_strcmp(t->left->name, name) > 0)
		return (right_rotate(t));
	else if (balance < -1 && ft_strcmp(t->right->name, name) < 0)
		return (left_rotate(t));
	else if (balance > 1 && ft_strcmp(t->left->name, name) < 0)
	{
		t->left = left_rotate(t->left);
		return (right_rotate(t));
	}
	else if (balance < -1 && ft_strcmp(t->right->name, name) > 0)
	{
		t->right = right_rotate(t->right);
		return (left_rotate(t));
	}
	return (t);
}
