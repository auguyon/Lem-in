/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:52:50 by auguyon           #+#    #+#             */
/*   Updated: 2019/11/12 19:30:27 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

# include <string.h>
# include "mem.h"

char	*ft_strcat(char *dest, const char *src);
char	*ft_strcchr(const char *str, int c);
int		ft_strccmp(const char *s1, const char *s2);
char	*ft_strchr(const char *str, int c);
void	ft_strclr(char *s);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dest, const char *src);
size_t	ft_strcspn(const char *s, const char *c);
void	ft_strdel(char **as);
char	*ft_strdup(const char *str);
int		ft_strequ(char const *s1, char const *s2);
void	ft_striter(char *s, void (*f)(char*));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_free(char *s1, char *s2, short code_free);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *restrict str);
char	*ft_strmap(char const *s, char (*f)(char));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_strmultidel(char **str);
char	*ft_strncat(char *dest, const char *src, size_t n);
int		ft_strnccmp(const char *s1, const char *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_strndup(const char *str, size_t size);
int		ft_strnequ(char const *s1, char const *s2, size_t n);
char	*ft_strnew(size_t size);
char	*ft_strnjoin(char const *s1, char const *s2, size_t size);
char	*ft_strnstr(const char *str, const char *srh, size_t n);
char	*ft_strrchr(const char *str, int c);
char	**ft_strsplit(char const *s, char c);
size_t	ft_strspn(const char *s, const char *c);
char	*ft_strstr(const char *str, const char *srh);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s);
size_t	ft_strclen(const char *restrict str, char c);
char	*ft_strcdup(const char *str, const char c);
void	ft_strrev(char *str);
char	*ft_strlower(char *str);
int		ft_isint(char *nb);

#endif
