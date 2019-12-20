/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 11:10:48 by ftrujill          #+#    #+#             */
/*   Updated: 2019/12/20 11:33:49 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

void         find_solution(t_data *dt, t_path **possible)
{
    int     i;
    int     j;
    int     s;
    int     max_length;
    int     aux;

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

void    merge_first_aux(t_solution *solution, int pos, int p, int i, t_path *tmp)
{
    int     j;
    t_path  *old_path;
    t_path  *new_path;

    old_path = &solution->paths[i];
    new_path = &solution->paths[solution->nbr_paths];
    j = -1;
    while (++j <= p)
    {
        old_path->path[j] = tmp->path[j];
        old_path->depths[j] = tmp->depths[j];
    }
    j = -1;
    while (pos + ++j < new_path->depth)
    {
        old_path->path[p + j] = new_path->path[pos + j];
        old_path->depths[p + j] = new_path->depths[pos + j];
    }
    old_path->depth = p + j;
    old_path->endpoint = solution->size - 1;
}

void    merge_third_aux(t_solution *solution, int i, int pos, int k)
{
    int     j;
    t_path  *old_path;
    t_path  *new_path;

    old_path = &solution->paths[i];
    new_path = &solution->paths[solution->nbr_paths];
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

void    merge_second_aux(t_path *tmp, t_solution *solution, int p, int pos, int i)
{
    int     j;
    int     k;
    t_path  *tmp2;
    t_path  *old_path;
    t_path  *new_path;

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
    if (k == 0)
        exit(0);
    j = -1;
    while (++j <= pos - k)
    {
        new_path->path[j] = tmp2->path[j];
        new_path->depths[j] = tmp2->depths[j];
    }
    j = -1;
    while (p + k + ++j < tmp->depth)
    {
        new_path->path[pos - k + j] = tmp->path[p + k + j];
        new_path->depths[pos - k + j] = tmp->depths[p + k + j];
    }
    new_path->depth = pos - k + j;
    new_path->endpoint = solution->size - 1;
    free_stored_path(tmp2);
    merge_third_aux(solution, i, pos, k);
}

void    merge_paths(t_solution *solution, int pos, int i, int p)
{
    int     j;
    t_path  *tmp;
    t_path  *old_path;
    t_path  *new_path;

    old_path = &solution->paths[i];
    new_path = &solution->paths[solution->nbr_paths];
    deep_copy_path(old_path, &tmp, solution->size);
    merge_first_aux(solution, pos, p, i, tmp);
    merge_second_aux(tmp, solution, p, pos, i);
    free_stored_path(tmp);
    prt_path(old_path);
    prt_path(new_path);
}
