/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 10:08:22 by auguyon           #+#    #+#             */
/*   Updated: 2019/11/08 17:06:39 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

size_t	ft_strclen(const char *restrict str, const char c)
{
	const char	*ptr;
	size_t		i;

	ptr = str;
	i = 0;
	while (1)
	{
		if (!ptr[0] || ptr[0] == c)
			return (i);
		else if (!ptr[1] || ptr[1] == c)
			return (i + 1);
		else if (!ptr[2] || ptr[2] == c)
			return (i + 2);
		else if (!ptr[3] || ptr[3] == c)
			return (i + 3);
		ptr += 4;
		i += 4;
	}
}
