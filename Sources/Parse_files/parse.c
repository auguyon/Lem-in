/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Aurelien <Aurelien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:47:57 by auguyon           #+#    #+#             */
/*   Updated: 2019/12/15 19:18:45 by Aurelien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

static void	get_info_link(t_info *info)
{
	int		i;

	i = ft_strclen(info->line, '-');
	info->f_room = ft_strndup(info->line, i);
	info->s_room = ft_strdup(info->line + i + 1);
}

void		parse_link(int fd, t_info *in, t_btree *groot)
{
	if (in->error == 2)
		in->error = 1;
	while (in->line || get_next_line(fd, &in->line))
	{
		if (in->error == 1)
			in->error = check_error_link(groot, in);
		if (in->error == 1)
		{
			get_info_link(in);
			btree_add_link(groot, groot, in->f_room, in->s_room);
			free(in->f_room);
			free(in->s_room);
		}
		ft_putendl(in->line);
		free(in->line);
		in->line = NULL;
	}
	if (in->line != NULL)
		free(in->line);
}

static int	get_ants(t_info *in)
{
	int		i;

	i = 0;
	while (ft_isdigit(in->line[i]))
		i++;
	if (in->line[i] != '\0' || (in->line[0] == '0' && in->line[1] == '\0'))
	{
		in->error = -6;
		return (1);
	}
	in->error = 1;
	return (ft_atoi(in->line));
}

t_btree		*parse_room(int fd, t_info *in, short code)
{
	t_btree	*groot;

	groot = NULL;
	in->error = 0;
	while (get_next_line(fd, &in->line))
	{
		if (in->error == 1 && in->line[0] != '#' && in->line[1] != '#')
			if ((in->error = check_error_room(groot, in, 0)) == 2)
				break ;
		if (in->ants == 0)
			in->ants = get_ants(in);
		else if (in->error == 1 && in->line[0] == '#' && in->line[1] == '#')
		{
			if (ft_strccmp(in->line, "##start") == 0)
				code = 1;
			else if (ft_strccmp(in->line, "##end") == 0)
				code = 2;
		}
		else if (in->error == 1)
			groot = add_room(groot, in, &code);
		ft_putendl(in->line);
		free(in->line);
	}
	return (groot);
}
