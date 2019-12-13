/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 11:10:48 by ftrujill          #+#    #+#             */
/*   Updated: 2019/12/13 11:25:31 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

void    merge_first_aux(t_solution *solution, int pos, int i, int p)
{
    int     j;
    t_path  *old_path;
    t_path  *new_path;

    old_path = &solution->paths[i];
    new_path = &solution->paths[solution->nbr_paths];
    free_path(old_path);
    if (!(old_path->path = (int*)malloc(solution->size * sizeof(int)))
        || !(old_path->depths = (int*)malloc(solution->size * sizeof(int))))
        ft_malloc_error();
    j = -1;
    while (++j <= pos)
    {
        old_path->path[j] = new_path->path[j];
        old_path->depths[j] = new_path->depths[j];
    }
    old_path->endpoint = solution->size - 1;
}

void    merge_second_aux(t_path *tmp, t_solution *solution, int p, int pos)
{
    int j;
    t_path  *tmp2;
    t_path  *new_path;

    if (!(tmp2 = (t_path*)malloc(sizeof(t_path))))
        ft_malloc_error();
    new_path = &solution->paths[solution->nbr_paths];
    copy_path(new_path, tmp2);
    j = -1;
    while (++j < p)
    {
        new_path->path[j] = tmp->path[j];
        new_path->depths[j] = tmp->depths[j];
        solution->used_vertices[new_path->path[j]][0] = 1;
        solution->used_vertices[new_path->path[j]][1] = solution->nbr_paths;
        solution->used_vertices[new_path->path[j]][2] = j;
    }
    j = -1;
    while (pos + ++j + 2 < tmp2->depth)
    {
        new_path->path[p + j] = tmp2->path[pos + j + 2];
        new_path->depths[p + j] = tmp2->depths[pos + j + 2];
    }
    new_path->depth = p + j;
    free_stored_path(tmp2);
}

void    merge_third_aux(t_path *old_path, t_solution *solution, int i)
{
    int j;

    j = -1;
    while (++j < old_path->depth)
    {
        solution->used_vertices[old_path->path[j]][0] = 1;
        solution->used_vertices[old_path->path[j]][1] = i;
        solution->used_vertices[old_path->path[j]][2] = j;
    }
}

void    merge_paths(t_solution *solution, int pos, int i, int p)
{
    int     j;
    t_path  *tmp;
    t_path  *old_path;
    t_path  *new_path;

    if (!(tmp = (t_path*)malloc(sizeof(t_path))))
        ft_malloc_error();
    copy_path(&solution->paths[i], tmp);
    merge_first_aux(solution, pos, i, p);
    old_path = &solution->paths[i];
    new_path = &solution->paths[solution->nbr_paths];
    j = -1;
    while (p + ++j < tmp->depth)
    {
        old_path->path[pos + j] = tmp->path[p + j];
        old_path->depths[pos + j] = tmp->depths[p + j];
    }
    old_path->depth = pos + j;
    merge_second_aux(tmp, solution, p, pos);
    new_path->endpoint = solution->size - 1;
    free_stored_path(tmp);
    merge_third_aux(old_path, solution, i);
}
