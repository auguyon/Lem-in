/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:05:55 by ftrujill          #+#    #+#             */
/*   Updated: 2019/12/05 22:43:11 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

void		init_struct_parse(t_data **dt, t_info **i)
{
    t_data  *data;
    t_info  *info;

	if (!(info = (t_info*)malloc(sizeof(t_info))))
		exit(0);
	ft_bzero(info, sizeof(t_info));
    info->error = 1;
	if (!(data = (t_data*)malloc(sizeof(t_data))))
		exit(0);
	ft_bzero(data, sizeof(t_data));
    *(dt) = data;
    *(i) = info;
}

void		init_struct_algo(t_solution **s, t_path ***p, int size)
{
	int	i;
	t_solution 	*sol;
	t_path 		**pos;

	i = 0;
	if (!(pos = (t_path**)malloc(sizeof(t_path*) * size)))
		exit(0);
	*(p) = pos;
    if (!(sol = (t_solution*)malloc(sizeof(t_solution))))
    	exit(0);
    ft_bzero(sol, sizeof(t_solution));
	sol->size = size;
	if (!(sol->used_vertices = (int**)malloc(sizeof(int*) * size)))
		exit(0);
	while (i < size)
		if (!(sol->used_vertices[i++] = (int*)malloc(sizeof(int) * 3)))
			exit(0);
	i = 0;
	while (i < size)
        if (!(sol->used_vertices[i++][0] = 0))
        	exit(0);
    if (!(sol->paths = (t_path*)malloc(sizeof(t_path) * size)))
        exit(0);
	*(s) = sol;
}

void        initialize(t_layer **l, int size)
{
    t_layer *layer;

    if (!(layer = (t_layer*)malloc(sizeof(t_layer))))
		exit(0);
	ft_bzero(layer, sizeof(t_layer));
    layer->size = size;
    layer->nbr_paths = 1;
    layer->sol_depth = size + 1;
    layer->min_depth = 1;
    if (!(layer->paths = (t_path*)malloc(sizeof(t_path))))
        exit(0);
    ft_bzero(layer->paths, sizeof(t_path));
    if (!(layer->paths->path = (int*)malloc(2 * sizeof(int))))
        exit(0);
    if (!(layer->paths->depths = (int*)malloc(2 * sizeof(int))))
        exit(0);
    ft_fill_nb(layer->paths->path, -1, 1);
    ft_fill_nb(layer->paths->depths, -1, 1);
    *(l) = layer;
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
    //new_layer->min_depth = layer->min_depth;
}