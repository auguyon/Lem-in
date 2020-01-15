/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <ftrujill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 21:20:39 by ftrujill          #+#    #+#             */
/*   Updated: 2020/01/15 15:53:32 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

void	order_solution(t_solution *solution)
{
	int		i;
	t_path	tmp;

	i = 0;
	while (i < solution->nbr_paths - 1)
	{
		if (solution->paths[i].depth > solution->paths[i + 1].depth)
		{
			tmp = solution->paths[i];
			solution->paths[i] = solution->paths[i + 1];
			solution->paths[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
	solution->max_length = solution->paths[solution->nbr_paths - 1].depth;
}

void	update(t_layer *new_layer, int *visited, int *updated)
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

void	min_depth(t_layer *layer)
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

void	update_solution_aux(t_path *new_path, t_solution *solution,
							t_path **possible)
{
	int	i;
	int	j;

	i = -1;
	while (++i < new_path->depth)
	{
		solution->used_vertices[new_path->path[i]][0] = 1;
		solution->used_vertices[new_path->path[i]][1] = solution->nbr_paths;
		solution->used_vertices[new_path->path[i]][2] = i;
	}
	solution->nbr_paths += 1;
	i = 0;
	while (possible[i])
		i++;
	if (!(possible[i] = (t_path*)ft_memalloc((solution->nbr_paths + 1)
		* sizeof(t_path))))
		ft_malloc_error();
	j = -1;
	while (++j < i + 1)
		copy_path(&solution->paths[j], &possible[i][j]);
	possible[i + 1] = NULL;
	solution->max_length = ft_max(solution->max_length,
							solution->paths[solution->nbr_paths - 1].depth);
}

void	update_solution(t_path *path, t_solution *solution, t_path **possible)
{
	int		i;
	t_path	*new_path;

	new_path = &solution->paths[solution->nbr_paths];
	copy_path(path, new_path);
	i = new_path->depth - 2;
	while (i > 0)
	{
		if (solution->used_vertices[new_path->path[i]][0] != 0)
		{
			merge_paths(solution, i, solution->used_vertices[new_path->path[i]]
				[1], solution->used_vertices[new_path->path[i]][2]);
			i = new_path->depth - 2;
		}
		else
			i--;
	}
	update_solution_aux(new_path, solution, possible);
}
