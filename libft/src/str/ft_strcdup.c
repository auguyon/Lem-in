/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 10:09:30 by auguyon           #+#    #+#             */
/*   Updated: 2019/11/12 20:29:28 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include <stdlib.h>

char	*ft_strcdup(const char *str, const char c)
{
	char	*dst;
	char	*cpy;
	size_t	size;

	size = ft_strclen(str, c);
	if (ft_strlen(str) < size)
		size = ft_strlen(str);
	if (!(dst = ft_memalloc(size + 1)))
		return (NULL);
	cpy = dst;
	ft_strncpy(dst, str, size);
	return (cpy);
}
