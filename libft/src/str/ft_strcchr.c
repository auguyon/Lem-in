/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 21:10:19 by auguyon           #+#    #+#             */
/*   Updated: 2019/06/06 21:10:23 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

static int	ft_search_letter(char c, char to_find)
{
	if (c == to_find)
		return (1);
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		if (c + 32 == to_find || c - 32 == to_find)
			return (1);
	return (0);
}

char		*ft_strcchr(const char *str, int c)
{
	while (*str)
	{
		if (ft_search_letter(*str, c))
			return ((char*)str);
		str++;
	}
	if (ft_search_letter(*str, c))
		return ((char*)str);
	return (0);
}
