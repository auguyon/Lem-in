/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <ftrujill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 12:22:45 by ftrujill          #+#    #+#             */
/*   Updated: 2020/01/15 18:36:11 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

void		free_path(t_path *path)
{
	free(path->path);
	free(path->depths);
}

void		free_stored_path(t_path *path)
{
	free(path->path);
	free(path->depths);
	free(path);
}

void		free_layer(t_layer **layer)
{
	int		i;
	t_path	*path;

	i = -1;
	while (++i < (*layer)->nbr_paths)
	{
		path = &((*layer)->paths[i]);
		free_path(path);
	}
	free((*layer)->paths);
	free((*layer)->upd);
	free((*layer)->vtd);
	free((*layer));
}

void		free_solution(t_solution *solution)
{
	int		i;
	t_path	*path;

	i = -1;
	while (++i <= solution->nbr_paths)
	{
		path = &(solution->paths[i]);
		free_path(path);
	}
	free(solution->paths);
	i = -1;
	while (++i < solution->size)
		free(solution->used_vertices[i]);
	free(solution->used_vertices);
	free(solution);
}

void		free_possible(t_path **possible)
{
	int i;
	int j;

	i = -1;
	while (possible[++i])
	{
		j = -1;
		while (++j < i + 1)
			free_path(&(possible[i][j]));
		free(possible[i]);
	}
	free(possible);
}
