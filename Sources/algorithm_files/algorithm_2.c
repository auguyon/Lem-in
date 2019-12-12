/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 11:10:48 by ftrujill          #+#    #+#             */
/*   Updated: 2019/12/12 14:37:42 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

void        reset_path(t_path *path)
{
    path->endpoint = 0;
    path->depth = 0;
    free(path->path);
    free(path->depths);
}

void        merge_paths(t_solution *solution, int pos, int i, int p) //The position pos of new_path is equal to the position p of solution->paths[i] (new_path[pos] = solution->paths[i][p])
{
    int     j;
    t_path  *tmp;
    t_path  *tmp2;
    t_path  *old_path;
    t_path  *new_path;

    tmp = (t_path*)malloc(sizeof(t_path));
    tmp2 = (t_path*)malloc(sizeof(t_path));
    old_path = &solution->paths[i];
    new_path = &solution->paths[solution->nbr_paths];
    copy_path(old_path, tmp);
    j = -1;
    old_path->path = (int*)malloc(solution->size * sizeof(int));
    old_path->depths = (int*)malloc(solution->size * sizeof(int));
    while (++j <= pos)
    {
        old_path->path[j] = new_path->path[j];
        old_path->depths[j] = new_path->depths[j];
    }
    j = 0;
    while (p + j < tmp->depth)
    {
        old_path->path[pos + j] = tmp->path[p + j];
        old_path->depths[pos + j] = tmp->depths[p + j];
        j++;
    }
    old_path->depth = pos + j;
    old_path->endpoint = solution->size - 1;
    j = -1;
    copy_path(new_path, tmp2);
    while (++j < p)
    {
        new_path->path[j] = tmp->path[j];
        new_path->depths[j] = tmp->depths[j];
        solution->used_vertices[new_path->path[j]][0] = 1;
        solution->used_vertices[new_path->path[j]][1] = solution->nbr_paths;
        solution->used_vertices[new_path->path[j]][2] = j;
    }
    j = 0;
    while (pos + j + 2 < tmp2->depth)
    {
        new_path->path[p + j] = tmp2->path[pos + j + 2];
        new_path->depths[p + j] = tmp2->depths[pos + j + 2];
        j++;
    }
    new_path->depth = p + j;
    new_path->endpoint = solution->size - 1;
    reset_path(tmp);
    reset_path(tmp2);
    j = -1;
    while (++j < old_path->depth)
    {
        solution->used_vertices[old_path->path[j]][0] = 1;
        solution->used_vertices[old_path->path[j]][1] = i;
        solution->used_vertices[old_path->path[j]][2] = j;
    }
}

void        update_solution(t_path *path, t_solution *solution, t_path **possible)
{
    int i;
    int j;
    t_path *new_path;

    new_path = &solution->paths[solution->nbr_paths];
    copy_path(path, new_path);
    i = 1;
    while (i < new_path->depth - 1)
    {
        if (solution->used_vertices[new_path->path[i]][0] != 0
            && solution->used_vertices[new_path->path[i]][1] != solution->nbr_paths)
        {
            merge_paths(solution, i, solution->used_vertices[new_path->path[i]][1], solution->used_vertices[new_path->path[i]][2]);
            i = 1;
        }
        else
            i++;
    }
    i = -1;
    while (++i < new_path->depth)
    {
        solution->used_vertices[new_path->path[i]][0] = 1;
        solution->used_vertices[new_path->path[i]][1] = solution->nbr_paths;
        solution->used_vertices[new_path->path[i]][2] = i;
    }
    solution->nbr_paths += 1;
    i = 0;
    while (possible[i])
        i++;
    possible[i] = (t_path*)malloc( (solution->nbr_paths + 1) * sizeof(t_path));
    j = -1;
    while (++j < solution->nbr_paths)
        copy_path(&solution->paths[j], &possible[i][j]);
    possible[i + 1] = NULL;
}