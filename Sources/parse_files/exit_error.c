/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:47:57 by auguyon           #+#    #+#             */
/*   Updated: 2019/11/12 22:50:38 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

static void	print_error(short error)
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
		write(1, "\tNo path found.\n", 16);
	write(1, "\033[0m", 4);
}

void		free_btree_n_link(t_btree *groot)
{
	t_link 	*tmp;


	printf("\nFree branch {%s}\n", groot->name);
	tmp = groot->link;
	if (groot->link)
	{
		while (groot->link->next != NULL)
		{
			printf("free maiilon\n");
			tmp = groot->link->next;
			free(groot->link);
			groot->link = tmp;
		}
		free(groot->link);
	}
	free(groot->name);
	free(groot);
	printf("%s\n", "Fin des free");
}

void	btree_apply_postfix(t_btree *root)
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

static void	exit_error(t_info *info, t_btree *groot, short error)
{
	print_error(error);
	btree_apply_postfix(groot);
	free(info->parse);
	free(info);
	while (1);
	exit (0);
}

void		check_error(t_info *info, t_btree *groot, short error)
{
	// if ((error <= -1 && error >= -3) || (error <= -6 && error >= -8))
		exit_error(info, groot, error);
	// else if (!info->adr_start || !info->adr_end)
	// 	exit_error(info, groot, line, -7);
}