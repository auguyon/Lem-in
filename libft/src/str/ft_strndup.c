/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 15:13:55 by auguyon           #+#    #+#             */
/*   Updated: 2018/11/16 15:37:03 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include <stdlib.h>

char	*ft_strndup(const char *str, size_t size)
{
	char	*dst;
	char	*cpy;

	if (ft_strlen(str) < size)
		size = (size_t)ft_strlen(str);
	if (!(dst = ft_memalloc(size + 1)))
		return (NULL);
	cpy = dst;
	ft_strncpy(dst, str, size);
	return (cpy);
}
