/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <ftrujill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 18:02:18 by ftrujill          #+#    #+#             */
/*   Updated: 2019/06/01 16:19:20 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	ssize_t	l1;
	ssize_t	l2;
	ssize_t	i;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	i = 0;
	if (ft_memnlap_fwd(s1, s2, l1 + ft_min(l2, n)))
		return (s1);
	while (i < ft_min(l2, n))
	{
		s1[l1 + i] = s2[i];
		i++;
	}
	s1[l1 + i] = 0;
	return (s1);
}
