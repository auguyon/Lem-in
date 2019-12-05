/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:47:57 by auguyon           #+#    #+#             */
/*   Updated: 2019/12/05 22:49:26 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

static int	verif_room_name(t_btree *groot, char *line)
{
	char	*name;

	name = ft_strcdup(line, '-');
	if (btree_search(groot, name) == NULL)
	{
		free(name);
		return (-5);
	}
	free(name);
	name = ft_strdup(line + (ft_strclen(line, '-') + 1));
	if (btree_search(groot, name) == NULL)
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

static int	check_error_room_two(t_btree *groot, char *line, int i)
{
	char	*name;
	int		j;

	j = 0;
	while (j <= i)
	{
		if (line[j] == '-')
			return (-3);
		j++;
	}
	name = ft_strndup(line, i);
	if (btree_search(groot, name) != NULL)
	{
		free(name);
		return (-8);
	}
	free(name);
	return (1);
}

int			check_error_room(t_btree *groot, char *line)
{
	int		i;

	if (ft_count_c(line, '-') == 1)
		if (verif_room_name(groot, line) == 1)
			return (2);
	if (!(i = ft_strlen(line)))
		return (-4);
	if (!ft_isdigit(line[i - 1]))
		return (-1);
	while (line[i] != ' ')
		i--;
	i--;
	if (!ft_isdigit(line[i]))
		return (-1);
	while (line[i] && line[i] != ' ')
		i--;
	if (i <= 0)
		return (-2);
	return (check_error_room_two(groot, line, i));
}