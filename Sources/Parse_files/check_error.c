/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:47:57 by auguyon           #+#    #+#             */
/*   Updated: 2020/01/10 15:51:56 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

static int	verif_room_name(t_btree *groot, char *line)
{
	char	*name;
	int		j;

	j = 0;
	name = ft_strcdup(line, '-');
	if (btree_search_name(groot, &j, name) && j == 0)
	{
		free(name);
		return (-5);
	}
	free(name);
	name = ft_strdup(line + (ft_strclen(line, '-') + 1));
	if (btree_search_name(groot, &j, name) && j == 0)
	{
		free(name);
		return (-5);
	}
	free(name);
	return (1);
}

static int	its_comment(char *line, unsigned int *best_move)
{
	int		i;

	if (line[0] == '#' && line[1] == '#')
		return (3);
	else if ((i = ft_strspn("#Here is the number of lines required: ", line)) == 39)
	{
		*(best_move) = ft_atoi(&line[i]);
		return (3);
	}
	return (1);
}

int			check_error_link(t_btree *groot, t_info *info)
{
	if (info->line[0] == '#')
		return (its_comment(info->line, &(info->best_move)));
	if (ft_count_c(info->line, '-') > 1)
		return (-3);
	if (ft_count_c(info->line, '-') == 0)
		return (-11);
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
	if (btree_search_name(groot, &j, name) && j == 1)
	{
		free(name);
		return (-8);
	}
	free(name);
	if (btree_search_pos(groot, &j, x, y) && j == 1)
		return (-9);
	return (1);
}

int			check_error_room(t_btree *groot, t_info *in, int y)
{
	int		i;

	if (in->line[0] == '#')
		return (its_comment(in->line, &(in->best_move)));
	if (ft_count_c(in->line, '-') == 1)
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
