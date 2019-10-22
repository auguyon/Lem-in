/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:49:39 by auguyon           #+#    #+#             */
/*   Updated: 2019/10/15 15:49:41 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "../libft/inc/libft.h"

#include <stdio.h>

typedef struct 		s_map
{
	unsigned int	*tubs;
	char			*room;
	int				x;
	int				y;
}					t_map;

typedef	struct		s_info
{
	unsigned int	ants;
	unsigned int	i;
	char			*n_start;
	char			*n_end;
	short			start;
	short			end;
}					t_info;

#endif
