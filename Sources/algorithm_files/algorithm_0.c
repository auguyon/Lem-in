/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 09:39:54 by ftrujill          #+#    #+#             */
/*   Updated: 2019/12/13 16:05:24 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

void         find_solution(t_path **possible, t_solution *sol)
{
    int     i;
    int     j;
    int     s;
    int     max_length;
    int     aux;

    i = 0;
    while (possible[++i])
    {
        j = 0;
        s = 0;
        max_length = possible[0][0].depth;
        while (j <= i)
        {
            s += possible[i][j].depth;
            max_length = ft_max(max_length, possible[i][j++].depth);
        }
        if ((i + 1) * (max_length + 1) <= sol->nbr_ants + s)
        {
            aux = ((sol->nbr_ants + s) % (i + 1) == 0) ? (sol->nbr_ants + s) /
                (i + 1) - 2 : (sol->nbr_ants + s) / (i + 1) - 1;
            sol->nbr_paths = (aux < sol->nbr_steps) ? i : sol->nbr_paths;
            sol->nbr_steps = ft_min(aux, sol->nbr_steps);
        }
    }
}  

int        mbfs(t_data *dt, t_solution *solution, t_path **possible)
{
    t_layer     *layer;

    initialize(&layer, dt->nb_rooms);
    while((layer->sol_depth == layer->size + 1
        || layer->min_depth < layer->sol_depth + solution->max_length
        || layer->nbr_paths > 1))
    {
        if (layer->nbr_paths == 0)
            return (0);
        next_layer(dt->tab, dt->nbr, &layer, solution);
    }
    update_solution(layer->paths, solution, possible);
    free_layer(&layer);
    return (1);
}   

void        order_possible(t_path **possible)
{
    int     i;
    int     j;
    t_path  tmp;

    i = -1;
    while (possible[++i])
    {
        j = 0;
        while (j < i)
        {
            if (possible[i][j].depth > possible[i][j + 1].depth)
                {
                    tmp = possible[i][j];
                    possible[i][j] = possible[i][j + 1];
                    possible[i][j + 1] = tmp;
                    j = 0;
                }
            else
                j++;
        }
    }
}

int         solver_2(t_data *dt, t_solution *solution, t_path **possible)
{
    int *path_nbrs;
    int *ant_first;

    possible[0] = NULL;
   // prt_g(dt->tab, dt->nb_rooms);
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
    prt_steps(possible, solution, path_nbrs, ant_first);
    ft_printf("\nAnd the right solution with %d ants is the one with %d path(s)"
    " and it takes %d step(s)\n\n", dt->ants, solution->nbr_paths + 1, solution->nbr_steps);
    free(path_nbrs);
    free(ant_first);
    free_possible(possible);
    free_solution(solution);
    return (0);
}

int         solver(t_data *dt)
{
    int         i;
    int         size;
    t_solution  *solution;
    t_path      **possible;

    size = dt->nb_rooms;
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
