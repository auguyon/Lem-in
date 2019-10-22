/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 14:31:10 by auguyon           #+#    #+#             */
/*   Updated: 2018/11/30 13:28:05 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (c == *str)
			return ((char*)str);
		str++;
	}
	if (*str == c)
		return ((char*)str);
	return (0);
}
