/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:47:57 by auguyon           #+#    #+#             */
/*   Updated: 2020/01/03 15:52:12 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/lemin.h"

t_data	*parser(int fd)
{
	t_data	*dt;
	t_info	*info;
	t_btree	*groot;

	init_struct_parse(&dt, &info);
	groot = parse_room(fd, info, 0);
	parse_link(fd, info, groot);
	check_error(info, groot);
	btree_to_data(groot, info, dt);
	free_btree_n_info(info, groot);
	return (dt);
}

int		main(int ac, char **av)
{
	t_data	*dt;
	int		i;
	int		fd;

	i = 1;
	while (i <= ac)
	{
		if (ac > 1)
			fd = open(av[i], O_RDONLY);
		else
			fd = 0;
		i++;
		dt = parser(fd);
		solver(dt);
	}
	return (0);
}
