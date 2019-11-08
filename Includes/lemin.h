/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:49:39 by auguyon           #+#    #+#             */
/*   Updated: 2019/11/08 16:41:26 by auguyon          ###   ########.fr       */
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
}					t_info;


#endif
