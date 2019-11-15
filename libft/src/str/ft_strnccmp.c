/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnccmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 21:02:52 by auguyon           #+#    #+#             */
/*   Updated: 2019/06/06 21:02:54 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

int		ft_strnccmp(const char *s1, const char *s2, size_t n)
{
	if (!n)
		return (0);
	while (*s1 && *s2 && --n)
	{
		if (*s1 != *s2 && *s1 - 32 != *s2 && *s1 + 32 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++ && s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
