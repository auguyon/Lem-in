/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:05:55 by ftrujill          #+#    #+#             */
/*   Updated: 2019/12/11 23:50:43 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

void		init_struct_parse(t_data **dt, t_info **i)
{
    t_data  *data;
    t_info  *info;

	if (!(info = (t_info*)malloc(sizeof(t_info))))
		ft_malloc_error();
	ft_bzero(info, sizeof(t_info));
    info->error = 1;
	if (!(data = (t_data*)malloc(sizeof(t_data))))
		ft_malloc_error();
	ft_bzero(data, sizeof(t_data));
    *(dt) = data;
    *(i) = info;
}

void        initialize(t_layer *layer, int size)
{
    t_path  *path;

    layer->size = size;
    layer->nbr_paths = 1;
    layer->sol_depth = size + 1;
    layer->min_depth = 1;
    layer->paths = (t_path*)malloc(sizeof(t_path));
    path = layer->paths;
    path->endpoint = 0;
    path->depth = 1;
    path->path = (int*)malloc(2 * sizeof(int));
    path->path[0] = 0;
    path->path[1] = -1;
    path->depths = (int*)malloc(2 * sizeof(int));
    path->depths[0] = 1;
}

void        initialize_new_layer(t_layer *new_layer, t_layer *layer, int *ngbs)
{
    int     i;
    int     s;
    int     v;

    i = 0;
    s = 0;
    while (i < layer->nbr_paths)
        s += ngbs[layer->paths[i++].endpoint];
    new_layer->nbr_paths = 0;
    new_layer->paths = (t_path*)malloc((s + 1) * sizeof(t_path));
    new_layer->size = layer->size;
    new_layer->sol_depth = layer->size + 1;
}