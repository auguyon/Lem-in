/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 20:41:56 by auguyon           #+#    #+#             */
/*   Updated: 2018/11/16 10:52:58 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toa.h"
#include <stdlib.h>

char	*ft_itoa(int n)
{
	unsigned short	i;
	short			neg;
	int				nb;
	char			*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (!(i = 0) && n == 0)
		i++;
	if (!(neg = 0) && n < 0 && ++i)
		neg = 1;
	nb = (neg ? -n : n);
	while (n && ++i)
		n = n / 10;
	if (!(str = (char*)malloc(sizeof(char) * i + 1)))
		return (0);
	str[i] = '\0';
	while (i--)
	{
		str[i] = (nb % 10) + '0';
		nb = nb / 10;
	}
	(neg ? str[0] = '-' : 1);
	return (str);
}
