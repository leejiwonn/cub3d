/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonlee <jiwonlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 02:19:32 by jiwonlee          #+#    #+#             */
/*   Updated: 2021/06/12 02:19:37 by jiwonlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

static void			set_minimap_pixels(t_game *game,
						t_minimap *minimap, t_player *player)
{
	int			i;
	int			j;

	i = -1;
	while (++i < minimap->y)
	{
		j = -1;
		minimap->line = minimap->cur_img_ptr;
		while (++j < minimap->x)
		{
			if (game->data->map[i / SCALE][j / SCALE] == ' ')
				*minimap->line = MINIMAP_COLOR_SPACE;
			else if (game->data->map[i / SCALE][j / SCALE] == '1')
				*minimap->line = MINIMAP_COLOR_WALL;
			else if (is_door_pos(j / SCALE, i / SCALE, game))
				*minimap->line = MINIMAP_COLOR_DOOR;
			else if (game->data->map[i / SCALE][j / SCALE] == '0')
				*minimap->line = MINIMAP_COLOR_ROAD;
			if (i / SCALE == (int)player->pos[Y]
					&& j / SCALE == (int)player->pos[X])
				*minimap->line = MINIMAP_COLOR_PLAYER;
			minimap->line++;
		}
		minimap->cur_img_ptr += minimap->texture.size_line;
	}
}

static int			draw_minimap(t_game *game, t_player *player)
{
	t_minimap	*minimap;
	t_texture	texture;

	minimap = &(game->minimap);
	minimap->y = (game->data->col_index + 1) * SCALE + SCALE;
	minimap->x = (game->data->map_width + 1) * SCALE + SCALE;
	if (!(minimap->img = mlx_new_image(game->mlx, minimap->x, minimap->y)))
	{
		printf("Error\nMessage : drawing minimap fail");
		free_game(game);
		exit(1);
	}
	texture.image = minimap->img;
	texture.addr = mlx_get_data_addr(texture.image, &(texture.bpp),
			&(texture.size_line), &(texture.endian));
	texture.size_line /= 4;
	minimap->cur_img_ptr = (unsigned int *)texture.addr;
	minimap->texture = texture;
	set_minimap_pixels(game, minimap, player);
	mlx_put_image_to_window(game->mlx, game->window, texture.image, 0, 0);
	mlx_destroy_image(game->mlx, game->minimap.img);
	game->minimap.img = 0;
	return (1);
}

static unsigned int	get_texture_color(char *texture_start,
										int y, t_texture *texture)
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
	game->addr = mlx_get_data_addr(game->image,
					&(game->bpp), &(game->size_line), &(game->endian));
	game->bpp /= 8;
	x_cur = -1;
	img_data = game->addr;
	while (++x_cur < data->resol[X])
	{
		set_dda_value(game->dda, player, data->resol[X], x_cur);
		hit_wall(game->dda, data->map, player->pos);
		set_point(game->dda, data);
		draw_line_y(game, img_data,
				get_texture_start(game->texture, game->dda, game));
		img_data += game->bpp;
	}
	mlx_put_image_to_window(game->mlx, game->window, game->image, 0, 0);
	draw_minimap(game, game->player);
	mlx_destroy_image(game->mlx, game->image);
	game->image = 0;
	return (1);
}
