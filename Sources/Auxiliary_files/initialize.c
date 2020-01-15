/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <ftrujill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:05:55 by ftrujill          #+#    #+#             */
/*   Updated: 2020/01/15 18:40:38 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

void		init_struct_parse(t_data **dt, t_info **i)
{
	t_data	*data;
	t_info	*info;

	if (!(info = (t_info*)malloc(sizeof(t_info))))
		ft_malloc_error();
	ft_bzero(info, sizeof(t_info));
	if (!(data = (t_data*)malloc(sizeof(t_data))))
		ft_malloc_error();
	ft_bzero(data, sizeof(t_data));
	*(dt) = data;
	*(i) = info;
}

void		initialize(t_layer **layer_p, int size)
{
	t_layer		*layer;
	t_path		*p;

	p = NULL;
	if (!(layer = (t_layer*)malloc(sizeof(t_layer)))
		|| !(p = (t_path*)malloc(sizeof(t_path)))
		|| !(p->path = (int*)malloc(2 * sizeof(int)))
		|| !(p->depths = (int*)malloc(2 * sizeof(int)))
		|| !(layer->vtd = (int*)ft_memalloc(size * sizeof(int)))
		|| !(layer->upd = (int*)ft_memalloc(size * sizeof(int))))
		ft_malloc_error();
	(*layer_p) = layer;
	layer->paths = p;
	layer->size = size;
	layer->nbr_paths = 1;
	layer->sol_depth = size + 1;
	layer->min_depth = 1;
	layer->vtd[0] = 1;
	p->endpoint = 0;
	p->depth = 1;
	p->path[0] = 0;
	p->path[1] = -1;
	p->depths[0] = 1;
}

void		initialize_new_layer(t_layer *new_layer, t_layer *layer, int *ngbs)
{
	int		i;
	int		s;

	i = 0;
	s = 0;
	while (i < layer->nbr_paths)
		s += ngbs[layer->paths[i++].endpoint];
	if (!(new_layer->paths = (t_path*)malloc((s + 1) * sizeof(t_path)))
		|| !(new_layer->upd = (int*)ft_memalloc(sizeof(int) * layer->size))
		|| !(new_layer->vtd =
			(int*)ft_realloc(layer->vtd, sizeof(int) * layer->size)))
		ft_malloc_error();
	new_layer->nbr_paths = 0;
	new_layer->size = layer->size;
	new_layer->sol_depth = layer->size + 1;
}
