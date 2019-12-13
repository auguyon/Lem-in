/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Aurelien <Aurelien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:47:57 by auguyon           #+#    #+#             */
/*   Updated: 2019/12/13 21:41:32 by Aurelien         ###   ########.fr       */
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
		write(1, "\tDash in name is forbidden.\n", 28);
	else if (error == -4)
		write(1, "\tEmpty line\n", 12);
	else if (error == -5)
		write(1, "\tWrong room name for link\n", 26);
	else if (error == -6)
		write(1, "\tNo ants\n", 9);
	else if (error == -7)
		write(1, "\tNo start or end\n", 17);
	else if (error == -8)
		write(1, "\tRoom name already used.\n", 25);
	else if (error == -9)
		write(1, "\tX or Y already used.\n", 22);
	else if (error == -10)
		write(1, "\tNo path found.\n", 16);
	write(1, "\033[0m", 4);
}