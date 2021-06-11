/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonlee <jiwonlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 02:06:02 by jiwonlee          #+#    #+#             */
/*   Updated: 2021/06/12 02:06:07 by jiwonlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t			ft_strlen(const char *s)
{
	size_t		count;

	count = 0;
	while (*s++)
		count++;
	return (count);
}

char			*ft_strchr(const char *s)
{
	if (!s)
		return (0);
	while (*s && *s != '\n')
		s++;
	return ((char *)s);
}

char			*ft_strdup(const char *s, size_t len)
{
	char		*result;
	size_t		count;

	if (!s)
		return (0);
	if (!(result = (char *)malloc(len + 1)))
		return (0);
	result[len] = 0;
	count = 0;
	while (count < len)
		*(result + count++) = *s++;
	return (result);
}

char			*ft_strjoin(char *s1, char *s2)
{
	size_t		size;
	size_t		count;
	char		*result;
	char		*tmp;

	if (!s1 || !s2)
		return (0);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(result = (char *)malloc(size)))
		return (0);
	result[size - 1] = 0;
	tmp = result;
	count = 0;
	while (*(s1 + count))
		*tmp++ = *(s1 + count++);
	count = 0;
	while (*(s2 + count))
		*tmp++ = *(s2 + count++);
	free(s1);
	free(s2);
	return (result);
}

t_fdlist		*ft_newfd(int fd)
{
	t_fdlist	*new;

	if (!(new = malloc(sizeof(t_fdlist))))
		return (0);
	new->save = 0;
	new->fd = fd;
	new->next = 0;
	return (new);
}
