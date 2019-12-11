/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:47:57 by auguyon           #+#    #+#             */
/*   Updated: 2019/12/10 23:12:13 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

void			print_error(short error)
{
	write(1, "\033[31mError:\n", 13);
	if (error == -1)
		write(1, "\tNo X or Y for room.\n", 21);
	else if (error == -2)
		write(1, "\tRoom has no name.\n", 19);
	else if (error == -3)
		write(1, "\tDash in name has forbidden.\n", 29);
	else if (error == -4)
		write(1, "\tEmpty line\n", 12);
	else if (error == -5)
		write(1, "\tWrong room's name for link\n", 28);
	else if (error == -6)
		write(1, "\tNo ants\n", 9);
	else if (error == -7)
		write(1, "\tNo start or end\n", 17);
	else if (error == -8)
		write(1, "\tName's room already used.\n", 27);
	else if (error == -9)
		write(1, "\tX or Y already used.\n", 22);
	else if (error == -10)
		write(1, "\tNo path found.\n", 16);
	write(1, "\033[0m", 4);
}

static void		free_btree_n_link(t_btree *groot)
{
	t_link	*tmp;

	tmp = groot->link;
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

void			free_btree_n_info(t_info *info, t_btree *groot)
{
	btree_apply_postfix(groot);
	free(info);
}
