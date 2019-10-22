/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 19:10:23 by auguyon           #+#    #+#             */
/*   Updated: 2018/11/16 10:57:33 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char *s;

	d = (unsigned char*)dest;
	s = (const unsigned char*)src;
	if (d < s)
	{
		while (n--)
			*d++ = *s++;
	}
	else
		while (n--)
			d[n] = s[n];
	return (dest);
}
