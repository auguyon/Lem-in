/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:47:57 by auguyon           #+#    #+#             */
/*   Updated: 2019/10/15 15:47:59 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/lemin.h"

#define SIZE_TUBES 30

void	get_value(t_map *map, char *line, unsigned int size, short code)
{
	unsigned int j;

	j = 0;
	while (line[j])
	{
		while (j < size)
		{
			map[map->i]->room[j] = line[j];
			j++;
		}
		j++;
		map[map->i]->x = ft_atoi(line + j);
		while (line[j] && line[j] != ' ')
			j++;
		map[map->i]->y = ft_atoi(line + j);
	}
	if (code == 1)
	{
		info->n_start = ft_strdup(map[map->i]->room);
		info->start = map->i;
	}
	else if (code == 2)
	{
		info->n_end = ft_strdup(map[map->i]->room);
		info->end = map->i;
	}
}

int		init_room(t_map *map, char *line)
{
	unsigned int	size;
	unsigned int	space;

	size = 0;
	space = 0;
	if (space = ft_countc(line, ' ') == 2)
		size = ft_strclen(line, ' ');	
	else
	{
		size = ft_strlen(line);
		while (line[size] != ' ')
			size--;
		size--;
		while (ft_isdigit(line[size]))
			size--;
	}
	if (!(map[i]->room = (char*)malloc(sizeof(char) * size + 1)))
		exit(0);
	if (!(map[i]->tubs = (char*)malloc(sizeof(char) * SIZE_TUBES + 1)))
		exit(0);
	info->end = 0;
	return (size);
}

void	get_tubes(t_map **map, t_info *info, char *line, short code)
{
	unsigned int	size;

	if (!(map[map->i] = (t_map*)malloc(sizeof(map))))
		exit(0);
	size = init_room(map[map->i], line);
	get_value(map[map->i], line, size, code);
	map->i++;
}

int		get_info(t_info *info, char *line)
{
	short	code;
	int		i;

	i = 0;
	code = 0;
	if (ft_isdigit(line[0]) && info->ants == 0)
		info->ants = ft_atoi(line);
	else if (line[0] == '#')
	{
		if (ft_strccmp(line, "##start\n") == 0)
			code = 1;
		else if (ft_strccmp(line, "##end\n") == 0)
			code = 2;
	}
	return (code);
}

int		check_comment_n_info(char *line)
{
	int	i;

	i = 0;
	if (line[0] == '#' && line[1] == '#')
		return (1);
	while (line[i] && ft_isdigit(line[i]))
	{
		i++;
		if (line[i] == '\0')
			return (1);
	}
	return (0);
}

int		check_tubes(char *line) // strcchr ?
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '-')
			return (1);
	}
	return (0);
}

// int		check_error(char *line)
// {
// 	int		i;

// 	i = 0;
// 	while (line[i] != ' ')
// }

int 	main(int ac, char **av)
{
	t_info			*info;
	t_map			**map;
	char 			*line;
	short			code;

	(void)ac;
	(void)av;
	map->i = 0;
	if (!(info = (t_info*)malloc(sizeof(info))) || !(map = (t_map**)malloc(sizeof(*map))))
		exit(0);
	while (get_next_line(0, &line))
	{
		// if (check_error(line))
		// 	return (free_n_quit());
		if (info->end)
			if (check_tubes(line))
				break ;
		if (check_comment_n_info(line))
			code = get_info(info, line);
		else
			get_tubes(map, info, line, code);
		free(line);
	}
	while (get_next_line(0, &line))
	{

	}
}
