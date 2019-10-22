/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 10:09:30 by auguyon           #+#    #+#             */
/*   Updated: 2018/11/30 13:35:02 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include <stdlib.h>

char	*ft_strdup(const char *str)
{
	char	*dest;

	if (!(dest = ft_memalloc(ft_strlen(str) + 1)))
		return (NULL);
	return (ft_strcpy(dest, str));
}
