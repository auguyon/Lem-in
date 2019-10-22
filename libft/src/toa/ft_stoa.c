/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 18:27:00 by auguyon           #+#    #+#             */
/*   Updated: 2019/07/04 18:27:01 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toa.h"
#include <stdlib.h>

char	*ft_stoa(short n)
{
	short	a;
	short	b;
	short	neg;
	char	*str;

	if (n == -32768)
		return (ft_strdup("-32768"));
	if (!(b = 0) && n == 0)
		b++;
	if (!(neg = 0) && n < 0 && ++b)
		neg = 1;
	a = (neg ? -n : n);
	while (n && ++b)
		n = n / 10;
	if (!(str = (char*)malloc(sizeof(char) * b + 1)))
		return (0);
	str[b] = '\0';
	while (b--)
	{
		str[b] = (a % 10) + '0';
		a = a / 10;
	}
	(neg ? str[0] = '-' : 1);
	return (str);
}
