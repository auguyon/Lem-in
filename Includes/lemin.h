/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:49:39 by auguyon           #+#    #+#             */
/*   Updated: 2019/12/11 18:39:00 by auguyon          ###   ########.fr       */
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

typedef	struct		s_info
{
	struct s_btree 	*adr_start;
	struct s_btree 	*adr_end;
    char            *line;
    char            *f_room;
	char			*s_room;
	unsigned int	ants;
	unsigned int	best_move;
    int             error;
    int    			x;
    int    			y;
    int             rooms;
}					t_info;

typedef struct      s_data
{
    int             *nbr;
    int             **tab;
    int             *x;
    int             *y;
    char            **name;
    int             ants;
    int             nb_rooms;
    int             best_move;
}                   t_data;

typedef struct      s_path
{
    int             endpoint;
    int             depth;
    int             *path;
    int             *depths;
}                   t_path;

typedef struct      s_layer
{
    int             size;
    int             nbr_paths;
    int             sol_depth;
    int             min_depth;
    t_path          *paths;
}                   t_layer;

typedef struct      s_solution
{
    int             size;
    int             nbr_paths;
    int             max_length;
    int             **used_vertices;
    t_path          *paths;
}                   t_solution;

/*
** Initialization
*/
void                initialize(t_layer **l, int size);
void		        init_struct_parse(t_data **dt, t_info **i);
void		        init_struct_algo(t_solution **s, t_path ***p, int size);
/*
** Parsing
*/
t_btree		        *parse_room(t_info *in, short code);
int		            check_error_room(t_btree *groot, t_info *in, int y);
int	                btree_search_name(t_btree *groot, int *j, char *find);
int	                btree_search_pos(t_btree *groot, int *j, int x, int y);
t_btree 	        *add_room(t_btree *groot, t_info *in, short *code);
t_btree			    *btree_rotate(t_btree *t, char *name);
int				    height(t_btree *n);
void		        parse_link(t_info *in, t_btree *groot);
int		            check_error_link(t_btree *groot, t_info *info);
void	            btree_add_link(t_btree *start, t_btree *groot, char *find, char *room);
void	            btree_to_data(t_btree *groot, t_info *info, t_data *dt);
void	            fill_to_neg(int *t, int count);
void		        check_error(t_info *in, t_btree *groot);
void		        free_btree_n_info(t_info *info, t_btree *groot);
void			    print_error(short error);
/*
** Printing
*/
void                prt_g(t_data *dt);
void                prt_path(t_path *path);
void                prt_layer(t_layer *layer);
void                prt_solution(t_solution *solution);
void                prt_possible(t_path **possible);
/*
** Copying
*/
void                copy_path(t_path *source, t_path *dest);
void                copy_solution(t_layer *new_layer, t_path *path);
/*
** Algorithm
*/ 
void                initialize_new_layer(t_layer *new_layer, t_layer *layer, int *ngbs);
int                 mbfs(t_data *dt, t_solution *solution, t_layer *layer, t_path **possible);
void                find_solution(t_path **possible, int n, int *nbr_steps, int *sol);
void                prt_steps(t_path **possible, int nbr_ants, int nbr_steps, int sol);

#endif
