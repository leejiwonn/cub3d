/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifier_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonlee <jiwonlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 02:07:09 by jiwonlee          #+#    #+#             */
/*   Updated: 2021/06/12 02:08:04 by jiwonlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_bonus.h"

static int		is_png_file(char *path, int len)
{
	int	i;

	i = 0;
	path += len - 4;
	if (path[i] != '.')
		return (0);
	i++;
	if (path[i] != 'p' && path[i] != 'P')
		return (0);
	i++;
	if (path[i] != 'n' && path[i] != 'N')
		return (0);
	i++;
	if (path[i] != 'g' && path[i] != 'G')
		return (0);
	return (1);
}

static char		*set_wall_texture(t_parse *data, char *line, int flag)
{
	int		len;
	char	*path;

	if (!set_wall_texture_path(data->texture + flag, &line))
		return ("set_wall_texture_path malloc failed");
	path = *(data->texture + flag);
	len = ft_strlen(path);
	if (len < 5 || !is_png_file(path, len))
		return ("texture is not PNG(png) file");
	if (*line)
		return ("invalid wall_path");
	return (0);
}

static char		*set_color(t_parse *data, char *line, int flag)
{
	int				count;
	int				color_value;
	unsigned char	*color_ptr;
	int				i;

	count = 0;
	color_ptr = (unsigned char *)((data->color) + flag - 4);
	i = 0;
	while (i < 3)
	{
		color_value = 0;
		count += parse_atoi(&line, &color_value);
		if (color_value > 255)
			return ("invalid color");
		*(color_ptr + i + 1) = (unsigned char)color_value;
		i++;
	}
	if (count != 2 || *line)
		return ("invalid color");
	return (0);
}

int				set_wall_texture_path(char **target, char **line)
{
	int	i;

	if (!(*target = malloc(ft_strlen(*line) + 1)))
		return (0);
	i = 0;
	while (**line && **line != ' ')
	{
		*(*target + i++) = **line;
		(*line)++;
	}
	*(*target + i) = 0;
	return (1);
}

char			*set_identifier(t_parse *data, char *line, int flag)
{
	char	*line_cur;
	char	*error_msg;

	line_cur = line;
	error_msg = 0;
	while (*line_cur == ' ')
		line_cur++;
	while (*line_cur != ' ')
		line_cur++;
	while (*line_cur == ' ')
		line_cur++;
	if (FLAG_NO <= flag && flag <= FLAG_EA)
		error_msg = set_wall_texture(data, line_cur, flag);
	else if (flag == FLAG_F || flag == FLAG_C)
		error_msg = set_color(data, line_cur, flag);
	free(line);
	return (error_msg);
}
