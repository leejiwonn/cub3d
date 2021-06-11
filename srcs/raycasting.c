/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:41:38 by seujeon           #+#    #+#             */
/*   Updated: 2021/06/12 01:40:27 by jiwonlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static unsigned int	get_texture_color(char *texture_start, int y,
		t_texture *texture)
{
	char	*result;

	result = texture_start + (int)(y * texture->ratio_y) * texture->size_line;
	return (*(unsigned int *)result);
}

static void			draw_line_y(t_game *game, char *img_data,
		char *texture_start)
{
	int		y;
	int		index;
	t_color	*color;
	int		*point;

	y = 0;
	point = game->dda->point;
	color = game->data->color;
	while (y < game->data->resol[Y])
	{
		if (point[UP] <= y && y <= point[DOWN])
			*(unsigned int *)img_data = get_texture_color(texture_start,
					y - point[UP], game->dda->cur);
		else
		{
			index = C;
			if (y > point[DOWN])
				index = F;
			*(unsigned int *)img_data = (color[index].a << 24) +
			(color[index].r << 16) + (color[index].g << 8) + color[index].b;
		}
		img_data += game->size_line;
		y++;
	}
}

int					ray_casting(t_game *game, t_player *player, t_parse *data)
{
	int		x_cur;
	char	*img_data;

	if (!(game->image = mlx_new_image(game->mlx,
					data->resol[X], data->resol[Y])))
		return (free_game_exit(game, "creating raycasting image failed"));
	game->addr = mlx_get_data_addr(game->image, &(game->bpp),
			&(game->size_line), &(game->endian));
	game->bpp /= 8;
	x_cur = -1;
	img_data = game->addr;
	while (++x_cur < data->resol[X])
	{
		set_dda_value(game->dda, player, data->resol[X], x_cur);
		hit_wall(game->dda, data->map, player->pos);
		set_point(game->dda, data);
		draw_line_y(game, img_data,
				get_texture_start(game->texture, game->dda));
		img_data += game->bpp;
	}
	mlx_put_image_to_window(game->mlx, game->window, game->image, 0, 0);
	mlx_destroy_image(game->mlx, game->image);
	game->image = 0;
	return (1);
}
