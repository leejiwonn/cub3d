#include "main_bonus.h"

int			proc_mouse_event(int x, int y, t_game *game)
{
	(void)y;
	if (game && game->player)
		game->player->mouse_x = x;
	mlx_mouse_hide();
	game->player->key[MOUSE_MOVE] = 1;
	return (1);
}

int			rotate_mouse(t_game *game)
{
	int	center_x;
	int center_y;
	int	move_offset;

	if (game->player->key[MOUSE_MOVE] == 0)
		return (0);
	game->player->key[MOUSE_MOVE] = 0;
	center_x = game->data->resol[X] / 2;
	center_y = game->data->resol[Y] / 2;
	move_offset = (game->player->mouse_x - center_x) / 5;
	if (move_offset < 0)
	{
		rotate_player(game->player, (PI / HALF_CYCLE) * 5);
		mlx_mouse_move(game->window, center_x, center_y);
	}
	else if (move_offset > 0)
	{
		rotate_player(game->player, (PI / HALF_CYCLE) * -5);
		mlx_mouse_move(game->window, center_x, center_y);
	}
	else
		return (0);
	return (1);
}