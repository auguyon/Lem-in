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

void	get_value(t_map **map, t_info *info, char *line, unsigned int size)
{
	unsigned int j;

	j = size + 1;
	while (line[j])
	{
		map[info->i]->room = ft_strncpy(map[info->i]->room, line, size);
		map[info->i]->x = ft_atoi(line + j);
		while (line[j] && line[j] != ' ')
			j++;
		map[info->i]->y = ft_atoi(line + j);
		j++;
	}
}

int		init_room(t_map *map, t_info *info, char *line)
{
	unsigned int	size;

	if (ft_countc(line, ' ') == 2)
		size = ft_strclen(line, ' ') - 1;	
	else
	{
		size = ft_strlen(line);
		while (line[size] != ' ')
			size--;
		size--;
		while (ft_isdigit(line[size]))
			size--;
	}
	if (!(map->room = (char*)malloc(sizeof(char) * size + 1)))
		exit(0);
	if (!(map->tubs = (unsigned int*)malloc(sizeof(unsigned int) * SIZE_TUBES + 1)))
		exit(0);
	return (size);
}

void	get_tubes(t_map **map, t_info *info, char *line, short *code)
{
	unsigned int	size;

	if (!(map[info->i] = (t_map*)malloc(sizeof(map))))
		exit(0);
	size = init_room(map[info->i], info, line);
	get_value(map, info, line, size);
	if (*(code) == 1)
	{
		printf("%s\n", map[info->i]->room);
		info->n_start = ft_strdup(map[info->i]->room);
		info->start = info->i;
	}
	else if (*(code) == 2)
	{
		info->n_end = ft_strdup(map[info->i]->room);
		info->end = info->i;
	}
	map[info->i]->tubs[0] = -1;
	info->i++;
	*(code) = 0;
}

void	free_n_quit(t_info *info, t_map **map, short code)
{
	if (code == -1)
	{
		free(map);
		free(info);
		write(1, "No ants\n", 8);
		exit(0);
	}
}

// int		check_error_room(char *line)
// {
// 	int		i;

// 	i = 0;
// 	while (line[i] != ' ')
// }

int		name_occurence(t_map **map, char *name)
{
	int	j;

	j = 0;
	while (map[j]->room)
	{
		if (!ft_strcmp(name, map[j]->room))
		{
			free(name);
			return (j);
		}
		j++;
	}
	free(name);
	return (0);
}

void	add_index_to_tubs(int index, int index2, t_map **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[index]->tubs[i] != -1)
		i++;
	while (map[index2]->tubs[j] != -1)
		j++;
	map[index]->tubs[i] = index2;
	map[index2]->tubs[j] = index;
	map[index]->tubs[i + 1] = -1;
	map[index2]->tubs[j + 1] = -1;
}

void	parse_link(t_info *info, t_map **map, char *line)
{
	char	*room;
	int		i;
	int		index;
	int		index2;

	i = 0;
	while (line[i])
	{
		if (line[i] == '-')
		{
			room = ft_strndup(line, i);
			if ((index = name_occurence(map, room)))
			{
				room = ft_strdup(line + i + 1);
				if ((index2 = name_occurence(map, room)))
				{
					add_index_to_tubs(index, index2, map);
					return ;
				}
			}
		}
		i++;
	}
}

void	parse(t_info *info, t_map **map)
{
	char 	*line;
	short	code;
	int		i;

	i = 0;
	while (get_next_line(0, &line))
	{
		printf("%s\n", line);
		// if (check_error_room(line))
		// 	return (free_n_quit(info, map, -2));
		if (info->end && ft_strchr(line, '-'))
			break ;
		if (!info->ants) // fct a part
		{
			while (ft_isdigit(line[i]))
				i++;
			if (line[i] != '\0' || (line[0] == '0' && line[1] == '\0'))
				return (free_n_quit(info, map, -1));
			info->ants = ft_atoi(line);
		}
		else if (line[0] == '#' && line[1] == '#')
		{
			if (ft_strccmp(line, "##start") == 0)
				code = 1;
			else if (ft_strccmp(line, "##end") == 0)
				code = 2;
		}
		else
			get_tubes(map, info, line, &code);
		free(line);
	}
	parse_link(info, map, line);
}

int 	main(int ac, char **av)
{
	t_info			*info;
	t_map			**map;

	(void)ac;
	(void)av;
	if (!(info = (t_info*)malloc(sizeof(info))) || !(map = (t_map**)malloc(sizeof(*map))))
		exit(0);
	ft_bzero(map, sizeof(t_map*));
	ft_bzero(info, sizeof(t_info*));
	parse(info, map);
	return (1);
}
