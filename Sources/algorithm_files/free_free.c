/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 12:22:45 by ftrujill          #+#    #+#             */
/*   Updated: 2019/12/12 15:12:56 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

void        free_layer(t_layer **layer)
{
    int i;
    t_path *path;

    i = -1;
    while (++i < (*layer)->nbr_paths)
    {
        path = &((*layer)->paths[i]);
        free(path->path);
        free(path->depths);
    }
    free((*layer)->paths);
    free((*layer)->upd);
    free((*layer)->vtd);
    free((*layer));
}

void        free_solution(t_solution *solution)
{

}

void        free_possible(t_path **possible)
{

}

void        free_dt(t_data *dt)
{

}

void        free_all(t_data *dt, t_layer *layer, t_solution *solution, t_path **possible)
{
    free_dt(dt);
    free_layer(&layer);
    free_solution(solution);
    free_possible(possible);
}