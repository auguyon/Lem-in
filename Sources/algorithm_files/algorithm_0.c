/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <ftrujill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:41:56 by ftrujill          #+#    #+#             */
/*   Updated: 2020/01/15 19:08:45 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

void	order_possible(t_path **possible)
{
	int		i;
	int		j;
	t_path	tmp;

	i = -1;
	while (possible[++i])
	{
		j = 0;
		while (j < i)
		{
			if (possible[i][j].depth > possible[i][j + 1].depth)
			{
				tmp = possible[i][j];
				possible[i][j] = possible[i][j + 1];
				possible[i][j + 1] = tmp;
				j = 0;
			}
			else
				j++;
		}
	}
}

int		is_trivial(t_data *dt, t_info *info)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (i < dt->nbr[0])
		n = (dt->tab[0][i++] == dt->nb_rooms - 1) ? 1 : n;
	if (!n || dt->ants == 0)
		return (0);
	print_map(info->map_start);
	i = 0;
	ft_printf("\nStep #1: ");
	while (i + 1 < dt->ants)
		ft_printf("L%d-%s ", i++ + 1, dt->name[dt->nb_rooms - 1]);
	if (dt->ants)
		ft_printf("L%d-%s", i + 1, dt->name[dt->nb_rooms - 1]);
	ft_printf("\n");
	ft_printf("\nThe right solution with %d ants is the one with %d "
			"path(s) and it takes %d step(s) for %d step(s) asked.\n",
			dt->ants, 1, 1, 1);
	free_dt(dt);
	return (1);
}

int		mbfs(t_data *dt, t_solution *solution, t_path **possible)
{
	t_layer		*layer;

	initialize(&layer, dt->nb_rooms);
	while ((layer->sol_depth == layer->size + 1
		|| layer->min_depth < layer->sol_depth + solution->max_length
		|| layer->nbr_paths > 1))
	{
		if (layer->nbr_paths == 1 && layer->sol_depth < layer->size + 1)
			break ;
		if (layer->nbr_paths == 0)
		{
			free_layer(&layer);
			return (0);
		}
		next_layer(dt->tab, dt->nbr, &layer, solution);
	}
	update_solution(layer->paths, solution, possible);
	free_layer(&layer);
	return (1);
}

void	solver_2(t_data *dt, t_solution *solution, t_path **possible,
						t_info *info)
{
	int *path_nbrs;
	int *ant_first;

	while (mbfs(dt, solution, possible))
	{
	}
	if (solution->max_length == 0)
		print_error(info->error == 1 ? -13 : info->error);
	else
	{
		print_map(info->map_start);
		dt->nbr_paths = 0;
		dt->nbr_steps = dt->ants + possible[0][0].depth - 2;
		order_possible(possible);
		find_solution(dt, possible);
		path_nbrs = path_numbers(dt, possible);
		ant_first = ant_first_app(dt, possible);
		prt_steps(dt, possible, path_nbrs, ant_first);
		ft_printf("\nThe right solution with %d ants is the one with %d "
			"path(s) and it takes %d step(s) for %d step(s) asked.\n",
			dt->ants, dt->nbr_paths + 1, dt->nbr_steps, dt->best_move);
		free(path_nbrs);
		free(ant_first);
	}
	free_all(dt, solution, possible);
}

void	solver(t_data *dt, t_info *info)
{
	int			i;
	int			size;
	t_solution	*solution;
	t_path		**possible;

	size = dt->nb_rooms;
	if (is_trivial(dt, info))
		return ;
	if (!(solution = (t_solution*)ft_memalloc(sizeof(t_solution)))
		|| !(solution->used_vertices = (int**)ft_memalloc(size * sizeof(int*)))
		|| !(solution->paths = (t_path*)ft_memalloc(size * sizeof(t_path)))
		|| !(possible = (t_path**)ft_memalloc(size * sizeof(t_path*))))
		ft_malloc_error();
	i = 0;
	while (i < size)
	{
		if (!(solution->used_vertices[i] = (int*)ft_memalloc(3 * sizeof(int))))
			ft_malloc_error();
		solution->used_vertices[i++][0] = 0;
	}
	solution->max_length = 0;
	solution->nbr_paths = 0;
	solution->size = size;
	possible[0] = NULL;
	solver_2(dt, solution, possible, info);
}
