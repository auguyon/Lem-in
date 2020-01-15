/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <ftrujill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:07:26 by ftrujill          #+#    #+#             */
/*   Updated: 2020/01/15 15:59:23 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

void	prt_g(int **g, int size)
{
	int i;
	int j;

	ft_printf("Printing graph\n\n");
	i = 0;
	while (i < size)
	{
		j = 0;
		while (g[i][j] != -1)
			ft_printf("%d ", g[i][j++]);
		i++;
		ft_printf("\n");
	}
	ft_printf("\n");
}

void	prt_path(t_path *path)
{
	int i;

	i = 0;
	ft_printf("Endpoint: %d, Length: %d, Path: ", path->endpoint, path->depth);
	while (i < path->depth)
		ft_printf("%d ", path->path[i++]);
	ft_printf(", Depths: ");
	i = 0;
	while (i < path->depth)
		ft_printf("%d ", path->depths[i++]);
	ft_printf("\n");
}

void	prt_layer(t_layer *layer)
{
	int	i;

	i = 0;
	ft_printf("\nSize %d, nbr of paths %d, sol_depth %d, min_depth %d\n",
		layer->size, layer->nbr_paths, layer->sol_depth, layer->min_depth);
	while (i < layer->nbr_paths)
		prt_path(&(layer->paths[i++]));
	i = 0;
}

void	prt_solution(t_solution *solution)
{
	int i;

	ft_printf("\n\nThe solution\n\n");
	ft_printf("\nThe size is %d, nbr_paths %d, max_length %d\n",
		solution->size, solution->nbr_paths, solution->max_length);
	i = 0;
	while (i < solution->nbr_paths)
		prt_path(&solution->paths[i++]);
}

void	prt_possible(t_path **possible)
{
	int i;
	int j;

	ft_printf("Printing possible solutions\n\n");
	i = 0;
	while (possible[i])
	{
		if (i == 0)
			ft_printf("Shortest path:\n");
		else
			ft_printf("Shortests %d paths:\n", i + 1);
		j = 0;
		while (j < i + 1)
			prt_path(&possible[i][j++]);
		ft_printf("\n");
		i++;
	}
}
