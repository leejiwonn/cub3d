/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:41:11 by seujeon           #+#    #+#             */
/*   Updated: 2021/06/11 19:48:34 by seujeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int			key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		free_game(game);
		exit(0);
	}
	if (KEY_A <= keycode && keycode <= KEY_D)
		game->player->key[keycode] = 1;
	if (keycode == KEY_W)
		game->player->key[3] = 1;
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		game->player->key[keycode - 119] = 1;
	return (0);
}

int			key_release(int keycode, t_game *game)
{
	if (keycode >= KEY_A && keycode <= KEY_D)
		game->player->key[keycode] = 0;
	if (keycode == KEY_W)
		game->player->key[3] = 0;
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		game->player->key[keycode - 119] = 0;
	return (0);
}

int			key_exit(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}

int			main_loop(t_game *game)
{
	char	is_active;

	is_active = 0;
	if (game->player->key[A] == 1)
		is_active = move_ad(game->player, game->data->map, MOVE_SCALE);
	else if (game->player->key[D] == 1)
		is_active = move_ad(game->player, game->data->map, -MOVE_SCALE);
	if (game->player->key[S] == 1)
		is_active = move_ws(game->player, game->data->map, -MOVE_SCALE);
	else if (game->player->key[W] == 1)
		is_active = move_ws(game->player, game->data->map, MOVE_SCALE);
	if (game->player->key[LEFT] == 1)
		is_active = rotate_player(game->player, (PI / HALF_CYCLE) * 1.5);
	else if (game->player->key[RIGHT] == 1)
		is_active = rotate_player(game->player, (PI / HALF_CYCLE) * -1.5);
	if (is_active)
		ray_casting(game, game->player, game->data);
	return (1);
}
