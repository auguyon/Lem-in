/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <ftrujill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 11:10:48 by ftrujill          #+#    #+#             */
/*   Updated: 2020/01/15 18:29:52 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

void	merge_first_aux(t_solution *solution, int p, int i, int pos)
{
	int		j;
	t_path	*old_path;
	t_path	*new_path;

	old_path = &solution->paths[i];
	new_path = &solution->paths[solution->nbr_paths];
	j = -1;
	while (pos + ++j < new_path->depth)
	{
		old_path->path[p + j] = new_path->path[pos + j];
		old_path->depths[p + j] = new_path->depths[pos + j];
	}
	old_path->depth = p + j;
	old_path->endpoint = solution->size - 1;
}

void	merge_third_aux(t_solution *solution, int i, int pos, int k)
{
	int		j;
	t_path	*old_path;
	t_path	*new_path;

	old_path = &solution->paths[i];
	new_path = &solution->paths[solution->nbr_paths];
	new_path->endpoint = solution->size - 1;
	j = -1;
	while (++j < old_path->depth)
	{
		solution->used_vertices[old_path->path[j]][0] = 1;
		solution->used_vertices[old_path->path[j]][1] = i;
		solution->used_vertices[old_path->path[j]][2] = j;
	}
	j = -1;
	while (pos - k + ++j < new_path->depth)
	{
		solution->used_vertices[new_path->path[pos - k + j]][0] = 0;
		solution->used_vertices[new_path->path[pos - k + j]][1] = 0;
		solution->used_vertices[new_path->path[pos - k + j]][2] = 0;
	}
}

int		merge_second_aux(t_path *tmp, t_solution *solution, int p, int pos)
{
	int		j;
	int		k;
	t_path	*tmp2;
	t_path	*new_path;

	new_path = &solution->paths[solution->nbr_paths];
	deep_copy_path(new_path, &tmp2, solution->size);
	k = 0;
	while (tmp->path[p + k] == tmp2->path[pos - k])
	{
		k++;
		solution->used_vertices[tmp->path[p + k]][0] = 0;
		solution->used_vertices[tmp->path[p + k]][1] = 0;
		solution->used_vertices[tmp->path[p + k]][2] = 0;
	}
	k--;
	j = -1;
	while (++j <= pos - k)
	{
		new_path->path[j] = tmp2->path[j];
		new_path->depths[j] = tmp2->depths[j];
	}
	free_stored_path(tmp2);
	return (k);
}

void	merge_zero_aux(t_path *old_path, t_path *tmp, int p)
{
	int		j;

	j = -1;
	while (++j <= p)
	{
		old_path->path[j] = tmp->path[j];
		old_path->depths[j] = tmp->depths[j];
	}
}

void	merge_paths(t_solution *solution, int pos, int i, int p)
{
	int		j;
	int		k;
	t_path	*tmp;
	t_path	*old_path;
	t_path	*new_path;

	old_path = &solution->paths[i];
	new_path = &solution->paths[solution->nbr_paths];
	deep_copy_path(old_path, &tmp, solution->size);
	merge_zero_aux(old_path, tmp, p);
	merge_first_aux(solution, p, i, pos);
	k = merge_second_aux(tmp, solution, p, pos);
	j = -1;
	while (p + k + ++j < tmp->depth)
	{
		new_path->path[pos - k + j] = tmp->path[p + k + j];
		new_path->depths[pos - k + j] = tmp->depths[p + k + j];
	}
	new_path->depth = pos - k + j;
	merge_third_aux(solution, i, pos, k);
	free_stored_path(tmp);
}
