/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm norm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 09:39:54 by ftrujill          #+#    #+#             */
/*   Updated: 2019/12/11 23:46:14 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

void        update(t_layer *new_layer, int *visited, int *updated)
{
    int i;
    int j;
    int k;
    int n;
    int depth;

    i = -1;
    n = new_layer->nbr_paths;
    while (++i < new_layer->size)
    {
        if (updated[i] == 0)
            continue ;
        j = -1;
        while (++j < n)
        {
            depth = new_layer->paths[j].depth;
            k = -1;
            while (++k < depth)
            {
                if (new_layer->paths[j].path[k] == i && new_layer->paths[j].depths[k] > visited[i])
                        new_layer->paths[j].endpoint = new_layer->size;
            }
        }
    }
}

void        min_depth(t_layer *layer)
{
    int i;

    i = -1;
    layer->min_depth = layer->size;
    while (++i < layer->nbr_paths)
    {
        if (layer->paths[i].endpoint != layer->size)
            layer->min_depth = ft_min(layer->min_depth,
                layer->paths[i].depths[layer->paths[i].depth - 1]);
    }
}

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

void         find_solution(t_path **possible, int n, int *nbr_steps, int *sol)
{
    int     i;
    int     j;
    int     sum_lengths;
    int     max_length;
    int     aux;

    i = 1;
    *sol = 0;
    *nbr_steps = n + possible[0][0].depth - 2;
    while (possible[i])
    {
        j = 0;
        sum_lengths = 0;
        max_length = possible[0][0].depth;
        while (j <= i)
        {
            sum_lengths += possible[i][j].depth;
            max_length = ft_max(max_length, possible[i][j++].depth);
        }
        if ((i + 1) * max_length < n + sum_lengths)
        {
            aux = ((n + sum_lengths) % (i + 1) == 0) ? (n + sum_lengths) / (i + 1) - 2 : (n + sum_lengths) / (i + 1) - 1;
            if (aux < *nbr_steps)
            {
                *nbr_steps = aux;
                *sol = i;
            }
        }
        i++;
    }
}

void        prt_just_path(t_path *path)
{
    int i;
    
    i = 0;
    while (i < path->depth)
        ft_printf("%d ", path->path[i++]);
    ft_printf("\n");
}      

int         *path_numbers(t_path **possible, int nbr_ants, int nbr_steps, int sol)
{
    int     *tab;
    int     i;
    int     j;
    int     ant;
    int     available_paths;

    tab = (int*)malloc(sizeof(int) * nbr_ants);
    i = -1;
    ant = 0;
    available_paths = sol + 1;
    while (++i < nbr_steps - possible[sol][0].depth + 2)
    {
        j = -1;
        while (++j < available_paths)
        {
            tab[ant] = j % (available_paths);
            ant++;
            if (ant >= nbr_ants)
                break;
        }
        if (ant >= nbr_ants)
            break;
        j = available_paths;
        while (--j >= 0)
        {
            if (nbr_steps - i < possible[sol][j].depth)
                available_paths--;
        }
    }
    return (tab);
}

int         *ant_first_app(t_path **possible, int nbr_ants, int nbr_steps, int sol)
{
    int     *tab;
    int     i;
    int     j;
    int     ant;
    int     available_paths;

    tab = (int*)malloc(sizeof(int) * nbr_ants);
    i = -1;
    ant = 0;
    available_paths = sol + 1;
    while (++i < nbr_steps - possible[sol][0].depth + 2)
    {
        j = -1;
        while (++j < available_paths)
        {
            tab[ant] = i;
            ant++;
            if (ant >= nbr_ants)
                break;
        }
        if (ant >= nbr_ants)
            break;
        j = available_paths;
        while (--j >= 0)
        {
            if (nbr_steps - i < possible[sol][j].depth)
                available_paths--;
        }
    }
    return (tab);
}

void        prt_steps(t_path **possible, int nbr_ants, int nbr_steps, int sol)
{
    int i;
    int j;
    int f;
    int *path_nbrs;
    int *ant_first;

    i = 0;
    f = sol + 1;
    path_nbrs = path_numbers(possible, nbr_ants, nbr_steps, sol);
    ant_first = ant_first_app(possible, nbr_ants, nbr_steps, sol);
    while (i < nbr_steps)
    {
        j = -1;
        while(++j < f)
        {
            if (j >= nbr_ants || i - ant_first[j] > possible[sol][path_nbrs[j]].depth - 2)
                continue;
            else
                ft_printf("L%d-%d ", j, possible[sol][path_nbrs[j]].path[i - ant_first[j] + 1]);
        }
        ft_printf("\n");
        j = -1;
        while (++j <= sol)
            f = (nbr_steps - i < possible[sol][j].depth) ? f : f + 1;
        i++;
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

void        fill_new_layer_used_edge(t_layer *new_layer, t_path *path,
                int *visited, int w)
{
    int j;
    int n;

    j = -1;
    n = new_layer->nbr_paths;
    while (++j < path->depth)
    {
        new_layer->paths[n].path[j] = path->path[j];
        new_layer->paths[n].depths[j] = path->depths[j];
    }
    new_layer->paths[n].path[j] = w;
    new_layer->paths[n].depths[j] = path->depths[j - 1] + 1 - 3;
    new_layer->paths[n].depth = path->depth + 1;
    new_layer->paths[n].endpoint = w;
    new_layer->nbr_paths += 1;
    if (w == new_layer->size - 1)
        if (new_layer->sol_depth > path->depth + 1)
            new_layer->sol_depth = path->depth + 1;
    if (w != new_layer->size - 1)
        visited[w] = path->depth + 1;
}

void        fill_new_layer(t_layer *new_layer, t_path *path,
                int *visited, int w)
{
    int j;
    int n;

    j = -1;
    n = new_layer->nbr_paths;
    while (++j < path->depth)
    {
        new_layer->paths[n].path[j] = path->path[j];
        new_layer->paths[n].depths[j] = path->depths[j];
    }
    new_layer->paths[n].path[j] = w;
    new_layer->paths[n].depths[j] = path->depths[j - 1] + 1;
    new_layer->paths[n].depth = path->depth + 1;
    new_layer->paths[n].endpoint = w;
    new_layer->nbr_paths += 1;
    if (w == new_layer->size - 1)
        if (new_layer->sol_depth > path->depth + 1)
            new_layer->sol_depth = path->depth + 1;
    if (w != new_layer->size - 1)
        visited[w] = path->depth + 1;
}

void        add_path_used_edge(t_layer *new_layer, t_path *path,
                int *visited, int w)
{
    int n;
    int j;

    if (path->endpoint == new_layer->size - 1
        && path->depths[path->depth - 1] >= new_layer->sol_depth)
        return ;
    else if (path->endpoint == new_layer->size - 1)
    {
        copy_solution(new_layer, path);
        return ;
    }
    n = new_layer->nbr_paths;
    if (!(new_layer->paths[n].path =
        (int*)malloc((path->depth + 1) * sizeof(int)))
        || !(new_layer->paths[n].depths =
            (int*)malloc((path->depth + 1) * sizeof(int))))
        ft_malloc_error();
    fill_new_layer_used_edge(new_layer, path, visited, w);
}

void        add_path(t_layer *new_layer, t_path *path,
                int *visited, int w)
{
    int n;
    int j;

    if (path->endpoint == new_layer->size - 1
        && path->depths[path->depth - 1] >= new_layer->sol_depth)
        return ;
    else if (path->endpoint == new_layer->size - 1)
    {
        copy_solution(new_layer, path);
        return ;
    }
    n = new_layer->nbr_paths;
    if (!(new_layer->paths[n].path =
        (int*)malloc((path->depth + 1) * sizeof(int)))
        || !(new_layer->paths[n].depths =
            (int*)malloc((path->depth + 1) * sizeof(int))))
        ft_malloc_error();
    fill_new_layer(new_layer, path, visited, w);
}

/*
void        i_step(t_layer *layer, int *visited,
    t_solution *solution, int *updated)
{

}
*/

t_layer     *next_layer(t_data *dt, t_layer *layer,
    int *visited, t_solution *solution)
{
    int         i;
    int         j;
    int         *updated;
    t_path      *path;
    t_layer     *new_layer;

    if (!(updated = (int*)ft_memalloc(layer->size * sizeof(int)))
        || !(new_layer = (t_layer*)malloc(sizeof(t_layer))))
        ft_malloc_error();
    initialize_new_layer(new_layer, layer, dt->nbr);
    i = -1;
    while (++i < layer->nbr_paths)
    {
        path = &(layer->paths[i]);
        if (updated[path->endpoint] != 0 || path->endpoint == layer->size)
            continue ;
        if (path->endpoint == layer->size - 1 
            && path->depths[path->depth - 1] < new_layer->sol_depth)
        {
            add_path(new_layer, path, visited, layer->size - 1);
            visited[layer->size - 1] = path->depth;
            updated[layer->size - 1] = 1;
            continue;
        }
        if (path->endpoint == layer->size - 1)
            continue ;
        if (path->depth > 1 && solution->used_vertices[path->endpoint][0]
            && !solution->used_vertices[path->path[path->depth - 2]][0])
        {
            add_path_used_edge(new_layer, path, visited,
                solution->paths[solution->used_vertices[path->endpoint][1]]
                .path[(solution->used_vertices[path->endpoint][2]) - 1]);
            continue ;
        }
        j = -1;
        while (dt->tab[path->endpoint][++j] != -1)
        {
            if (path->endpoint == 0
                && solution->used_vertices[dt->tab[path->endpoint][j]][0])
                continue ;
            if (visited[dt->tab[path->endpoint][j]] == 0)
                add_path(new_layer, path, visited, dt->tab[path->endpoint][j]);
            else if (visited[dt->tab[path->endpoint][j]] > path->depth + 1)
            {
                add_path(new_layer, path, visited, dt->tab[path->endpoint][j]);
                updated[dt->tab[path->endpoint][j]] = 1;
            }
        }
    }
    update(new_layer, visited, updated);
    min_depth(new_layer);
    return (new_layer);
}

int        mbfs(t_data *dt, t_solution *solution, t_layer *layer, t_path **possible)
{
    int     *visited;

    if (!(visited = (int*)ft_memalloc(layer->size * sizeof(int))))
        ft_malloc_error();
    visited[0] = 1;
    while((layer->sol_depth == layer->size + 1
        || layer->min_depth < layer->sol_depth + solution->max_length
        || layer->nbr_paths > 1))
    {
        if (layer->nbr_paths == 0)
            return (0);
        layer = next_layer(dt, layer, visited, solution);
    }
    update_solution(layer->paths, solution, possible);
    return (1);
}   

int         solver_2(t_data *dt, t_layer *layer, t_solution *solution, t_path **possible)
{
    int         sol;
    int         nbr_steps;

    prt_g(dt->tab, dt->nb_rooms);

    while (mbfs(dt, solution, layer, possible))
    {
    }
    prt_possible(possible);
    find_solution(possible, dt->ants, &nbr_steps, &sol);
    ft_printf("\nAnd the right solution with %d ants is the one with %d path(s) and it takes %d step(s)\n\n", dt->ants, sol + 1, nbr_steps);
    prt_steps(possible, dt->ants, nbr_steps, sol);
    return (0);
}

int         solver(t_data *dt)
{
    int         i;
    t_layer     *layer;
    t_solution  *solution;
    t_path      **possible;

    if (!(solution = (t_solution*)malloc(sizeof(t_solution)))
        || !(solution->used_vertices = (int**)malloc(dt->nb_rooms * sizeof(int*)))
        || !(solution->paths = (t_path*)malloc(dt->nb_rooms * sizeof(t_path)))
        || !(possible = (t_path**)malloc(dt->nb_rooms * sizeof(t_path*)))
        || !(layer = (t_layer*)malloc(sizeof(t_layer))))
        ft_malloc_error();
    i = 0;
    while (i < dt->nb_rooms)
    {
        if (!(solution->used_vertices[i] = (int*)malloc(3 * sizeof(int))))
            ft_malloc_error();
        solution->used_vertices[i++][0] = 0;
    }
    solution->max_length = 0;
    solution->nbr_paths = 0;
    solution->size = dt->nb_rooms;   
    possible[0] = NULL;
    initialize(layer, dt->nb_rooms);
    return (solver_2(dt, layer, solution, possible));
}
