/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:53:05 by auguyon           #+#    #+#             */
/*   Updated: 2019/12/09 18:32:14 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_H
# define UTILITY_H

int				ft_atoi(const char *str);
int				ft_atoi_base(const char *str, int base);
unsigned int	ft_utoi(const char *str);
long long		ft_atoll(const char *str);
int				ft_isdigit(char c);
int				ft_max(int a, int b);
int				ft_min(int a, int b);
int				ft_abs(int x);
int				ft_count_c(const char *line, char c);
void			ft_fill_nb(int *t, int nb, int size);
void			ft_malloc_error();

#endif
