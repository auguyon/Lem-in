/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 14:15:27 by auguyon           #+#    #+#             */
/*   Updated: 2019/11/08 12:31:52 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 1
# define EOL '\n'

# include "libft.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>

typedef struct			s_liste
{
	int					fd;
	char				*buftemp;
	struct s_liste		*next;
}						t_liste;

int					get_next_line(const int fd, char **line);

#endif
