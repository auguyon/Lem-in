/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <ftrujill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 10:55:46 by ftrujill          #+#    #+#             */
/*   Updated: 2020/01/15 18:31:52 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

void	find_solution(t_data *dt, t_path **possible)
{
	int	i;
	int	j;
	int	s;
	int	max_length;
	int	aux;

	i = 0;
	while (possible[++i])
	{
		j = 0;
		s = 0;
		max_length = possible[0][0].depth;
		while (j <= i)
		{
			s += possible[i][j].depth;
			max_length = ft_max(max_length, possible[i][j++].depth);
		}
		if ((i + 1) * (max_length + 1) <= dt->ants + s)
		{
			aux = ((dt->ants + s) % (i + 1) == 0) ? (dt->ants + s) /
				(i + 1) - 2 : (dt->ants + s) / (i + 1) - 1;
			dt->nbr_paths = (aux < dt->nbr_steps) ? i : dt->nbr_paths;
			dt->nbr_steps = ft_min(aux, dt->nbr_steps);
		}
	}
}

int		check_path(t_path *path, t_data *dt)
{
	int i;
	int j;
	int t;

	if (path->path[0] != 0 || path->path[path->depth - 1] != dt->nb_rooms - 1)
		ft_printf("\nBad start/ending %d/%d \n", path->path[0], path->path[1]);
	i = -1;
	while (++i < path->depth - 1)
	{
		if (path->path[i] == dt->nb_rooms - 1)
			ft_printf("\nEnding at position %d \n", i);
		t = 0;
		j = -1;
		while (dt->tab[path->path[i]][++j] != -1)
			if (dt->tab[path->path[i]][j] == path->path[i + 1])
				t = 1;
		if (t == 0)
			ft_printf("\nWRONG not neighbour \n");
		j = -1;
		while (++j < i)
			if (path->path[i] == path->path[j])
				ft_printf("\nWRONG Repeated link at positions %d, %d with"
					"values %d, %d \n", i, j, path->path[i], path->path[j]);
	}
	return (0);
}

void	check_overlap(t_path *a, t_path *b)
{
	int	i;
	int	j;

	i = 0;
	while (++i < a->depth - 1)
	{
		j = 0;
		while (++j < b->depth - 1)
		{
			if (a->path[i] == b->path[j])
				ft_printf("Paths overlaping at positions %d and "
				"%d with values %d and %d\n", i, j, a->path[i], b->path[j]);
		}
	}
}

void	prt_check_possible(t_path **possible, t_data *dt)
{
	int i;
	int j;
	int k;

	ft_printf("Printing possible solutions\n\n");
	i = 0;
	while (possible[i])
	{
		if (i == 0)
			ft_printf("Shortest path:\n");
		else
			ft_printf("Shortests %d paths:\n", i + 1);
		j = -1;
		while (++j < i + 1)
		{
			prt_path(&possible[i][j]);
			check_path(&(possible[i][j]), dt);
			k = -1;
			while (++k < j)
				check_overlap(&possible[i][k], &possible[i][j]);
		}
		ft_printf("\n");
		i++;
	}
}
