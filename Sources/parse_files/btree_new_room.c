/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_new_room.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:47:57 by auguyon           #+#    #+#             */
/*   Updated: 2019/11/12 22:50:38 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

static t_btree	*btree_new(t_info *info, short *code)
{
	t_btree	*new;

	if (!(new = (t_btree*)malloc(sizeof(t_btree))))
		exit(0);
	ft_bzero(new, sizeof(t_btree));
	new->height = 1;
	new->name = info->parse->f_room;
	new->x = info->parse->x;
	new->y = info->parse->y;
	if (*(code) == 1 && !info->adr_start)
		info->adr_start = new;
	else if (*(code) == 2 && !info->adr_end)
		info->adr_end = new;
	if (*(code))
		*(code) = 0;
	return (new);
}

static t_btree	*btree_add_room(t_btree *t, t_info *info, short *code)
{
	int	ret_cmp;

	if (t == NULL)
		return (btree_new(info, code));
	if ((ret_cmp = ft_strcmp(t->name, info->parse->f_room)) == 0)
		return (t);
	if (ret_cmp > 0)
		t->left = btree_add_room(t->left, info, code);
	else
		t->right = btree_add_room(t->right, info, code);
	t->height = 1 + ft_max(height(t->left), height(t->right));
	return (btree_rotate(t, info->parse->f_room));
}

static void		get_info_room(char *line, t_parse *parse, int i_end)
{
	int	i;

	i = i_end;
	while (line[i] != ' ')
		i--;
	parse->y = ft_atoi(&line[i]);
	i--;
	while (ft_isdigit(line[i]))
		i--;
	parse->x = ft_atoi(&line[i]);
	parse->f_room = ft_strndup(line, i);
}

t_btree 	*add_room(t_btree *groot, t_info *info, char *line, short *code)
{
	get_info_room(line, info->parse, ft_strlen(line));
	groot = btree_add_room(groot, info, code);
	return (groot);
}
