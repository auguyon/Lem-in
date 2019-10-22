/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stoa_base_caps.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 19:05:17 by auguyon           #+#    #+#             */
/*   Updated: 2019/07/24 19:05:18 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toa.h"
#include <stdlib.h>

static char	*min_short(short n, short base)
{
	char	*str;
	short	nb;
	short	i;

	i = 3;
	nb = n;
	while ((nb = (nb / base)) > 0)
		i++;
	if (!(str = (char*)malloc(sizeof(char) * (i))))
		return (NULL);
	str[i--] = '\0';
	str[0] = '-';
	nb = (8 % base);
	str[i] = nb > 9 ? nb + 55 : nb + 48;
	while (i > 1)
	{
		nb = (n % base);
		str[--i] = nb > 9 ? nb + 87 : nb + 48;
		n /= base;
	}
	return (str);
}

char		*ft_stoa_base_caps(short n, int base)
{
	char	*str;
	short	nb;
	short	i;
	short	neg;

	i = 1;
	if (n == -32768)
		return (min_short(3276, base));
	if (!(neg = 0) && n < 0 && ++i)
		neg = 1;
	neg ? n *= -1 : 1;
	nb = n;
	while ((nb = (nb / base)) > 0)
		i++;
	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i] = '\0';
	neg ? str[0] = '-' : 1;
	while (i > neg)
	{
		nb = (n % base);
		str[--i] = nb > 9 ? nb + 55 : nb + 48;
		n /= base;
	}
	return (str);
}
