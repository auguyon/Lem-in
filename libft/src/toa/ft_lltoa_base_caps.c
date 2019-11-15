/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_base_caps.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 15:47:29 by auguyon           #+#    #+#             */
/*   Updated: 2019/07/01 15:47:30 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toa.h"
#include <stdlib.h>

static char	*min_long_long(long long n, int base)
{
	char		*str;
	long long	nb;
	int			i;

	i = 3;
	nb = n;
	while ((nb = (nb / base)) > 0)
		i++;
	if (!(str = (char*)malloc(sizeof(char) * (i))))
		return (NULL);
	str[i--] = '\0';
	str[0] = '-';
	nb = (7 % base);
	str[i] = nb > 9 ? nb + 55 : nb + 48;
	while (i > 1)
	{
		nb = (n % base);
		str[--i] = nb > 9 ? nb + 87 : nb + 48;
		n /= base;
	}
	return (str);
}

char		*ft_lltoa_base_caps(long long n, int base)
{
	char		*str;
	int			i;
	long long	nb;
	int			neg;

	i = 1;
	if (n == -922337203685477580)
		return (min_long_long(922337203685477580, base));
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
