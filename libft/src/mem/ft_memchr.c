/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 20:08:55 by auguyon           #+#    #+#             */
/*   Updated: 2018/11/17 14:24:01 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char *sr;

	sr = (const unsigned char*)s;
	while (n--)
	{
		if (*sr == (unsigned char)c)
			return ((void*)sr);
		sr++;
	}
	return (NULL);
}
