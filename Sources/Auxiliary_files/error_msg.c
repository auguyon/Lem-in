/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <ftrujill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:47:57 by auguyon           #+#    #+#             */
/*   Updated: 2020/01/15 18:33:43 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

void	print_error(short error)
{
	write(1, "\033[31mError:\n", 13);
	if (error == -1)
		write(1, "\tNo X or Y for room.\n", 21);
	else if (error == -2)
		write(1, "\tRoom has no name.\n", 19);
	else if (error == -3)
		write(1, "\tDash in name is forbidden.\n", 28);
	else if (error == -11)
		write(1, "\tBad files\n", 11);
	else if (error == -6)
		write(1, "\tNo ants\n", 9);
	else if (error == -7)
		write(1, "\tNo start or end\n", 17);
	else if (error == -8)
		write(1, "\tRoom name already used.\n", 25);
	else if (error == -9)
		write(1, "\tX and Y already used.\n", 23);
	else if (error == -10)
		write(1, "\tNo path found.\n", 16);
	else if (error == -4)
		write(1, "\tEmpty line\n", 12);
	else if (error == -5)
		write(1, "\tWrong room name for link\n", 26);
	write(1, "\033[0m", 4);
}

void	check_error(t_info *in, t_btree *groot)
{
	if (in->line == NULL)
	{
		print_error(-11);
		free_btree_n_info(in, groot);
		exit(0);
	}
	else if ((in->error <= -1 && in->error >= -3)
		|| (in->error <= -6 && in->error >= -9))
	{
		print_error(in->error);
		free_btree_n_info(in, groot);
		exit(0);
	}
	else if (!in->adr_start || !in->adr_end)
	{
		print_error(-7);
		free_btree_n_info(in, groot);
		exit(0);
	}
}
