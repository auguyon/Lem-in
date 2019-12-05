/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:07:34 by auguyon           #+#    #+#             */
/*   Updated: 2018/11/16 17:47:38 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

char	*ft_strnstr(const char *str, const char *srh, size_t n)
{
	int		nb;

	nb = (int)n;
	if (ft_strlen(srh) == 0)
		return ((char*)str);
	nb = nb - ft_strlen(srh);
	while (*str && nb >= 0)
	{
		if ((ft_strncmp(str, srh, ft_strlen(srh)) == 0))
			return ((char*)str);
		nb--;
		str++;
	}
	return (NULL);
}
