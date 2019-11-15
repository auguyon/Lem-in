/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 20:26:54 by auguyon           #+#    #+#             */
/*   Updated: 2018/11/30 13:09:01 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	char	*d;

	if (!s)
		return (NULL);
	if (!(dst = (char*)malloc(sizeof(*dst) * len + 1)))
		return (NULL);
	d = dst;
	while (len--)
		*dst++ = s[start++];
	*dst = '\0';
	return (d);
}
