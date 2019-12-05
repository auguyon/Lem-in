/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 12:01:55 by auguyon           #+#    #+#             */
/*   Updated: 2018/12/10 11:39:06 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_ccword(char *s, char c)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		i;
	int		k;

	if (!(i = 0) && (!s || !c))
		return (0);
	if (!(tab = (char**)malloc(sizeof(*tab) * (ft_ccword((char*)s, c) + 1))))
		return (0);
	while (!(k = 0) && *s)
	{
		while (*s == c && *s)
			s++;
		while (s[k] != c && s[k])
			k++;
		if (!k)
			break ;
		if (!(tab[i] = (char*)malloc(sizeof(*tab) * (k + 1))))
			return (0);
		k = 0;
		while (*s != c && *s)
			tab[i][k++] = *s++;
		tab[i++][k] = '\0';
	}
	tab[i] = 0;
	return (tab);
}
