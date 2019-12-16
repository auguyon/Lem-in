/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:05:55 by ftrujill          #+#    #+#             */
/*   Updated: 2019/12/13 16:06:05 by ftrujill         ###   ########.fr       */
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

	i = -1;
	while (++i < (*layer)->nbr_paths)
	{
		free_path(&((*layer)->paths[i]));
	}
	free((*layer)->upd);
	free((*layer)->vtd);
	free((*layer));
}

void		free_solution(t_solution *solution)
{
	int		i;

	i = -1;
	while (++i < solution->nbr_paths)
		free_path(&(solution->paths[i]));
	i = -1;
	while (++i < solution->size)
		free(solution->used_vertices[i]);
	free(solution->used_vertices);
	free(solution);
}

void		free_possible(t_path **possible)
{
	int		i;
	int		j;

	i = -1;
	while (possible[++i])
	{
		j = -1;
		while (++j < i + 1)
			free_path(&possible[i][j]);
		free(possible[i]);
	}
	free(possible);
}

void		free_dt(t_data *dt)
{
	int		i;

	i = 0;
	while (i < dt->nb_rooms)
	{
		free(dt->name[i]);
		free(dt->tab[i++]);
	}
	free(dt->nbr);
	free(dt->x);
	free(dt->y);
	free(dt->name);
	free(dt->tab);
	free(dt);
}

void		free_all(t_data *dt, t_solution *solution, t_path **possible)
{
	free_dt(dt);
	free_solution(solution);
	free_possible(possible);
}
