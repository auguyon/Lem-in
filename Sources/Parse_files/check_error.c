/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <ftrujill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:47:57 by auguyon           #+#    #+#             */
/*   Updated: 2020/01/15 18:38:05 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

static int	verif_room_name(t_btree *groot, char *line)
{
	char	*name;
	int		j;

	j = 0;
	name = ft_strcdup(line, '-');
	printf("name->{%s}\n", name);
	if (btree_search_name(groot, &j, name) && j == 0)
	{
		free(name);
		return (-5);
	}
	free(name);
	name = ft_strdup(line + (ft_strclen(line, '-') + 1));
	printf("name->{%s}\n", name);
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
	else if ((i = ft_strspn("#Here is the number of lines required: ", line))
				== 39)
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

static int	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return(1);
}

int			check_error_room(t_btree *groot, t_info *in, int j, int i)
{
	char	**tab;

	if (in->line[0] == '#')
		return (its_comment(in->line, &(in->best_move)));
	if (ft_count_c(in->line, '-') == 1 && ft_count_c(in->line, ' ') != 2)
		return (2);
	if (!(ft_strlen(in->line)))
		return (-4);
	tab = ft_strsplit(in->line, ' ');
	if (ft_count_c(tab[0], '-'))
		return (-3);
	if (btree_search_name(groot, &j, tab[0]) && j == 1)
		return (-8);
	if (!(j = 0) && !tab[1] && !tab[2])
		return (-1);
	i = ft_isint(tab[1]);
	j = ft_isint(tab[2]);
	if ((i != 1 && i != 2) && (j != 1 && j != 2))
		return (-10);
	in->x = ft_utoi(tab[1]);
	in->y = ft_utoi(tab[2]);
	if (!(j = 0) && btree_search_pos(groot, &j, in->x, in->y) && j == 1)
		return (-9);
	return (free_tab(tab));
}























