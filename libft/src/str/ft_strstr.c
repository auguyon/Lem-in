/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:54:32 by auguyon           #+#    #+#             */
/*   Updated: 2018/11/17 13:16:07 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

char	*ft_strstr(const char *str, const char *srh)
{
	if (!(ft_strlen(srh)))
		return ((char*)str);
	while (*str)
	{
		if ((ft_strncmp(str++, srh, ft_strlen(srh)) == 0))
			return ((char*)str - 1);
	}
	return (NULL);
}
