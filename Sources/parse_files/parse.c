/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Aurelien <Aurelien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:47:57 by auguyon           #+#    #+#             */
/*   Updated: 2019/11/27 18:54:28 by Aurelien         ###   ########.fr       */
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
            write(1, "DOWN LEFT\n", 10);
			btree_apply_prefix_lr(root->left, applyf);
            write(1, "UP LEFT\n", 8);
        }
		if (root->right)
        {
            write(1, "DOWN RIGHT\n", 11);
			btree_apply_prefix_lr(root->right, applyf);
            write(1, "UP RIGHT\n", 9);
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

void	btree_apply_prefix_count(t_btree *root, int *count)
{
	if (root)
	{
		root->nb = *(count);
		*(count) += 1;
	}
	if (root->left)
		btree_apply_prefix_count(root->left, count);
	if (root->right)
		btree_apply_prefix_count(root->right, count);
}

void	fill_to_neg(int *t, int count)
{
	int i;

	i = 0;
	while (i < count)
		t[i++] = -1;
}

void	fill_data(t_btree *groot, t_data *dt)
{
	t_btree *branch;
	t_link *link;

	dt->nbr[groot->nb] = 0;
	link = groot->link;
	branch = link->adr;
	dt->x[groot->nb] = groot->x;
	dt->y[groot->nb] = groot->y;
	dt->name[groot->nb] = ft_strdup(groot->name);
	while (link)
	{
		dt->tab[groot->nb][dt->nbr[groot->nb]] = branch->nb;
		dt->nbr[groot->nb] += 1;
		link = link->next;
		if (link)
			branch = link->adr;
	}
}

void 	count_link(t_btree *groot, int *count)
{
	t_link *tmp;
	
	*(count) = 0;
	tmp = groot->link;
	while (tmp)
	{
		*(count) += 1;
		tmp = tmp->next;
	}
}

void	add_data(t_btree *groot, t_data *dt)
{
	count_link(groot, &dt->nbr[groot->nb]);
// printf("nb_link-> {%d}\n", dt->nbr[groot->nb]);
	if (!(dt->tab[groot->nb] = (int*)malloc(sizeof(int) * dt->nbr[groot->nb] + 1)))
		exit (0);
	fill_to_neg(dt->tab[groot->nb], dt->nbr[groot->nb] + 1);
	if (dt->nbr[groot->nb])
		fill_data(groot, dt);
}

void	btree_apply_prefix_add_data(t_btree *root, t_data *dt)
{
	if (root)
	{
		if (root)
			add_data(root, dt);
		if (root->left)
			btree_apply_prefix_add_data(root->left, dt);
		if (root->right)
			btree_apply_prefix_add_data(root->right, dt);
	}
}

void	btree_to_data(t_btree *groot, t_info *info, t_data *dt)
{
	btree_apply_prefix_count(groot, &dt->nb_rooms);
	if (!(dt->tab = (int**)malloc(sizeof(int*) * dt->nb_rooms + 1)))
		exit (0);
	if (!(dt->name = (char**)malloc(sizeof(char*) * dt->nb_rooms + 1)))
		exit (0);
	if (!(dt->x = (int*)malloc(sizeof(int) * dt->nb_rooms + 1)))
		exit (0);
	fill_to_neg(dt->x, dt->nb_rooms + 1);
	if (!(dt->y = (int*)malloc(sizeof(int) * dt->nb_rooms + 1)))
		exit (0);
	fill_to_neg(dt->y, dt->nb_rooms + 1);
	if (!(dt->nbr = (int*)malloc(sizeof(int) * dt->nb_rooms + 1)))
		exit (0);
	fill_to_neg(dt->nbr, dt->nb_rooms + 1);
	btree_apply_prefix_add_data(groot, dt);
}

int 	main(void)
{
	t_data	*data;
	t_info	*info;
	t_btree	*groot;

	if (!(info = (t_info*)malloc(sizeof(t_info))))
		exit(0);
	ft_bzero(info, sizeof(t_info));
	if (!(info->parse = (t_parse*)malloc(sizeof(t_parse))))
		exit(0);
	ft_bzero(info->parse, sizeof(t_parse));
	if (!(data = (t_data*)malloc(sizeof(t_data))))
		exit(0);
	ft_bzero(data, sizeof(t_data));
	groot = parse(info, NULL, 0, 0);
	btree_to_data(groot, info, data);
	// printf("\n---print---\n\n");
	// printf("number of ants-> {%d} && move-> {%d}\n", info->ants, info->best_move);
	// btree_apply_prefix_lr(groot, &print_btree);
	int i = 0;
	int j = 0;
	while(i < data->nb_rooms)
	{
		printf("Name->%s salle->%d x->%d y->%d nbr->%d\n", data->name[i], i, data->x[i], data->y[i], data->nbr[i]);
		while (data->tab[i][j] != -1)
		{
			printf("dans tab -> %s -> %d\n", data->name[data->tab[i][j]], data->tab[i][j]);
			j++;
		}
		printf("Next tab \n\n");
		j =0;
		i++;
	}
	
	return (1);
}
