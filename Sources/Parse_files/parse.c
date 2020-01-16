/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <ftrujill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:47:57 by auguyon           #+#    #+#             */
/*   Updated: 2020/01/15 18:39:43 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

static void	add_line(t_map **map, char *line, t_map **start)
{
	t_map	*new;
	t_map	*current;

	current = *map;
	if (!(new = (t_map*)malloc(sizeof(t_map))))
		ft_malloc_error();
	ft_bzero(new, sizeof(t_map));
	new->line = line;
	new->next = NULL;
	if (*map == NULL)
	{
		*map = new;
		*start = new;
	}
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

static void	get_info_link(t_info *info)
{
	int		i;

	i = ft_strclen(info->line, '-');
	info->f_room = ft_strndup(info->line, i);
	info->s_room = ft_strdup(info->line + i + 1);
}

void		parse_link(int fd, t_info *in, t_btree *groot)
{
	while (in->error == 2 || (get_next_line(fd, &in->line) && in->line))
	{
		if (in->error == 2)
			in->error = 1;
		if (in->error == 1)
			in->error = check_error_link(groot, in);
		if (in->error == 1)
		{
			get_info_link(in);
			btree_add_link(groot, groot, in->f_room, in->s_room);
			free(in->f_room);
			free(in->s_room);
		}
		in->error = (in->error == 3 ? 1 : in->error);
		if (in->error == 1)
			add_line(&(in->map), in->line, &(in->map_start));
	}
	if (in->line)
		free(in->line);
}

static int	get_ants(t_info *in)
{
	int		i;

	i = 0;
	if (ft_isint(in->line) != 2)
	{
		in->error = -6;
		return (0);
	}
	in->error = 1;
	return (ft_atoi(in->line));
}

t_btree		*parse_room(int fd, t_info *in, short code)
{
	t_btree	*groot;

	groot = NULL;
	while ((in->error == 0 || in->error == 1) &&
		get_next_line(fd, &in->line) && in->line)
	{
		printf("line->{%s}\n", in->line);
		if (in->error == 1)
			if ((in->error = check_error_room(groot, in, 0, 0)) == 2)
				break ;
		if (in->ants == 0)
			in->ants = get_ants(in);
		else if (in->error == 3)
		{
			if (ft_strccmp(in->line, "##start") == 0)
				code = 1;
			else if (ft_strccmp(in->line, "##end") == 0)
				code = 2;
		}
		else if (in->error == 1)
			groot = add_room(groot, in, &code);
		in->error = (in->error == 3 ? 1 : in->error);
		if (in->error == 1)
			add_line(&(in->map), in->line, &(in->map_start));
	}
	return (groot);
}
