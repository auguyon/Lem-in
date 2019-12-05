/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 15:06:14 by auguyon           #+#    #+#             */
/*   Updated: 2019/01/07 15:30:59 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

char	*ft_strnjoin(char const *s1, char const *s2, size_t size)
{
	char	*dst;

	if (!s1 || !s2)
		return (NULL);
	if (!(dst = ft_memalloc(ft_strlen(s1) + size + 1)))
		return (NULL);
	ft_strncat((ft_strcpy(dst, s1)), s2, size);
	return (dst);
}
