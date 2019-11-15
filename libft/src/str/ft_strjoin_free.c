/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 20:36:43 by auguyon           #+#    #+#             */
/*   Updated: 2018/12/10 11:39:30 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2, short code_free)
{
	char	*new;

	if (!(new = ft_strjoin(s1, s2)))
		return (NULL);
	if (code_free == 1 || code_free == 3)
		ft_strdel(&s1);
	if (code_free == 2 || code_free == 3)
		ft_strdel(&s2);
	return (new);
}
