/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strccmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 20:59:58 by auguyon           #+#    #+#             */
/*   Updated: 2019/06/06 21:00:02 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strccmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2 && *s1 - 32 != *s2 && *s1 + 32 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++ && s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
