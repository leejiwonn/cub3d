/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_key_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonlee <jiwonlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 02:03:07 by jiwonlee          #+#    #+#             */
/*   Updated: 2021/06/12 02:03:17 by jiwonlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

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
	if (keycode == KEY_P && game->player->key[MOUSE_TOGGLE])
	{
		mlx_mouse_show();
		game->player->key[MOUSE_TOGGLE] = 0;
	}
	else if (keycode == KEY_P && !game->player->key[MOUSE_TOGGLE])
	{
		mlx_mouse_hide();
		game->player->key[MOUSE_TOGGLE] = 1;
	}
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
	if (keycode == KEY_SPACE)
		game->player->key[SPACE] = 1;
	return (0);
}

int			key_exit(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}

int			activate_door(t_game *game, t_player *player)
{
	int		x;
	int		y;

	y = player->pos[Y] + player->dir[Y];
	x = player->pos[X] + player->dir[X];
	game->player->key[SPACE] = 0;
	if (y >= game->data->col_index - 1 || y <= 0
		|| x >= game->data->map_width - 1 || x <= 0)
		return (0);
	if ((int)player->pos[Y] == y && (int)player->pos[X] == x)
		return (0);
	if (game->data->map[y][x] == 'D')
		game->data->map[y][x] = '0';
	else if (game->data->map[y][x] == '0' && is_door_pos(x, y, game))
		game->data->map[y][x] = 'D';
	return (1);
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
	if (game->player->key[MOUSE_TOGGLE] && game->player->key[MOUSE_MOVE] == 1)
		is_active = rotate_mouse(game);
	if (game->player->key[SPACE] == 1)
		is_active = activate_door(game, game->player);
	if (is_active)
		ray_casting(game, game->player, game->data);
	return (1);
}
