/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Aurelien <Aurelien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:49:39 by auguyon           #+#    #+#             */
/*   Updated: 2019/11/19 18:07:36 by Aurelien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "../libft/inc/libft.h"

#include <stdio.h>

typedef struct      s_link
{
	struct s_link   *next;
	struct s_btree 	*adr;
    char            *name;
}                   t_link;

typedef struct      s_btree 
{
    struct s_btree  *left;
	struct s_btree  *right;
    struct s_link	*link;
	char 			*name;
    int             height;
	int				x;
	int				y;
    int             nb;
}                   t_btree;

typedef struct 		s_parse
{
	char            *f_room;
	char			*s_room;
    int    			x;
    int    			y;
}					t_parse;

typedef	struct		s_info
{
	struct s_btree 	*adr_start;
	struct s_btree 	*adr_end;
	struct s_parse	*parse;
	unsigned int	ants;
	unsigned int	best_move;
}					t_info;

typedef struct s_data
{
    int         *nbr;
    int         **tab;
    int         *x;
    int         *y;
    char        **name;
    int         ants;
    int         nb_rooms;
    int         best_move;
}               t_data;

void				get_info_link(t_parse *parse, char *line);
void				btree_add_data(t_btree *start, t_btree *groot, char *find, char *room);
t_btree 			*add_room(t_btree *groot, t_info *info, char *line, short *code);
t_btree				*btree_rotate(t_btree *t, char *name);
int					height(t_btree *n);
t_btree				*btree_search(t_btree *groot, char *find);
int					check_error_room(t_btree *groot, char *line);
int					check_error_link(t_btree *groot, t_info *info, char *line);
void				check_error(t_info *info, t_btree *groot, short error);
void				btree_apply_postfix_lr(t_btree *root, void (*applyf)(t_btree *));

#endif
