/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <ftrujill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 11:02:23 by ftrujill          #+#    #+#             */
/*   Updated: 2020/01/15 16:03:07 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

void	aux_tab(t_path **possible, t_data *dt, int *tab, int available_paths)
{
	int	i;
	int	j;
	int	ant;

	i = -1;
	ant = 0;
	while (++i <= dt->nbr_steps - possible[dt->nbr_paths][0].depth + 2)
	{
		j = -1;
		while (++j < available_paths)
		{
			tab[ant] = i;
			ant++;
			if (ant >= dt->ants)
				break ;
		}
		if (ant >= dt->ants)
			break ;
		j = available_paths;
		while (--j >= 0)
			if (dt->nbr_steps - i < possible[dt->nbr_paths][j].depth)
				available_paths--;
	}
}

int		*ant_first_app(t_data *dt, t_path **possible)
{
	int	*tab;
	int	available_paths;

	if (!(tab = (int*)ft_memalloc(sizeof(int) * dt->ants)))
		ft_malloc_error();
	available_paths = dt->nbr_paths + 1;
	aux_tab(possible, dt, tab, available_paths);
	return (tab);
}

void	aux_tab_two(t_path **possible, t_data *dt, int *tab, int available_path)
{
	int	i;
	int	j;
	int	ant;

	i = -1;
	ant = 0;
	while (++i <= dt->nbr_steps - possible[dt->nbr_paths][0].depth + 2)
	{
		j = -1;
		while (++j < available_path)
		{
			tab[ant] = j % (available_path);
			ant++;
			if (ant >= dt->ants)
				break ;
		}
		if (ant >= dt->ants)
			break ;
		j = available_path;
		while (--j >= 0)
			if (dt->nbr_steps - i < possible[dt->nbr_paths][j].depth)
				available_path--;
	}
}

int		*path_numbers(t_data *dt, t_path **possible)
{
	int	*tab;
	int	available_paths;

	if (!(tab = (int*)ft_memalloc(sizeof(int) * dt->ants)))
		ft_malloc_error();
	available_paths = dt->nbr_paths + 1;
	aux_tab_two(possible, dt, tab, available_paths);
	return (tab);
}

void	prt_steps(t_data *dt, t_path **pos, int *path_nbrs, int *ant_first)
{
	int i;
	int j;

	i = -1;
	ft_printf("\n");
	while (++i < dt->nbr_steps)
	{
		ft_printf("Step #%d: ", i + 1);
		j = -1;
		while (++j < dt->ants)
		{
			if (i >= ant_first[j] && i + 1 < ant_first[j] +
				pos[dt->nbr_paths][path_nbrs[j]].depth)
				ft_printf("L%d-%s ", j + 1, dt->name[pos[dt->nbr_paths]
					[path_nbrs[j]].path[i + 1 - ant_first[j]]]);
		}
		ft_printf("\n");
	}
}
