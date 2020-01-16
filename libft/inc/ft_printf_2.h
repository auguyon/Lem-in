/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_2.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <ftrujill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 13:56:32 by ftrujill          #+#    #+#             */
/*   Updated: 2019/06/22 16:23:51 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_2_H
# define FT_PRINTF_2_H

t_conv			g_conv_tab[] =
{
	{'c', &ft_printarg_c},
	{'s', &ft_printarg_s},
	{'p', &ft_printarg_p},
	{'d', &ft_printarg_d},
	{'i', &ft_printarg_i},
	{'o', &ft_printarg_o},
	{'u', &ft_printarg_u},
	{'x', &ft_printarg_x},
	{'X', &ft_printarg_big_x},
	{'f', &ft_printarg_f},
	{'%', &ft_printarg_pcnt}
};

#endif
