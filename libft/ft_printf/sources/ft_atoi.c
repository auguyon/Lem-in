/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flbartol <flbartol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 19:40:58 by ftrujill          #+#    #+#             */
/*   Updated: 2019/01/19 15:45:46 by flbartol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** atoi "stops" working after long long range.
** For positive numbers not in the range it returns 1.
** For negative numbers not in the range it returns 0.
*/

int		ft_atoi(const char *str)
{
	int					sgn;
	size_t				i;
	long long int		number;
	long long int		ovrflw;

	sgn = 1;
	i = 0;
	number = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		sgn = (str[i++] == '-') ? 0 : 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		ovrflw = 10 * number + str[i++] - 48;
		if (ovrflw < number)
			return (-sgn);
		number = ovrflw;
	}
	if (sgn == 0)
		number = -number;
	return ((int)number);
}
