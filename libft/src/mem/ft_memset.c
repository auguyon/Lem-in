/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 18:29:13 by auguyon           #+#    #+#             */
/*   Updated: 2018/11/17 15:13:41 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*st;

	st = (unsigned char*)s;
	while (n--)
		*st++ = (char)c;
	return ((unsigned char*)s);
}
