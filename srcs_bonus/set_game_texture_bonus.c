/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_game_texture_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonlee <jiwonlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 02:20:54 by jiwonlee          #+#    #+#             */
/*   Updated: 2021/06/12 02:20:59 by jiwonlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

void			free_texture(t_texture **texture_info, void *mlx)
{
	int			i;

	i = 0;
	while (texture_info[i])
	{
		if (texture_info[i]->image)
			mlx_destroy_image(mlx, texture_info[i]->image);
		free(texture_info[i]);
		i++;
	}
	free(texture_info);
}

int				set_texture_data(void *mlx, char *path, t_texture *texture_info)
{
	int fd;

	if ((fd = open(path, O_RDONLY)) <= 0)
		return (0);
	close(fd);
	if (!(texture_info->image = mlx_png_file_to_image(
		mlx, path, &texture_info->len[WIDTH], &texture_info->len[HEIGHT])))
		return (0);
	if (!(texture_info->addr = mlx_get_data_addr(
		texture_info->image, &(texture_info->bpp),
		&(texture_info->size_line), &(texture_info->endian))))
		return (0);
	texture_info->bpp /= 8;
	return (1);
}

t_texture		**set_texture(void *mlx, char **list)
{
	int			i;
	t_texture	**texture_info;

	if (!(texture_info = (t_texture **)malloc(sizeof(t_texture *) * 5)))
		return (0);
	i = 5;
	while (--i >= 0)
		texture_info[i] = 0;
	while (++i < 4)
	{
		if (!(texture_info[i] = malloc(sizeof(t_texture))))
			return (0);
		ft_memset(texture_info[i], 0, sizeof(t_texture));
		if (!(set_texture_data(mlx, list[i], texture_info[i])))
		{
			free_texture(texture_info, mlx);
			return (0);
		}
	}
	return (texture_info);
}
