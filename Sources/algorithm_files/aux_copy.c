/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <ftrujill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:10:28 by ftrujill          #+#    #+#             */
/*   Updated: 2020/01/15 16:30:01 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*newptr;

	if (!(newptr = ft_memalloc(size)))
		return (NULL);
	ft_memcpy(newptr, ptr, size);
	return (newptr);
}

void	deep_copy_path(t_path *source, t_path **dest_p, int size)
{
	t_path *dest;

	if (!(*dest_p = (t_path*)ft_memalloc(sizeof(t_path))))
		ft_malloc_error();
	dest = *dest_p;
	if (!(dest->path = (int*)ft_realloc(source->path,
								sizeof(int) * source->depth))
		|| !(dest->depths = (int*)ft_realloc(source->depths,
								sizeof(int) * source->depth)))
		ft_malloc_error();
	dest->endpoint = source->endpoint;
	dest->depth = source->depth;
	free_path(source);
	if (!(source->path = (int*)ft_memalloc(sizeof(int) * size))
		|| !(source->depths = (int*)ft_memalloc(sizeof(int) * size)))
		ft_malloc_error();
}

void	copy_path(t_path *source, t_path *dest)
{
	dest->endpoint = source->endpoint;
	dest->depth = source->depth;
	if (!(dest->path = (int*)ft_realloc(source->path,
										sizeof(int) * source->depth))
		|| !(dest->depths = (int*)ft_realloc(source->depths,
										sizeof(int) * source->depth)))
		ft_malloc_error();
}

void	copy_solution(t_layer *new_layer, t_path *path)
{
	int j;
	int n;

	n = new_layer->nbr_paths;
	if (!(new_layer->paths[n].path =
		(int*)ft_memalloc((path->depth) * sizeof(int)))
		|| !(new_layer->paths[n].depths =
		(int*)ft_memalloc((path->depth) * sizeof(int))))
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
