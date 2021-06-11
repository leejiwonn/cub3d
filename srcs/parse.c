/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:41:33 by seujeon           #+#    #+#             */
/*   Updated: 2021/06/12 04:20:13 by seujeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parse.h"

static char		init_parse(t_parse **data)
{
	if (!(*data = malloc(sizeof(t_parse))))
		return (0);
	if (!((*data)->texture = malloc(sizeof(char *) * 5)))
		return (0);
	if (!((*data)->map = malloc(sizeof(char *) * 21)))
		return (0);
	ft_memset((*data)->texture, 0, sizeof(char *) * 5);
	ft_memset((*data)->map, 0, sizeof(char *) * 21);
	ft_memset((*data)->resol, 0, sizeof(int) * 6);
	ft_memset((*data)->color, 0, sizeof(t_color) * 2);
	(*data)->direction = 0;
	(*data)->col_end = 20;
	return (1);
}

static char		*set_parse(t_parse *data, char *line, char *flags)
{
	int		flag;
	int		check_full;

	flag = get_flag(line);
	check_full = is_full(flags);
	if ((!check_full && !*line) || (check_full && !*line && !*data->map))
	{
		free(line);
		return (0);
	}
	if (!check_full && flag == FLAG_NOT)
		return ("invalid identifier");
	if (!check_full)
	{
		if (flags[flag] == 1)
			return ("reduplication identifier");
		flags[flag] = 1;
		return (set_identifier(data, line, flag));
	}
	return (set_map(data, line));
}

char			*parse(t_parse **data, char *map_path)
{
	int		fd;
	int		result;
	char	*line;
	char	*error_msg;
	char	flags[6];

	ft_memset(flags, 0, sizeof(char) * 6);
	if (!init_parse(data))
		return ("init_parse failed");
	if ((fd = open(map_path, O_RDONLY)) == -1)
		return ("invalid map path");
	while (1)
	{
		if ((result = get_next_line(fd, &line)) == -1)
			return ("get_next_line failed");
		if (!result && !*line)
			break ;
		if ((error_msg = set_parse(*data, line, flags)))
			return (error_msg);
	}
	free(line);
	return (resize_map(*data, is_full(flags)));
}
