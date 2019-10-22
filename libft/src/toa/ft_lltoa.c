/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 15:47:34 by auguyon           #+#    #+#             */
/*   Updated: 2019/07/01 15:47:38 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toa.h"
#include <stdlib.h>

char	*ft_lltoa(long long n)
{
	long long		nb;
	unsigned int	b;
	short			neg;
	char			*str;

	if (n == -9223372036854775807)
		return (ft_strdup("-9223372036854775807"));
	if (!(b = 0) && n == 0)
		b++;
	if (!(neg = 0) && n < 0 && ++b)
		neg = 1;
	nb = (neg ? -n : n);
	while (n && ++b)
		n = n / 10;
	if (!(str = (char*)malloc(sizeof(char) * b + 1)))
		return (0);
	str[b] = '\0';
	while (b--)
	{
		str[b] = (nb % 10) + '0';
		nb /= 10;
	}
	neg ? str[0] = '-' : 1;
	return (str);
}
