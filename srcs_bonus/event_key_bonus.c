#include "main_bonus.h"

void		set_minimap_pixels(t_game *game, t_minimap *minimap, t_player *player)
{
	int			i;
	int			j;

	i = 0;
	while (i < minimap->y)
	{
		j = 0;
		minimap->line = minimap->img;
		while (j < minimap->x)
		{
			if (game->data->map[i / SCALE][j / SCALE] == ' ')
				*minimap->line = 0x000000ff;
			else if (game->data->map[i / SCALE][j / SCALE] == '1')
				*minimap->line = 0x00000000;
			else if (game->data->map[i / SCALE][j / SCALE] == '0')
				*minimap->line = 0x0000ff00;
			if (i / SCALE == (int)player->pos[Y] && j / SCALE == (int)player->pos[X])
				*minimap->line = 0x00ff0000;
			minimap->line++;
			j++;
		}
		minimap->img += minimap->texture.size_line;
		i++;
	}
}

int			draw_minimap(t_game *game, t_player *player)
{
	t_minimap	minimap;
	t_texture	texture;

	minimap.y = game->data->col_index * SCALE;
	minimap.x = game->data->map_width * SCALE;
	texture.image = mlx_new_image(game->mlx, minimap.x, minimap.y);
	texture.addr = mlx_get_data_addr(texture.image, &(texture.bpp), &(texture.size_line), &(texture.endian));
	texture.size_line /= 4;
	minimap.img = (unsigned int *)texture.addr;
	minimap.texture = texture;
	set_minimap_pixels(game, &minimap, player);
	mlx_put_image_to_window(game->mlx, game->window, texture.image, 0, 0);
	mlx_destroy_image(game->mlx, texture.image);
	return (1);
}

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
		is_active = move_ad(game->player, game->data->map, 0.3);
	else if (game->player->key[D] == 1)
		is_active = move_ad(game->player, game->data->map, -0.3);
	if (game->player->key[S] == 1)
		is_active = move_ws(game->player, game->data->map, -0.3);
	else if (game->player->key[W] == 1)
		is_active = move_ws(game->player, game->data->map, 0.3);
	if (game->player->key[LEFT] == 1)
		is_active = rotate_player(game->player, (PI / HALF_CYCLE) * 1.5);
	else if (game->player->key[RIGHT] == 1)
		is_active = rotate_player(game->player, (PI / HALF_CYCLE) * -1.5);
	if (is_active)
		ray_casting(game, game->player, game->data);
	return (1);
}
