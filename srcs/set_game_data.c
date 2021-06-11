/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_game_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:41:41 by seujeon           #+#    #+#             */
/*   Updated: 2021/06/12 01:41:43 by jiwonlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*set_game_data(t_game *game)
{
	int	*screen;

	screen = game->data->resol;
	screen[X] = RESOL_X;
	screen[Y] = RESOL_Y;
	if (!(game->window = mlx_new_window(game->mlx, screen[X], screen[Y],
					"cub3d")))
		return ("mlx_new_window failed");
	if (!(game->texture = set_texture(game->mlx, game->data->texture)))
		return ("set_texture failed");
	if (!(game->player = set_player(game->data->location,
					game->data->direction)))
		return ("set_player failed");
	if (!(game->dda = malloc(sizeof(t_dda))))
		return ("dda malloc failed");
	return (0);
}
