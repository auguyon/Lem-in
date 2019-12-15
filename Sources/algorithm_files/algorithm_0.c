/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Aurelien <Aurelien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 09:39:54 by ftrujill          #+#    #+#             */
/*   Updated: 2019/12/15 18:05:15 by Aurelien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

int         is_trivial(t_data *dt)
{
    int     i;
    int     n;

    i = 0;
    n = 0; 
    while (i < dt->nbr[0])
        n = (dt->tab[0][i++] == dt->nb_rooms - 1) ? 1 : n;
    if (!n)
        return (0);
    i = 0;
    while (i + 1 < dt->ants)
        ft_printf("L%d-%s ", i++, dt->name[dt->nb_rooms - 1]);
    if (dt->ants)
        ft_printf("L%d-%s", i, dt->name[dt->nb_rooms - 1]);
    ft_printf("\n");
    ft_printf("\nAnd the right solution with %d ants is the one with a trivial path"
    " and it takes 1 step\n", dt->ants);
    free_dt(dt);
    return (1);
}

int        mbfs(t_data *dt, t_solution *solution, t_path **possible)
{
    t_layer     *layer;

    initialize(&layer, dt->nb_rooms);
    while((layer->sol_depth == layer->size + 1
        || layer->min_depth < layer->sol_depth + solution->max_length
        || layer->nbr_paths > 1))
    {
        if (layer->nbr_paths == 0)
            return (0);
        next_layer(dt->tab, dt->nbr, &layer, solution);
    }
    update_solution(layer->paths, solution, possible);
    free_layer(&layer);
    return (1);
}   

void        order_possible(t_path **possible)
{
    int     i;
    int     j;
    t_path  tmp;

    i = -1;
    while (possible[++i])
    {
        j = 0;
        while (j < i)
        {
            if (possible[i][j].depth > possible[i][j + 1].depth)
                {
                    tmp = possible[i][j];
                    possible[i][j] = possible[i][j + 1];
                    possible[i][j + 1] = tmp;
                    j = 0;
                }
            else
                j++;
        }
    }
}
