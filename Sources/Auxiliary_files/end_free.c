/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Aurelien <Aurelien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 12:22:45 by ftrujill          #+#    #+#             */
/*   Updated: 2019/12/15 19:08:23 by Aurelien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

void        free_path(t_path *path)
{
    free(path->path);
    free(path->depths);
}

void        free_stored_path(t_path *path)
{
    free(path->path);
    free(path->depths);
    free(path);
}

void        free_layer(t_layer **layer)
{
    int i;
    t_path *path;

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

void        free_solution(t_solution *solution)
{
    int i;
    t_path *path;

    i = -1;
    while (++i < solution->nbr_paths)
    {
        path = &(solution->paths[i]);
        free_path(path);
    }
    i = -1;
    while (++i < solution->size)
        free(solution->used_vertices[i]);
    free(solution->used_vertices);
}

void        free_possible(t_path **possible)
{
    int i;
    int j;

    i = -1;
    while(possible[++i])
    {
        j = -1;
        while (++j < i + 1)
            free_path(&possible[i][j]);
    }
    free(possible);
}

void        free_dt(t_data *dt)
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

void        free_all(t_data *dt, t_solution *solution, t_path **possible)
{
    free_dt(dt);
    free_solution(solution);
    free_possible(possible);
}