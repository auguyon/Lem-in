/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 11:06:30 by ftrujill          #+#    #+#             */
/*   Updated: 2019/12/13 11:13:09 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

void    fill_new_layer(t_layer *new_layer, t_path *path,
                int w, int used_edge)
{
    int j;
    int n;

    j = -1;
    n = new_layer->nbr_paths;
    while (++j < path->depth)
    {
        new_layer->paths[n].path[j] = path->path[j];
        new_layer->paths[n].depths[j] = path->depths[j];
    }
    new_layer->paths[n].path[j] = w;
    new_layer->paths[n].depths[j] = path->depths[j - 1] + 1 - 3 * used_edge;
    new_layer->paths[n].depth = path->depth + 1;
    new_layer->paths[n].endpoint = w;
    new_layer->nbr_paths += 1;
    if (w == new_layer->size - 1)
        if (new_layer->sol_depth > path->depth + 1)
            new_layer->sol_depth = path->depth + 1;
    if (w != new_layer->size - 1)
        new_layer->vtd[w] = path->depth + 1;
}

void    add_path(t_layer *new_layer, t_path *path, int w, int used_edge)
{
    int n;
    int j;

    if (path->endpoint == new_layer->size - 1
        && path->depths[path->depth - 1] >= new_layer->sol_depth)
        return ;
    else if (path->endpoint == new_layer->size - 1)
    {
        copy_solution(new_layer, path);
        return ;
    }
    n = new_layer->nbr_paths;
    if (!(new_layer->paths[n].path =
        (int*)malloc((path->depth + 1) * sizeof(int)))
        || !(new_layer->paths[n].depths =
            (int*)malloc((path->depth + 1) * sizeof(int))))
        ft_malloc_error();
    fill_new_layer(new_layer, path, w, used_edge);
}

int     j_step(t_path *path, t_layer *new_layer, t_solution *solution, int w)
{
    if (path->endpoint == 0 && solution->used_vertices[w][0])
        return(1);
    if (new_layer->vtd[w] == 0)
        add_path(new_layer, path, w, 0);
    else if (new_layer->vtd[w] > path->depth + 1)
    {
        add_path(new_layer, path, w, 0);
        new_layer->upd[w] = 1;
    }   
    return (0);
}

int     i_step(t_path *path, t_layer *new_layer, t_solution *solution)
{
    if (new_layer->upd[path->endpoint] != 0 || path->endpoint == new_layer->size)
        return (1);
    if (path->endpoint == new_layer->size - 1 
        && path->depths[path->depth - 1] < new_layer->sol_depth)
    {
        add_path(new_layer, path, new_layer->size - 1, 0);
        new_layer->vtd[new_layer->size - 1] = path->depth;
        new_layer->upd[new_layer->size - 1] = 1;
        return (1);
    }
    if (path->endpoint == new_layer->size - 1)
        return (1);
    if (path->depth > 1 && solution->used_vertices[path->endpoint][0]
        && !solution->used_vertices[path->path[path->depth - 2]][0])
    {
        add_path(new_layer, path,
            solution->paths[solution->used_vertices[path->endpoint][1]].
            path[(solution->used_vertices[path->endpoint][2]) - 1], 1);
        return (1);
    }
    return (0);
}

void    next_layer(int **g, int *nbr, t_layer **layer, t_solution *solution)
{
    int         i;
    int         j;
    t_path      *path;
    t_layer     *new_layer;

    if (!(new_layer = (t_layer*)malloc(sizeof(t_layer))))
        ft_malloc_error();
    initialize_new_layer(new_layer, *layer, nbr);
    i = -1;
    while (++i < (*layer)->nbr_paths)
    {
        path = &((*layer)->paths[i]);
        if (i_step(path, new_layer, solution))
            continue ;
        j = -1;
        while (g[path->endpoint][++j] != -1)
            if (j_step(path, new_layer, solution, g[path->endpoint][j]))
                continue ;
    }
    update(new_layer, (new_layer)->vtd, (new_layer)->upd);
    min_depth(new_layer);
    free_layer(layer);
    *layer = new_layer;
}