/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uctoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 20:39:28 by auguyon           #+#    #+#             */
/*   Updated: 2019/07/04 20:39:33 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toa.h"
#include <stdlib.h>

char	*ft_uctoa(unsigned char n)
{
	unsigned char	a;
	unsigned short	b;
	char			*str;

	a = n;
	b = 0;
	if (n == 0)
		b = 1;
	while (n && ++b)
		n /= 10;
	if (!(str = (char*)malloc(sizeof(char) * b + 1)))
		return (0);
	str[b] = '\0';
	while (b--)
	{
		str[b] = (a % 10) + '0';
		a = a / 10;
	}
	return (str);
}
