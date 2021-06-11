/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonlee <jiwonlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 02:19:45 by jiwonlee          #+#    #+#             */
/*   Updated: 2021/06/12 02:20:04 by jiwonlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

void	set_point(t_dda *dda, t_parse *data)
{
	int	height;
	int	screen_height;

	height = (int)(data->resol[Y] / dda->walldist);
	screen_height = data->resol[Y];
	*dda->point = (-height + screen_height) / 2;
	*(dda->point + 1) = (height + screen_height) / 2;
}

char	*get_texture_start(t_texture **texture, t_dda *dda, t_game *game)
{
	int	pixel_offset;

	dda->cur = texture[FLAG_SO];
	if (!dda->side && dda->ray[X] < 0)
		dda->cur = texture[FLAG_EA];
	else if (!dda->side && dda->ray[X] > 0)
		dda->cur = texture[FLAG_WE];
	else if (dda->side == 1 && dda->ray[Y] < 0)
		dda->cur = texture[FLAG_NO];
	if (game->data->map[dda->pos_to_int[Y]][dda->pos_to_int[X]] == 'D')
	{
		dda->cur = &(game->door);
	}
	dda->cur->ratio_y = (double)(dda->cur->len[HEIGHT] - 1);
	dda->cur->ratio_y /= (double)(dda->point[DOWN] - dda->point[UP] + 1);
	pixel_offset = (int)(dda->wall_x * (dda->cur->len[WIDTH] - 1))
		* dda->cur->bpp;
	return (dda->cur->addr + pixel_offset);
}

void	set_dda_value(t_dda *dda, t_player *player, int width, int x_cur)
{
	int		i;
	double	x_camera;

	i = 0;
	x_camera = 2 * x_cur / (double)width - 1;
	while (i < 2)
	{
		dda->pos_to_int[i] = (int)(player->pos[i]);
		dda->point[i] = 0;
		dda->ray[i] = player->dir[i] + player->plane[i] * x_camera;
		dda->deltadist[i] = fabs(1 / dda->ray[i]);
		dda->step[i] = -1;
		dda->sidedist[i] = player->pos[i] - dda->pos_to_int[i];
		if (dda->ray[i] >= 0)
		{
			dda->step[i] = 1;
			dda->sidedist[i] = (-1 * dda->sidedist[i]) + 1.0;
		}
		dda->sidedist[i] *= dda->deltadist[i];
		i++;
	}
	dda->side = 0;
}

void	hit_wall(t_dda *dda, char **map, double *pos)
{
	int	s;

	s = Y;
	while (map[dda->pos_to_int[Y]][dda->pos_to_int[X]] == '0')
	{
		s = Y;
		if (dda->sidedist[X] < dda->sidedist[Y])
			s = X;
		dda->sidedist[s] += dda->deltadist[s];
		dda->pos_to_int[s] += dda->step[s];
	}
	dda->walldist = dda->pos_to_int[s] - pos[s] + (1 - dda->step[s]) / 2;
	dda->walldist /= dda->ray[s];
	dda->wall_x = pos[1 - s] + dda->walldist * dda->ray[1 - s];
	dda->wall_x -= floor(dda->wall_x);
	dda->side = s;
}
