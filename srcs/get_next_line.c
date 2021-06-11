/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:41:18 by seujeon           #+#    #+#             */
/*   Updated: 2021/06/12 01:32:34 by jiwonlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		find_fd(int fd, t_fdlist **fdl, t_fdlist **cur)
{
	t_fdlist	*tmp;

	tmp = *fdl;
	if (!*fdl)
	{
		*fdl = ft_newfd(fd);
		*cur = *fdl;
	}
	else
	{
		while (tmp->fd != fd && tmp->next)
			tmp = tmp->next;
		if (tmp->fd == fd)
			*cur = tmp;
		else
		{
			tmp = ft_newfd(fd);
			tmp->next = *fdl;
			*fdl = tmp;
			*cur = tmp;
		}
	}
	if (!*cur)
		return (0);
	return (1);
}

static void		remove_curfd(int fd, t_fdlist **fdl)
{
	t_fdlist	*pre;
	t_fdlist	*tmp;

	pre = 0;
	tmp = *fdl;
	while (tmp->fd != fd)
	{
		pre = tmp;
		tmp = tmp->next;
	}
	if (pre)
	{
		pre->next = tmp->next;
		if (tmp->save)
			free(tmp->save);
		free(tmp);
	}
	else
	{
		tmp = (*fdl)->next;
		if ((*fdl)->save)
			free((*fdl)->save);
		free(*fdl);
		*fdl = tmp;
	}
}

static int		set_result(char **line, t_fdlist *cur, int size,
					t_fdlist **fdl)
{
	char	*div;
	char	*tmp;

	if (size == -1 || !(div = ft_strchr(cur->save)))
		return (-1);
	tmp = cur->save;
	if (!(*line = ft_strdup(cur->save, div - cur->save)))
		return (-1);
	if (!*(cur->save) || !*div)
	{
		cur->save = 0;
		free(tmp);
		remove_curfd(cur->fd, fdl);
		return (0);
	}
	if (!(cur->save = ft_strdup(div + 1, ft_strlen(div + 1))))
		return (-1);
	free(tmp);
	return (1);
}

int				get_next_line(int fd, char **line)
{
	static t_fdlist	*fdlist;
	t_fdlist		*cur;
	char			*buff;
	char			*tmp;
	int				size;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line || !(find_fd(fd, &fdlist, &cur))
		|| !(buff = (char *)malloc(BUFFER_SIZE + 1)))
		return (-1);
	if (!cur->save)
		cur->save = ft_strdup("", 0);
	while ((size = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[size] = 0;
		tmp = ft_strdup(buff, size);
		cur->save = ft_strjoin(cur->save, tmp);
		if (!(tmp = ft_strchr(cur->save)))
			return (-1);
		if (*tmp)
			break ;
	}
	free(buff);
	if (size == -1)
		remove_curfd(cur->fd, &fdlist);
	return (set_result(line, cur, size, &fdlist));
}
