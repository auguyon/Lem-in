/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:40:20 by auguyon           #+#    #+#             */
/*   Updated: 2018/11/14 21:04:40 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utility.h"
#include "str.h"
#include "toa.h"

int		ft_isint(char *nb)
{
	long long		number;
	unsigned int	len;
	unsigned int	i;

	if (nb[0] != '-' && nb[0] != '+' && !ft_isdigit(nb[0]))
		return (-1);
	i = 1;
	len = ft_strlen(nb);
	while (i < len)
		if (!ft_isdigit(nb[i++]))
			return (-1);
	number = ft_atoll(nb);
	if (number < 0 && number >= -2147483648)
		return (1);
	else if (number >= 0 && number <= 2147483647)
		return (2);
	else if (number >= 2147483647 && number <= 4294967295)
		return (3);
	return (-1);
}