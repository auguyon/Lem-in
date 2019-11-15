/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldtoa_concat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 15:46:54 by auguyon           #+#    #+#             */
/*   Updated: 2019/07/24 15:46:55 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_dtoa_concat(char *s, long l, int sign)
{
	char	*whole;
	char	*tmp;

	whole = NULL;
	if (sign)
	{
		if (!(whole = ft_lltoa_base(l, 10)))
			return (NULL);
		tmp = whole;
		if (!(whole = ft_strjoin("-", whole)))
		{
			ft_strdel(&tmp);
			return (NULL);
		}
	}
	if (!(s = ft_strjoin_free((whole) ? whole : ft_lltoa_base(l, 10), s, 3)))
		return (NULL);
	return (s);
}

char	*ft_ldtoa_concat(char *s, long long l, int sign)
{
	char	*whole;
	char	*tmp;

	whole = NULL;
	if (sign)
	{
		if (!(whole = ft_lltoa_base(l, 10)))
			return (NULL);
		tmp = whole;
		if (!(whole = ft_strjoin("-", whole)))
		{
			ft_strdel(&tmp);
			return (NULL);
		}
	}
	if (!(s = ft_strjoin_free((whole) ? whole : ft_lltoa_base(l, 10), s, 3)))
		return (NULL);
	return (s);
}
