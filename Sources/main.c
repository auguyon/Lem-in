/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:47:57 by auguyon           #+#    #+#             */
/*   Updated: 2019/12/11 23:59:28 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/lemin.h"

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
	if (t->link)
		print_list(t->link);
}

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


t_data		*parser(void)
{
	t_data		*dt;
	t_info		*info;
	t_btree		*groot;

    init_struct_parse(&dt, &info);
	groot = parse_room(info, 0);
	parse_link(info, groot);
	check_error(info, groot);
    // btree_apply_prefix_lr(groot, &print_btree);
    btree_to_data(groot, info, dt);
	free_btree_n_info(info, groot);
	return (dt);
}

void        print_truc(t_data *dt)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < dt->nb_rooms && !(j = 0))
    {
        printf("Salle->%d Name->%s Nbr de nbs->%d\n", i, dt->name[i], dt->nbr[i]);
        while(dt->tab[i][j] != -1)
            printf("->%d ", dt->tab[i][j++]);
        printf("\n");
        i++;
    }
    exit (0);
}

int         main(int argc, char **argv)
{
    t_data		*dt;

    printf("Parser\n");
	dt = parser();
    printf("Print result parse:\n");
    // print_truc(dt);
    printf("Solver\n");
	solver(dt);
    return (0);
}
