/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 18:44:12 by auguyon           #+#    #+#             */
/*   Updated: 2018/11/13 21:27:33 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	ft_bzero(void *s, size_t n)
{
	long	*str;
	char	*str_2;

	str = (long*)s;
	while ((n >= sizeof(long)))
	{
		*str++ = 0;
		n -= sizeof(long);
	}
	str_2 = (char*)str;
	while (n > 0)
	{
		*str_2++ = 0;
		n--;
	}
}
