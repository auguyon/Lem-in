/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 14:42:57 by auguyon           #+#    #+#             */
/*   Updated: 2018/11/23 11:28:17 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

char	*ft_strrchr(const char *str, int c)
{
	const char	*s;

	s = str;
	while (*str)
		str++;
	while (s <= str)
	{
		if (*str == c)
			return ((char*)str);
		str--;
	}
	return (NULL);
}
