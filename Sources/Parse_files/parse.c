/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:47:57 by auguyon           #+#    #+#             */
/*   Updated: 2019/12/05 22:31:21 by auguyon          ###   ########.fr       */
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

void		parse_link(t_info *in, t_btree *groot)
{
	if (in->error == 2)
		in->error = 1;
	while (in->line || get_next_line(0, &in->line))
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
		free(in->line);
		ft_putendl(in->line);
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

t_btree		*parse_room(t_info *in, short code)
{
	t_btree	*groot;

	groot = NULL;
	while (get_next_line(0, &in->line))
	{
		if (in->error == 1 && in->line[0] != '#' && in->line[1] != '#')
			if ((in->error = check_error_room(groot, in->line)) == 2)
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

// void	print_list(t_link *l)
// {
// 	while (l->next != NULL)
// 	{
// 		printf("Name link->%s name adr->%s\n", l->name, l->adr->name);
// 		l = l->next;
// 	}
// 	printf("Name link->%s name adr->%s\n", l->name, l->adr->name);
// }

// void	print_btree(void *n)
// {
// 	t_btree *t;

// 	t = (t_btree*)n;
// 	write(1, "\nBranch-> ", 9);
// 	write(1, t->name, ft_strlen(t->name));
// 	write(1, "\n", 1);
// 	print_list(t->link);
// }

// void	btree_apply_prefix_lr(t_btree *root, void (*applyf)(void *))
// {
// 	if (root && applyf)
// 	{
// 		if (root)
// 		{
// 			applyf(root);
// 		}
// 		if (root->left)
// 		{
// 			write(1, "DOWN LEFT\n", 10);
// 			btree_apply_prefix_lr(root->left, applyf);
// 			write(1, "UP LEFT\n", 8);
// 		}
// 		if (root->right)
// 		{
// 			write(1, "DOWN RIGHT\n", 11);
// 			btree_apply_prefix_lr(root->right, applyf);
// 			write(1, "UP RIGHT\n", 9);
// 		}
// 	}
// }
