/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:47:57 by auguyon           #+#    #+#             */
/*   Updated: 2019/12/05 22:16:29 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/lemin.h"

void		solver(t_data *dt)
{
	t_layer		*layer;
    t_solution	*solution;
    t_path		**possible;
	int			nbr_steps;
	int			sol;

    init_struct_algo(&solution, &possible, dt->nb_rooms);
    initialize(&layer, dt->nb_rooms);
    prt_g(dt);
    while (mbfs(dt, solution, layer, possible))
    {
    }
    prt_possible(possible);
    find_solution(possible, dt->ants, &nbr_steps, &sol);
    ft_printf("\nAnd the right solution with %d ants is the one with %d path(s) and it takes %d step(s)\n\n", dt->ants, sol + 1, nbr_steps);
	prt_steps(possible, dt->ants, nbr_steps, sol);

}

t_data		*parser(void)
{
	t_data		*dt;
	t_info		*info;
	t_btree		*groot;

    init_struct_parse(&dt, &info);
	groot = parse_room(info);
	parse_link(info, groot, info->error);
	check_error(info, groot, info->error);
    btree_to_data(groot, info, dt);
	free_btree_n_info(groot, info);
	return (dt);
}

int         main(int argc, char **argv)
{
    t_data		*dt;

	dt = parser();
	solver(dt);
    return (0);
}
