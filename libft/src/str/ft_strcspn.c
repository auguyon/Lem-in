/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:36:59 by auguyon           #+#    #+#             */
/*   Updated: 2018/11/23 15:04:54 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

size_t	ft_strcspn(const char *s, const char *c)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (c[j])
		{
			if (c[j] == s[i])
				return (i);
			j++;
		}
		i++;
	}
	if (i)
		return (i);
	return (0);
}
