/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_free_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <ftrujill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 18:35:45 by ftrujill          #+#    #+#             */
/*   Updated: 2020/01/15 18:37:16 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

void		free_dt(t_data *dt)
{
	int i;

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
