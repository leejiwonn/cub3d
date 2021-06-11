/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:42:17 by seujeon           #+#    #+#             */
/*   Updated: 2021/06/12 02:45:27 by jiwonlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# define BUFFER_SIZE 10

typedef struct		s_fdlist
{
	char			*save;
	int				fd;
	struct s_fdlist	*next;
}					t_fdlist;

int					get_next_line(int fd, char **line);
char				*ft_strchr(const char *s);
char				*ft_strdup(const char *s, size_t len);
char				*ft_strjoin(char *s1, char *s2);
size_t				ft_strlen(const char *s);
t_fdlist			*ft_newfd(int fd);

#endif
