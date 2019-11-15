/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 21:56:34 by auguyon           #+#    #+#             */
/*   Updated: 2018/11/16 10:50:59 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	size_t	len;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	if (!(str = ft_memalloc(len + 1)))
		return (NULL);
	while (*s)
		*str++ = f(*s++);
	*str = '\0';
	return (str - len);
}
