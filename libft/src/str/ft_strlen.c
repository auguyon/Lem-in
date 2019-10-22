/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 10:08:22 by auguyon           #+#    #+#             */
/*   Updated: 2018/11/23 12:13:28 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

size_t	ft_strlen(const char *restrict str)
{
	const char	*ptr;
	size_t		i;

	ptr = str;
	i = 0;
	while (1)
	{
		if (!ptr[0])
			return (i);
		else if (!ptr[1])
			return (i + 1);
		else if (!ptr[2])
			return (i + 2);
		else if (!ptr[3])
			return (i + 3);
		ptr += 4;
		i += 4;
	}
}
