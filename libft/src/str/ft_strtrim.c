/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 21:29:18 by auguyon           #+#    #+#             */
/*   Updated: 2018/11/16 11:08:31 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_mod_isspace(char const *s)
{
	return ((*s == ' ' || *s == '\n' || *s == '\t') && *s);
}

char		*ft_strtrim(char const *s)
{
	char	*dst;
	int		len;
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (ft_mod_isspace(s))
		s++;
	while (s[i + 1] != '\0')
		i++;
	while (ft_mod_isspace(&s[i]))
		i--;
	len = ++i;
	if (!(dst = (char*)malloc(sizeof(*dst) * len + 1)))
		return (0);
	while (len--)
		*dst++ = *s++;
	*dst = '\0';
	return (dst - i);
}
