/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 11:02:23 by ftrujill          #+#    #+#             */
/*   Updated: 2019/12/13 22:00:49 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

void        aux_tab(t_path **possible, t_solution *sol,
                    int *tab, int available_paths)
{
    int     i;
    int     j;
    int     ant;

    i = -1;
    ant = 0;
    while (++i < sol->nbr_steps - possible[sol->nbr_paths][0].depth + 2)
    {
        j = -1;
        while (++j < available_paths)
        {
            tab[ant] = i;
            ant++;
            if (ant >= sol->nbr_ants)
                break;
        }
        if (ant >= sol->nbr_ants)
            break;
        j = available_paths;
        while (--j >= 0)
            if (sol->nbr_steps - i < possible[sol->nbr_paths][j].depth)
                available_paths--;
    }
}

int         *ant_first_app(t_path **possible, t_solution *sol)
{
    int     *tab;
    int     available_paths;

    if (!(tab = (int*)malloc(sizeof(int) * sol->nbr_ants)))
        ft_malloc_error();
    available_paths = sol->nbr_paths + 1;
    aux_tab(possible, sol, tab, available_paths);
    return (tab);
}

void        aux_tab_two(t_path **possible, t_solution *sol,
                    int *tab, int available_paths)
{
    int     i;
    int     j;
    int     ant;

    i = -1;
    ant = 0;
    while (++i < sol->nbr_steps - possible[sol->nbr_paths][0].depth + 2)
    {
        j = -1;
        while (++j < available_paths)
        {
            tab[ant] = j % (available_paths);
            ant++;
            if (ant >= sol->nbr_ants)
                break;
        }
        if (ant >= sol->nbr_ants)
            break;
        j = available_paths;
        while (--j >= 0)
            if (sol->nbr_steps - i < possible[sol->nbr_paths][j].depth)
                available_paths--;
    }
}

int         *path_numbers(t_path **possible, t_solution *sol)
{
    int     *tab;
    int     available_paths;

    if (!(tab = (int*)malloc(sizeof(int) * sol->nbr_ants)))
        ft_malloc_error();
    available_paths = sol->nbr_paths + 1;
    aux_tab_two(possible, sol, tab, available_paths);
    return (tab);
}

void        prt_steps(t_data *dt, t_path **pos, int *path_nbrs, int *ant_first)
{
    int i;
    int j;
    int f;

    i = -1;
    f = dt->nbr_paths + 1;
    while (++i < dt->nbr_steps)
    {
        j = -1;
        while(++j < f)
        {
            if (j >= dt->ants || i - ant_first[j] >
                pos[dt->nbr_paths][path_nbrs[j]].depth - 2)
                continue;
            else
                ft_printf("L%d-%s ", j, dt->name[pos[dt->nbr_paths]
                    [path_nbrs[j]].path[i - ant_first[j] + 1]]);
        }
        ft_printf("\n");
        j = -1;
        while (++j <= dt->nbr_paths)
            f = (dt->nbr_steps - i < pos[dt->nbr_paths][j].depth) ?
                f : f + 1;
    }
}
