/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ztoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 17:29:15 by auguyon           #+#    #+#             */
/*   Updated: 2019/06/24 17:29:16 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toa.h"
#include <stdlib.h>

char	*ft_ztoa_base(size_t n, unsigned int base)
{
	unsigned int	i;
	size_t			nb;
	char			*str;

	nb = n;
	i = 1;
	while ((nb = (nb / base)) > 0)
		i++;
	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i] = '\0';
	while (i > 0)
	{
		nb = (n % base);
		str[--i] = nb > 9 ? nb + 87 : nb + 48;
		n /= base;
	}
	return (str);
}
