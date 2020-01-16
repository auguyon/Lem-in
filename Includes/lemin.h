/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <ftrujill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:49:39 by auguyon           #+#    #+#             */
/*   Updated: 2020/01/15 18:59:36 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "../libft/inc/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct		s_map
{
	struct s_map	*next;
	char			*line;
}					t_map;

typedef struct		s_link
{
	struct s_link	*next;
	struct s_btree	*adr;
	char			*name;
}					t_link;

typedef struct		s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	struct s_link	*link;
	char			*name;
	int				height;
	int				x;
	int				y;
	int				nb;
}					t_btree;

typedef	struct		s_info
{
	struct s_map	*map;
	struct s_map	*map_start;
	struct s_btree	*adr_start;
	struct s_btree	*adr_end;
	char			*line;
	char			*f_room;
	char			*s_room;
	int				ants;
	unsigned int	best_move;
	short			error;
	int				x;
	int				y;
	int				rooms;
}					t_info;

typedef struct		s_data
{
	int				*nbr;
	int				**tab;
	int				*x;
	int				*y;
	char			**name;
	int				ants;
	int				nb_rooms;
	int				nbr_paths;
	int				nbr_steps;
	int				best_move;
	short			error;
}					t_data;

typedef struct		s_path
{
	int				endpoint;
	int				depth;
	int				*path;
	int				*depths;
}					t_path;

typedef struct		s_layer
{
	int				size;
	int				nbr_paths;
	int				sol_depth;
	int				min_depth;
	int				*upd;
	int				*vtd;
	t_path			*paths;
}					t_layer;

typedef struct		s_solution
{
	int				size;
	int				nbr_paths;
	int				max_length;
	int				nbr_ants;
	int				nbr_steps;
	int				**used_vertices;
	t_path			*paths;
}					t_solution;

/*
** Initialization
*/
void				init_struct_parse(t_data **dt, t_info **i);
/*
** Parsing
*/
t_btree				*parse_room(int fd, t_info *in, short code);
int					check_error_room(t_btree *groot, t_info *in, int j, int i);
int					btree_search_name(t_btree *groot, int *j, char *find);
int					btree_search_pos(t_btree *groot, int *j, int x, int y);
t_btree				*add_room(t_btree *groot, t_info *in, short *code);
t_btree				*btree_rotate(t_btree *t, char *name);
int					height(t_btree *n);
void				parse_link(int fd, t_info *in, t_btree *groot);
int					check_error_link(t_btree *groot, t_info *info);
void				btree_add_link(t_btree *start, t_btree *groot, char *find
										, char *room);
void				btree_to_data(t_btree *groot, t_info *info,
									t_data *dt, int nb);
void				fill_to_neg(int *t, int count);
void				check_error(t_info *in, t_btree *groot);
void				free_btree_n_info(t_info *info, t_btree *groot);
void				print_error(short error);
/*
** Printing
*/
void				print_map(t_map *map);
void				prt_g(int **g, int size);
void				prt_path(t_path *path);
void				prt_layer(t_layer *layer);
void				prt_solution(t_solution *solution);
void				prt_possible(t_path **possible);
void				prt_check_possible(t_path **possible, t_data *dt);
int					*ant_first_app(t_data *dt, t_path **possible);
int					*path_numbers(t_data *dt, t_path **possible);
void				prt_steps(t_data *dt, t_path **pos, int *path_nbrs
								, int *ant_first);
/*
** Copying
*/
void				copy_path(t_path *source, t_path *dest);
void				deep_copy_path(t_path *source, t_path **dest, int size);
void				copy_solution(t_layer *new_layer, t_path *path);
void				*ft_realloc(void *ptr, size_t size);
/*
** Algorithm
*/
void				solver(t_data *dt, t_info *info);
void				initialize(t_layer **layer, int size);
void				initialize_new_layer(t_layer *new_layer, t_layer *layer
											, int *ngbs);
int					mbfs(t_data *dt, t_solution *solution, t_path **possible);
void				min_depth(t_layer *layer);
void				update(t_layer *new_layer, int *visited, int *updated);
void				next_layer(int **g, int *nbr, t_layer **layer
								, t_solution *solution);
void				update(t_layer *new_layer, int *visited, int *updated);
void				find_solution(t_data *dt, t_path **possible);
void				merge_paths(t_solution *solution, int pos, int i, int p);
void				update_solution(t_path *path, t_solution *solution
									, t_path **possible);
/*
** Free
*/
void				free_path(t_path *path);
void				free_dt(t_data *dt);
void				free_stored_path(t_path *path);
void				free_layer(t_layer **layer);
void				free_new_layer(t_layer **layer, t_layer *new_layer);
void				free_solution(t_solution *solution);
void				free_possible(t_path **possible);
void				free_all(t_data *dt, t_solution *solution
								, t_path **possible);

#endif
