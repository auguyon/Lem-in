/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:47:57 by auguyon           #+#    #+#             */
/*   Updated: 2019/11/08 19:38:28 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lemin.h"

int height(t_btree *n) 
{ 
	if (n == NULL) 
		return (0); 
	return (n->height); 
} 

int get_balance(t_btree *n) 
{ 
	if (n == NULL) 
		return (0); 
	return (height(n->left) - height(n->right)); 
} 

t_btree *btree_new(t_info *info, short *code)
{
    t_btree     *new;
    t_link      *link;

    if (!(new = (t_btree*)malloc(sizeof(t_btree))))
        exit(0);
    ft_bzero(new, sizeof(t_btree));
    new->height = 1;
    new->name = info->parse->f_room;
    new->x = info->parse->x;
    new->y = info->parse->y;
    if (*(code) == 1)
        info->adr_start = new;
    else if (*(code) == 2)
        info->adr_end = new;
    if (*(code))
        *(code) = 0;
    return (new);
}

t_btree *right_rotate(t_btree *t) 
{ 
    t_btree *tmp_l;
	t_btree *tmp;

    tmp_l = t->left;
    tmp = tmp_l->right;
    tmp_l->right = t;
    t->left = tmp;
    t->height = ft_max(height(t->left), height(t->right)) + 1;
    tmp_l->height = ft_max(height(tmp_l->left), height(tmp_l->right)) + 1; 
	return (tmp_l);
} 

t_btree *left_rotate(t_btree *t) 
{ 
	t_btree *tmp_r;
	t_btree *tmp;

    tmp_r = t->right;
    tmp = tmp_r->left;
    tmp_r->left = t;
    t->right = tmp;
    t->height = ft_max(height(t->left), height(t->right)) + 1;
    tmp_r->height = ft_max(height(tmp_r->left), height(tmp_r->right)) + 1; 
	return (tmp_r); 
}

t_btree *btree_rotate(t_btree *t, char *name)
{
    int balance;

    balance = get_balance(t);
    if (balance > 1 && ft_strcmp(t->left->name, name) > 0)
		return (right_rotate(t));
	else if (balance < -1 && ft_strcmp(t->right->name, name) < 0)
		return (left_rotate(t));
	else if (balance > 1 && ft_strcmp(t->left->name, name) < 0)
    {
		t->left = left_rotate(t->left); 
		return (right_rotate(t));
	} 
	else if (balance < -1 && ft_strcmp(t->right->name, name) > 0)
	{
		t->right = right_rotate(t->right);
		return (left_rotate(t));
	}
    return(t);
}

t_btree *btree_add_room(t_btree *t, t_info *info, short *code)
{
    int ret_cmp;

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

// int		check_error_room(char *line)
// {
// 	int		i;

// 	i = 0;
// 	while (line[i] != ' ')
// }

void	get_info_room(char *line, t_parse *parse, int i_end)
{
	int i;

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

t_btree *add_room(t_btree *groot, t_info *info, char *line, short *code)
{
	get_info_room(line, info->parse, ft_strlen(line));
	groot = btree_add_room(groot, info, code);
	return (groot);
}

void	put_link(t_btree *groot, t_link **link, char *name)
{
    t_link  *new;
    t_link  *current;

    current = *link;
    if (!(new = (t_link*)malloc(sizeof(t_link))))
        exit(0);
    ft_bzero(new, sizeof(t_link));
    new->adr = groot;
    new->name = name;
    if (current)
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
	else
		current = new;
}

void	btree_search_data(t_btree *groot, char *find, char *room, int (*ft_strcmp)(const char *, const char *))
{
	int i = 0;

	if (groot == NULL)
		return ;
	if (ft_strcmp(groot->name, find) > 0)
		return (btree_search_data(groot->left, find, room, ft_strcmp));
	else if ((i = ft_strcmp(groot->name, find)) < 0)
		return (btree_search_data(groot->right, find, room, ft_strcmp));
	put_link(groot, &groot->link, room);
}

void	btree_add_link(t_btree *groot, t_info *info)
{
	printf("PUTEPUTEPUTE\n");
	btree_search_data(groot, info->parse->f_room, info->parse->s_room, &ft_strcmp);
	btree_search_data(groot, info->parse->s_room, info->parse->f_room, &ft_strcmp);
}

void	get_info_link(t_parse *parse, char *line)
{
	int i;

	i = ft_strclen(line, '-');
	parse->f_room = ft_strndup(line, i);
	parse->s_room = ft_strdup(line + i + 1);
}

t_btree *parse(t_info *info, char *line, int i, short code)
{
    t_btree *groot;

    groot = NULL;
    while (get_next_line(0, &line))
    {
		// if (check_error_room(line))
		// 	return (free_n_quit(info, map, -2));
		if (info->adr_end && ft_strchr(line, '-'))
			break ;
		if (info->ants == 0) // fct a part
		{
			while (ft_isdigit(line[i]))
				i++;
			if (line[i] != '\0' || (line[0] == '0' && line[1] == '\0'))
				exit(0);
				// return (free_n_quit(info, map, -1));
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
			groot = add_room(groot, info, line, &code);
		free(line);
	}
	// verif
	while (line || get_next_line(0, &line))
	{
		// if (check_error_link(line))
		// 	return (free_n_quit(info, map, -2));
		get_info_link(info->parse, line);
		btree_add_link(groot, info);
		free(line);
		line = NULL;
	}
	return (groot);
}

void	print_btree(void *n)
{
	write(1, n, ft_strlen((char*)n));
	write(1, "\n", 1);
}

void	btree_apply_prefix_lr(t_btree *root, void (*applyf)(void *))
{
	if (root && applyf)
	{
		if (root->name)
		{
			printf("%s\t", root->link->name);
			applyf(root->name);
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

void	btree_apply_postfix_lr(t_btree *root, void (*applyf)(void *))
{
	if (root && applyf)
	{
		if (root->left)
			btree_apply_postfix_lr(root->left, applyf);
		if (root->right)
			btree_apply_postfix_lr(root->right, applyf);
		if (root->name)
			applyf(root->name);
	}
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
	printf("---print---\n");
	btree_apply_prefix_lr(groot, &print_btree);
	return (1);
}
