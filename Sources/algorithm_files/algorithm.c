/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 09:39:54 by ftrujill          #+#    #+#             */
/*   Updated: 2019/12/12 22:14:35 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

void        update(t_layer *new_layer, int *visited, int *updated)
{
    int i;
    int j;
    int k;
    int depth;

    i = -1;
    while (++i < new_layer->size)
    {
        if (updated[i] == 0)
            continue ;
        j = -1;
        while (++j < new_layer->nbr_paths)
        {
            depth = new_layer->paths[j].depth;
            k = -1;
            while (++k < depth)
            {
                if (new_layer->paths[j].path[k] == i
                    && new_layer->paths[j].depths[k] > visited[i])
                        new_layer->paths[j].endpoint = new_layer->size;
            }
        }
    }
}

void        min_depth(t_layer *layer)
{
    int i;

    i = -1;
    layer->min_depth = layer->size;
    while (++i < layer->nbr_paths)
    {
        if (layer->paths[i].endpoint != layer->size)
            layer->min_depth = ft_min(layer->min_depth,
                layer->paths[i].depths[layer->paths[i].depth - 1]);
    }
}

int        mbfs(t_data *dt, t_solution *solution, t_layer *layer, t_path **possible)
{
    ft_bzero(layer->vtd, layer->size * sizeof(int));
    layer->vtd[0] = 1;
    while((layer->sol_depth == layer->size + 1
        || layer->min_depth < layer->sol_depth + solution->max_length
        || layer->nbr_paths > 1))
    {
        if (layer->nbr_paths == 0)
            return (0);
        next_layer(dt, &layer, solution);
    }
    update_solution(layer->paths, solution, possible);
    return (1);
}   

int         solver_2(t_data *dt, t_layer *layer, t_solution *solution, t_path **possible)
{
    int         sol;
    int         nbr_steps;

    possible[0] = NULL;
    initialize(layer, dt->nb_rooms);
    // prt_g(dt->tab, dt->nb_rooms);
    while (mbfs(dt, solution, layer, possible))
    {
    }
    prt_possible(possible);
    find_solution(possible, dt->ants, &nbr_steps, &sol);
    ft_printf("\nAnd the right solution with %d ants is the one with %d path(s) and it takes %d step(s) demander:%d\n\n", dt->ants, sol + 1, nbr_steps, dt->best_move);
    prt_steps(possible, dt->ants, nbr_steps, sol);
    return (0);
}

int         solver(t_data *dt)
{
    int         i;
    t_layer     *layer;
    t_solution  *solution;
    t_path      **possible;

    if (!(solution = (t_solution*)malloc(sizeof(t_solution)))
        || !(solution->used_vertices = (int**)malloc(dt->nb_rooms * sizeof(int*)))
        || !(solution->paths = (t_path*)malloc(dt->nb_rooms * sizeof(t_path)))
        || !(possible = (t_path**)malloc(dt->nb_rooms * sizeof(t_path*)))
        || !(layer = (t_layer*)malloc(sizeof(t_layer))))
        ft_malloc_error();
    i = 0;
    while (i < dt->nb_rooms)
    {
        if (!(solution->used_vertices[i] = (int*)malloc(3 * sizeof(int))))
            ft_malloc_error();
        solution->used_vertices[i++][0] = 0;
    }
    solution->max_length = 0;
    solution->nbr_paths = 0;
    solution->size = dt->nb_rooms;   
    return (solver_2(dt, layer, solution, possible));
}
