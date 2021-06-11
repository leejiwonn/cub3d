/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_validation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:41:27 by seujeon           #+#    #+#             */
/*   Updated: 2021/06/12 01:38:27 by jiwonlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	check_around(char **map, int col, int row)
{
	int		i;
	int		j;

	i = -2;
	while (++i < 2)
	{
		j = -2;
		while (++j < 2)
			if (map[col + i][row + j] == ' ')
				return (0);
	}
	return (1);
}

static char	*check_player(t_parse *data, int col, int row)
{
	char	cur;

	cur = data->map[col][row];
	if (cur == ' ' || cur == '1')
		return (0);
	else if (cur != '0')
	{
		if (data->direction)
			return ("player reduplication error");
		data->direction = cur;
		data->location[X] = row;
		data->location[Y] = col;
		data->map[col][row] = '0';
	}
	if (!check_around(data->map, col, row))
		return ("invalid map");
	return (0);
}

static char	find_chr(const char *str, char target)
{
	while (*str)
	{
		if (*str == target)
			return (target);
		str++;
	}
	return (0);
}

char		*map_validation(t_parse *data, int map_width)
{
	int		col;
	int		row;
	char	*error_msg;

	col = 0;
	while (++col < data->col_index + 1)
	{
		row = 0;
		while (++row < map_width - 1)
		{
			if (!find_chr(" 01WENS", data->map[col][row]))
				return ("invalid map");
			if ((error_msg = check_player(data, col, row)))
				return (error_msg);
		}
	}
	if (!data->direction)
		return ("player not exist");
	return (0);
}
