/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:47:57 by auguyon           #+#    #+#             */
/*   Updated: 2020/01/10 15:47:17 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/lemin.h"

static void	print_map(t_map *map)
{
	while (map->next != NULL)
	{
		ft_putendl(map->line);
		map = map->next;
	}
	ft_putendl(map->line);
}

t_data	*parser(int fd)
{
	t_data	*dt;
	t_info	*info;
	t_btree	*groot;

	init_struct_parse(&dt, &info);
	groot = parse_room(fd, info, 0);
	parse_link(fd, info, groot);
	check_error(info, groot);
	btree_to_data(groot, info, dt, 1);
	print_map(info->map_start);
	free_btree_n_info(info, groot);
	return (dt);
}

int		main(int ac, char **av)
{
	t_data	*dt;
	int		fd;
	int		i;

	i = 1;
	fd = 0;
	while (i <= ac)
	{
		if (ac > 1)
			if ((fd = open(av[i], O_RDONLY)) < 3)
				return (0);
		i++;
		dt = parser(fd);
		solver(dt);
	}
	return (0);
}
