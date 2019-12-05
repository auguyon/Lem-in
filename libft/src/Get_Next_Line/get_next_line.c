/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 20:44:12 by auguyon           #+#    #+#             */
/*   Updated: 2019/11/08 12:32:23 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		ft_cnt_len(char const *str, int i)
{
	int		cnt;

	cnt = i;
	if (str[cnt] == '\0')
		return (1);
	while (str[cnt] != '\0')
		cnt++;
	return (cnt - i);
}

char			**ft_rest_after_first_c(char **tab, char const *s, int i)
{
	int j;
	int k;

	j = 1;
	k = 0;
	if (!(tab[j] = ft_memalloc(ft_cnt_len(s, i))))
		return (NULL);
	if (s[i] != '\0')
	{
		i++;
		while (s[i] != '\0')
			tab[j][k++] = s[i++];
	}
	tab[j][k] = '\0';
	return (tab);
}

char			**ft_strsplit_at_first_c(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**tab;

	i = 0;
	j = 0;
	k = 0;
	if (!s || !(tab = (char**)malloc(sizeof(char*) * 2)))
		return (NULL);
	while (s[i] && s[i] != c)
		i++;
	if (!(tab[j] = ft_memalloc(i + 1)))
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		tab[j][k] = s[i];
		k++;
		i++;
	}
	tab[j][k] = '\0';
	tab = ft_rest_after_first_c(tab, s, i);
	return (tab);
}

t_liste		*gestion_list(t_liste *tmp, int fd, t_liste **list)
{
	t_liste				*new;

	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	if (!(new = (t_liste *)malloc(sizeof(t_liste))))
		return (NULL);
	new->fd = fd;
	new->buftemp = ft_strnew(0);
	new->next = NULL;
	if (tmp)
		tmp->next = new;
	else
		*list = new;
	return (new);
}

int			ft_read(char **str, int fd)
{
	int					i;
	char				*linetmp;
	char				*buf;

	if (!(buf = (char*)malloc(sizeof(char*) * (BUFF_SIZE + 1))))
		return (-1);
	while ((ft_strchr(*str, '\n')) == NULL)
	{
		if ((i = read(fd, buf, BUFF_SIZE)) < 0)
			return (-1);
		buf[i] = '\0';
		linetmp = *str;
		*str = ft_strjoin(*str, buf);
		free(linetmp);
		if (i == 0)
			break ;
	}
	free(buf);
	return (i);
}

void		ft_end_of_file(t_liste *tmp, t_liste **list)
{
	t_liste		*tmp2;

	if (tmp == *list)
	{
		*list = (*list)->next;
		free(tmp->buftemp);
		free(tmp);
	}
	else
	{
		tmp2 = *list;
		while (tmp2->next != tmp)
			tmp2 = tmp2->next;
		tmp2->next = tmp->next;
		free(tmp->buftemp);
		free(tmp);
	}
	return ;
}

int			get_next_line(const int fd, char **line)
{
	static t_liste		*list;
	t_liste				*tmp;
	int					i;
	char				*str;
	char				**tab;

	if (fd == 1 || !line)
		return (-1);
	tmp = list;
	tmp = gestion_list(tmp, fd, &list);
	str = ft_strdup(tmp->buftemp);
	if ((i = ft_read(&str, fd)) < 0)
		return (-1);
	tab = ft_strsplit_at_first_c(str, EOL);
	free(str);
	*line = tab[0];
	if (tmp->buftemp)
		free(tmp->buftemp);
	tmp->buftemp = tab[1];
	free(tab);
	if (i == 0 && *line[0] == '\0')
		ft_end_of_file(tmp, &list);
	return ((i == 0 && *line[0] == '\0') ? 0 : 1);
}