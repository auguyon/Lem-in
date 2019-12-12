/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:10:28 by ftrujill          #+#    #+#             */
/*   Updated: 2019/12/12 12:43:55 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

void        copy_path(t_path *source, t_path *dest)
{
    int i;

    dest->endpoint = source->endpoint;
    dest->depth = source->depth;
    if (!(dest->path = (int*)malloc(source->depth * sizeof(int)))
        || !(dest->depths = (int*)malloc(source->depth * sizeof(int))))
        ft_malloc_error();
    i = 0;
    while (i < source->depth)
    {
        dest->path[i] = source->path[i];
        dest->depths[i] = source->depths[i];
        i++;
    }
}

void        copy_solution(t_layer *new_layer, t_path *path)
{
    int j;
    int n;

    n = new_layer->nbr_paths;
    if (!(new_layer->paths[n].path = (int*)malloc((path->depth) * sizeof(int)))
        || !(new_layer->paths[n].depths = (int*)malloc((path->depth) * sizeof(int))))
        ft_malloc_error();
    j = -1;
    while (++j < path->depth)
    {
        new_layer->paths[n].path[j] = path->path[j];
        new_layer->paths[n].depths[j] = path->depths[j];
    }
    new_layer->paths[n].depth = path->depth;
    new_layer->paths[n].endpoint = new_layer->size - 1;
    new_layer->nbr_paths += 1;
    new_layer->sol_depth = path->depths[path->depth - 1];
}