/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 11:02:23 by ftrujill          #+#    #+#             */
/*   Updated: 2019/12/12 11:12:51 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

void         find_solution(t_path **possible, int n, int *nbr_steps, int *sol)
{
    int     i;
    int     j;
    int     sum_lengths;
    int     max_length;
    int     aux;

    i = 1;
    *sol = 0;
    *nbr_steps = n + possible[0][0].depth - 2;
    while (possible[i])
    {
        j = 0;
        sum_lengths = 0;
        max_length = possible[0][0].depth;
        while (j <= i)
        {
            sum_lengths += possible[i][j].depth;
            max_length = ft_max(max_length, possible[i][j++].depth);
        }
        if ((i + 1) * max_length < n + sum_lengths)
        {
            aux = ((n + sum_lengths) % (i + 1) == 0) ? (n + sum_lengths) / (i + 1) - 2 : (n + sum_lengths) / (i + 1) - 1;
            if (aux < *nbr_steps)
            {
                *nbr_steps = aux;
                *sol = i;
            }
        }
        i++;
    }
}  

int         *ant_first_app(t_path **possible, int nbr_ants, int nbr_steps, int sol)
{
    int     *tab;
    int     i;
    int     j;
    int     ant;
    int     available_paths;

    tab = (int*)malloc(sizeof(int) * nbr_ants);
    i = -1;
    ant = 0;
    available_paths = sol + 1;
    while (++i < nbr_steps - possible[sol][0].depth + 2)
    {
        j = -1;
        while (++j < available_paths)
        {
            tab[ant] = i;
            ant++;
            if (ant >= nbr_ants)
                break;
        }
        if (ant >= nbr_ants)
            break;
        j = available_paths;
        while (--j >= 0)
        {
            if (nbr_steps - i < possible[sol][j].depth)
                available_paths--;
        }
    }
    return (tab);
}

int         *path_numbers(t_path **possible, int nbr_ants, int nbr_steps, int sol)
{
    int     *tab;
    int     i;
    int     j;
    int     ant;
    int     available_paths;

    tab = (int*)malloc(sizeof(int) * nbr_ants);
    i = -1;
    ant = 0;
    available_paths = sol + 1;
    while (++i < nbr_steps - possible[sol][0].depth + 2)
    {
        j = -1;
        while (++j < available_paths)
        {
            tab[ant] = j % (available_paths);
            ant++;
            if (ant >= nbr_ants)
                break;
        }
        if (ant >= nbr_ants)
            break;
        j = available_paths;
        while (--j >= 0)
        {
            if (nbr_steps - i < possible[sol][j].depth)
                available_paths--;
        }
    }
    return (tab);
}

void        prt_steps(t_path **possible, int nbr_ants, int nbr_steps, int sol)
{
    int i;
    int j;
    int f;
    int *path_nbrs;
    int *ant_first;

    i = 0;
    f = sol + 1;
    path_nbrs = path_numbers(possible, nbr_ants, nbr_steps, sol);
    ant_first = ant_first_app(possible, nbr_ants, nbr_steps, sol);
    while (i < nbr_steps)
    {
        j = -1;
        while(++j < f)
        {
            if (j >= nbr_ants || i - ant_first[j] > possible[sol][path_nbrs[j]].depth - 2)
                continue;
            else
                ft_printf("L%d-%d ", j, possible[sol][path_nbrs[j]].path[i - ant_first[j] + 1]);
        }
        ft_printf("\n");
        j = -1;
        while (++j <= sol)
            f = (nbr_steps - i < possible[sol][j].depth) ? f : f + 1;
        i++;
    }
}
