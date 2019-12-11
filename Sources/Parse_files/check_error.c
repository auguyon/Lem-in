/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:47:57 by auguyon           #+#    #+#             */
/*   Updated: 2019/12/11 18:18:24 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

static int	verif_room_name(t_btree *groot, char *line)
{
	char	*name;
	int		j;

	j = 0;
	name = ft_strcdup(line, '-');
	btree_search_name(groot, &j, name);
	if (j == 0)
	{
		free(name);
		return (-5);
	}
	free(name);
	name = ft_strdup(line + (ft_strclen(line, '-') + 1));
	btree_search_name(groot, &j, name);
	if (j == 0)
	{
		free(name);
		return (-5);
	}
	free(name);
	return (1);
}

int			check_error_link(t_btree *groot, t_info *info)
{
	char	*name;

	if (info->line[0] == '#' && info->line[1] == 'H')
	{
		name = info->line;
		while (!ft_isdigit(*name))
			name++;
		info->best_move = ft_atoi(name);
		return (1);
	}
	if (ft_count_c(info->line, '-') != 1)
		return (-3);
	return (verif_room_name(groot, info->line));
}

static int	check_error_room_two(t_btree *groot, char *line, int i, int y)
{
	char	*name;
	int		j;
	int		x;

	j = 0;
	x = ft_atoi(&line[i]);
	while (j <= i)
	{
		if (line[j] == '-')
			return (-3);
		j++;
	}
	j = 0;
	name = ft_strndup(line, i);
	btree_search_name(groot, &j, name);
	if (j == 1)
	{
		free(name);
		return (-8);
	}
	// btree_search_pos(groot, &j, x, y);
	// if (j == 1)
	// 	return (-9);
	free(name);
	return (1);
}

int			check_error_room(t_btree *groot, t_info *in, int y)
{
	int		i;

	if (ft_count_c(in->line, '-') == 1)
		if (verif_room_name(groot, in->line) == 1)
			return (2);
	if (!(i = ft_strlen(in->line)))
		return (-4);
	if (!ft_isdigit(in->line[i - 1]))
		return (-1);
	while (in->line[i] != ' ')
		i--;
	y = ft_atoi(&in->line[i + 1]);
	i--;
	if (!ft_isdigit(in->line[i]))
		return (-1);
	while (in->line[i] && in->line[i] != ' ')
		i--;
	if (i <= 0)
		return (-2);
	return (check_error_room_two(groot, in->line, i, y));
}

void		check_error(t_info *in, t_btree *groot)
{
	printf("Error:%d\n", in->error);
	if ((in->error <= -1 && in->error >= -3) || (in->error <= -6 && in->error >= -9))
	{
		print_error(in->error);
		free_btree_n_info(in, groot);
	}
	else if (!in->adr_start || !in->adr_end)
	{
		print_error(-7);
		free_btree_n_info(in, groot);
	}
}
