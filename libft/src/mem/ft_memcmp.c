/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 21:16:19 by auguyon           #+#    #+#             */
/*   Updated: 2018/11/16 17:00:05 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned const char	*sa;
	unsigned const char	*sb;

	sa = (unsigned const char*)s1;
	sb = (unsigned const char*)s2;
	if (!n)
		return (0);
	while ((*sa == *sb) && --n)
	{
		sa++;
		sb++;
	}
	return (*sa - *sb);
}
