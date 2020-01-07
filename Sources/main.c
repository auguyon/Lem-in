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

t_data		*parser(void)
{
	t_data	 *dt;
	t_info	 *info;
	t_btree	*groot;

	init_struct_parse(&dt, &info);
	groot = parse_room(info, 0);
	parse_link(info, groot);
	check_error(info, groot);
	btree_to_data(groot, info, dt);
	free_btree_n_info(info, groot);
	return (dt);
}

void		print_truc(t_data *dt)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < dt->nb_rooms && !(j = 0))
	{
		printf("Salle->%d Name->%s Nbr de nbs->%d\n", i, dt->name[i], dt->nbr[i]);
		while(dt->tab[i][j] != -1)
			printf("->%d ", dt->tab[i][j++]);
		printf("\n");
		i++;
	}
	exit (0);
}

int		 main(int argc, char **argv)
{
	t_data	 *dt;

	(void)argc;
	(void)argv;
	dt = parser();
	printf("\nSolver\n");
	solver(dt);
	// while(1);
	return (0);
}
