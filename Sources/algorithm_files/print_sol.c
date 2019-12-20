/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 11:02:23 by ftrujill          #+#    #+#             */
/*   Updated: 2019/12/20 11:31:22 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

void        aux_tab(t_path **possible, t_data *dt,
                    int *tab, int available_paths)
{
    int     i;
    int     j;
    int     ant;

    i = -1;
    ant = 0;
    while (++i <= dt->nbr_steps - possible[dt->nbr_paths][0].depth + 2)
    {
        j = -1;
        while (++j < available_paths)
        {
            tab[ant] = i;
            ant++;
            if (ant >= dt->ants)
                break;
        }
        if (ant >= dt->ants)
            break;
        j = available_paths;
        while (--j >= 0)
            if (dt->nbr_steps - i < possible[dt->nbr_paths][j].depth)
                available_paths--;
    }
}

int         *ant_first_app(t_data *dt, t_path **possible)
{
    int     *tab;
    int     available_paths;

    if (!(tab = (int*)ft_memalloc(sizeof(int) * dt->ants)))
        ft_malloc_error();
    available_paths = dt->nbr_paths + 1;
    aux_tab(possible, dt, tab, available_paths);
    return (tab);
}

void        aux_tab_two(t_path **possible, t_data *dt,
                    int *tab, int available_paths)
{
    int     i;
    int     j;
    int     ant;

    i = -1;
    ant = 0;
    while (++i <= dt->nbr_steps - possible[dt->nbr_paths][0].depth + 2)
    {
        j = -1;
        while (++j < available_paths)
        {
            tab[ant] = j % (available_paths);
            ant++;
            if (ant >= dt->ants)
                break;
        }
        if (ant >= dt->ants)
            break;
        j = available_paths;
        while (--j >= 0)
            if (dt->nbr_steps - i < possible[dt->nbr_paths][j].depth)
                available_paths--;
    }
}

int         *path_numbers(t_data *dt, t_path **possible)
{
    int     *tab;
    int     available_paths;

    if (!(tab = (int*)ft_memalloc(sizeof(int) * dt->ants)))
        ft_malloc_error();
    available_paths = dt->nbr_paths + 1;
    aux_tab_two(possible, dt, tab, available_paths);
    return (tab);
}

void        prt_steps(t_data *dt, t_path **pos, int *path_nbrs, int *ant_first)
{
    int i;
    int j;

    i = -1;
    while (++i < dt->nbr_steps)
    {
        ft_printf("Step #%d: ", i);
        j = -1;
        while(++j < dt->ants)
        {
            if (i >= ant_first[j] && i + 1< ant_first[j] +
                pos[dt->nbr_paths][path_nbrs[j]].depth)
                ft_printf("L%d-%s ", j, dt->name[pos[dt->nbr_paths]
                    [path_nbrs[j]].path[i + 1 - ant_first[j]]]);
        }
        ft_printf("\n");
    }
}
