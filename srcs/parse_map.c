/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:41:29 by seujeon           #+#    #+#             */
/*   Updated: 2021/06/12 01:37:35 by jiwonlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	set_padding(char **map, int end, int map_width)
{
	if (!(map[0] = malloc(map_width + 1)))
	{
		free(map);
		return (0);
	}
	map[0][map_width] = 0;
	if (!(map[end - 1] = malloc(map_width + 1)))
	{
		free(map[0]);
		free(map);
		return (0);
	}
	map[end - 1][map_width] = 0;
	ft_memset(map[0], ' ', map_width);
	ft_memset(map[end - 1], ' ', map_width);
	map[end] = 0;
	return (1);
}

static int	resize_col(char ***map_ref, int col_end,
		int padding_size, int map_width)
{
	char	**new_map;
	int		i;

	if (!(new_map = malloc(sizeof(char *) * (col_end + padding_size + 1))))
		return (0);
	i = 0;
	if (padding_size)
		if (!(set_padding(new_map, col_end + padding_size,
						map_width + padding_size)))
			return (0);
	while (*(*map_ref + i))
	{
		*(new_map + i + (padding_size / 2)) = *(*map_ref + i);
		i++;
	}
	while (i < col_end + 1 && !padding_size)
		*(new_map + i++) = 0;
	free(*map_ref);
	*map_ref = new_map;
	return (1);
}

static int	resize_row(char **map_ref, int col_end)
{
	char	*new_row;
	int		i;
	int		j;

	i = 0;
	while (map_ref[i])
	{
		new_row = malloc(col_end + 1);
		if (!new_row)
			return (0);
		new_row[0] = ' ';
		j = -1;
		while (map_ref[i][++j])
			new_row[j + 1] = map_ref[i][j];
		j++;
		while (j < col_end)
			new_row[j++] = ' ';
		new_row[j] = 0;
		free(map_ref[i]);
		map_ref[i] = new_row;
		i++;
	}
	return (1);
}

char		*resize_map(t_parse *data, int check_flags)
{
	if (!check_flags)
		return ("invalid identifier");
	if (!resize_row(data->map, data->map_width + 2))
		return ("resize_row failed");
	if (!resize_col(&data->map, data->col_index, 2, data->map_width))
		return ("resize_col failed");
	return (map_validation(data, data->map_width + 2));
}

char		*set_map(t_parse *data, char *line)
{
	int	i;

	if (data->col_index == data->col_end)
	{
		data->col_end += 10;
		if (!resize_col(&data->map, data->col_end, 0, 0))
		{
			free(line);
			return ("resize_col failed");
		}
	}
	*(data->map + data->col_index++) = line;
	i = 0;
	while (*(line + i))
		i++;
	if (data->map_width < i)
		data->map_width = i;
	return (0);
}
