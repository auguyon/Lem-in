/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Aurelien <Aurelien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:47:57 by auguyon           #+#    #+#             */
/*   Updated: 2019/12/15 19:11:52 by Aurelien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/lemin.h"

int         solver_2(t_data *dt, t_solution *solution, t_path **possible)
{
    int *path_nbrs;
    int *ant_first;

    possible[0] = NULL;
    while (mbfs(dt, solution, possible))
    {
    }
    solution->nbr_paths = 0;
    solution->nbr_ants = dt->ants;
    solution->nbr_steps = dt->ants + possible[0][0].depth - 2;
    order_possible(possible);
    //prt_possible(possible);
    find_solution(possible, solution);
    path_nbrs = path_numbers(possible, solution);
    ant_first = ant_first_app(possible, solution);
    dt->nbr_steps = solution->nbr_steps;
    dt->nbr_paths = solution->nbr_paths;
    prt_steps(dt, possible, path_nbrs, ant_first);
    ft_printf("\nAnd the right solution with %d ants is the one with %d "
        "path(s) and it takes %d step(s)\n\n", dt->ants,
        solution->nbr_paths + 1, solution->nbr_steps);
    free(path_nbrs);
    free(ant_first);
    free_all(dt, solution, possible);
        // free_layer(&layer);
    return (0);
}

int         solver(t_data *dt)
{
    int         i;
    int         size;
    t_solution  *solution;
    t_path      **possible;

    size = dt->nb_rooms;
    if (is_trivial(dt))
        return (0);
    if (!(solution = (t_solution*)malloc(sizeof(t_solution)))
        || !(solution->used_vertices = (int**)malloc(size * sizeof(int*)))
        || !(solution->paths = (t_path*)malloc(size * sizeof(t_path)))
        || !(possible = (t_path**)malloc(size * sizeof(t_path*))))
        ft_malloc_error();
    i = 0;
    while (i < size)
    {
        if (!(solution->used_vertices[i] = (int*)malloc(3 * sizeof(int))))
            ft_malloc_error();
        solution->used_vertices[i++][0] = 0;
    }
    solution->max_length = 0;
    solution->nbr_paths = 0;
    solution->size = size;   
    return (solver_2(dt, solution, possible));
}


t_data		*parser(void)
{
	t_data		*dt;
	t_info		*info;
	t_btree		*groot;

    init_struct_parse(&dt, &info);
	groot = parse_room(info, 0);
	parse_link(info, groot);
	check_error(info, groot);
    btree_to_data(groot, info, dt);
	free_btree_n_info(info, groot);
	return (dt);
}

void        print_truc(t_data *dt)
{
    int i;
    int j;

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

int         main(int argc, char **argv)
{
    t_data		*dt;

	dt = parser();
	solver(dt);
    while(1);
    return (0);
}
