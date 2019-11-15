/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:47:57 by auguyon           #+#    #+#             */
/*   Updated: 2019/11/12 22:50:38 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

static void	parse_link(t_info *info, t_btree *groot, char *line, short error)
{
	if (error == 2)
		error = 1;
	while (line || get_next_line(0, &line))
	{
		if (error == 1)
			error = check_error_link(groot, info, line);
		if (error == 1)
		{
			get_info_link(info->parse, line);
			btree_add_data(groot, groot, info->parse->f_room, info->parse->s_room);
			free(info->parse->f_room);
			free(info->parse->s_room);
		}
		free(line);
		ft_putendl(line);
		line = NULL;
	}
	if (line != NULL)
		free(line);
}

static int	get_ants(short *error, char *line)
{
	int 	i;

	i = 0;
	while (ft_isdigit(line[i]))
				i++;
	if (line[i] != '\0' || (line[0] == '0' && line[1] == '\0'))
	{
		*(error) = -6; // no ants
		return (1);
	}
	*(error) = 1;
	return (ft_atoi(line));
}


void	print_list(t_link *l)
{
	while (l->next != NULL)
	{
		printf("Name link->%s name adr->%s\n", l->name, l->adr->name);
		l = l->next;
	}
	printf("Name link->%s name adr->%s\n", l->name, l->adr->name);
}

void	print_btree(void *n)
{
	t_btree *t;

	t = (t_btree*)n;
	write(1, "\nBranch-> ", 9);
	write(1, t->name, ft_strlen(t->name));
	write(1, "\n", 1);
	print_list(t->link);
}


void	btree_apply_prefix_lr(t_btree *root, void (*applyf)(void *))
{
	if (root && applyf)
	{
		if (root)
		{
			applyf(root);
		}
		if (root->left)
        {
            // write(1, "DOWN LEFT\n", 10);
			btree_apply_prefix_lr(root->left, applyf);
            // write(1, "UP LEFT\n", 8);
        }
		if (root->right)
        {
            // write(1, "DOWN RIGHT\n", 11);
			btree_apply_prefix_lr(root->right, applyf);
            // write(1, "UP RIGHT\n", 9);
		}
	}
}

t_btree 	*parse(t_info *info, char *line, short error, short code)
{
	t_btree	*groot;

	groot = NULL;
	while (get_next_line(0, &line))
	{
		if (error == 1 && line[0] != '#' && line[1] != '#')
			if ((error = check_error_room(groot, line)) == 2)
				break ;
		if (info->ants == 0)
			info->ants = get_ants(&error, line);
		else if (error == 1 && line[0] == '#' && line[1] == '#')
		{
			if (ft_strccmp(line, "##start") == 0)
				code = 1;
			else if (ft_strccmp(line, "##end") == 0)
				code = 2;
		}
		else if (error == 1)
			groot = add_room(groot, info, line, &code);
		ft_putendl(line);
		free(line);
	}
	parse_link(info, groot, line, error);
	// btree_apply_prefix_lr(groot, &print_btree);
	check_error(info, groot, error);
	return (groot);
}



int 	main(void)
{
	t_info	*info;
	t_btree	*groot;

	if (!(info = (t_info*)malloc(sizeof(t_info))))
		exit(0);
	ft_bzero(info, sizeof(t_info));
	if (!(info->parse = (t_parse*)malloc(sizeof(t_parse))))
		exit(0);
	ft_bzero(info->parse, sizeof(t_parse));
	groot = parse(info, NULL, 0, 0);
	// printf("\n---print---\n\n");
	// printf("number of ants-> {%d} && move-> {%d}\n", info->ants, info->best_move);
// btree_apply_prefix_lr(groot, &print_btree);
	return (1);
}
