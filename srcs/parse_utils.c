/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:41:31 by seujeon           #+#    #+#             */
/*   Updated: 2021/06/12 01:39:07 by jiwonlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int		parse_atoi(char **line, int *target)
{
	int		i;
	int		check_comma;

	i = 3;
	check_comma = 0;
	while (**line == '0')
		(*line)++;
	while (**line >= '0' && **line <= '9' && i--)
	{
		*target = (*target * 10) + **line - 48;
		(*line)++;
	}
	while (**line == ' ')
		(*line)++;
	if (**line == ',')
	{
		(*line)++;
		check_comma = 1;
	}
	while (**line == ' ')
		(*line)++;
	return (check_comma);
}

void	free_data(t_parse *data)
{
	int		i;

	i = 0;
	if (data->map)
	{
		while (data->map[i])
			free(data->map[i++]);
		free(data->map);
		i = 0;
	}
	if (data->texture)
	{
		while (data->texture[i])
			free(data->texture[i++]);
		free(data->texture);
		i = 0;
	}
}

int		get_flag(char *line)
{
	while (*line == ' ')
		line++;
	if (*line == 'N' && *(line + 1) == 'O' && *(line + 2) == ' ')
		return (FLAG_NO);
	else if (*line == 'S' && *(line + 1) == 'O' && *(line + 2) == ' ')
		return (FLAG_SO);
	else if (*line == 'W' && *(line + 1) == 'E' && *(line + 2) == ' ')
		return (FLAG_WE);
	else if (*line == 'E' && *(line + 1) == 'A' && *(line + 2) == ' ')
		return (FLAG_EA);
	else if (*line == 'F' && *(line + 1) == ' ')
		return (FLAG_F);
	else if (*line == 'C' && *(line + 1) == ' ')
		return (FLAG_C);
	return (FLAG_NOT);
}

int		is_full(char *flags)
{
	int		i;

	i = 0;
	while (i < 6)
	{
		if (flags[i++] == 0)
			return (0);
	}
	return (1);
}

void	ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((unsigned char *)s)[i++] = (unsigned char)c;
}
