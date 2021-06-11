#include "main_bonus.h"

int			rotate_mouse(int x, int y, t_game *game)
{
	int	center_x;
	int	center_y;

	y = 0;
	center_x = game->data->resol[X] / 2;
	center_y = game->data->resol[Y] / 2;
	mlx_mouse_hide();
	game->player->key[MOUSE_MOVE] = 1;
	if (x < center_x)
		rotate_player(game->player, (PI / HALF_CYCLE) * 1.5);
	else if (x > center_x)
		rotate_player(game->player, (PI / HALF_CYCLE) * -1.5);
	else
		game->player->key[MOUSE_MOVE] = 0;
	mlx_mouse_move(game->window, center_x, center_y);
	return (game->player->key[MOUSE_MOVE]);
}

char			move_ws(t_player *player, char **worldmap, double scale)
{
	double	*pos;
	double	*dir;

	pos = player->pos;
	dir = player->dir;
	if (worldmap[(int)(pos[Y] + dir[Y] * scale)][(int)pos[X]] != '1')
		pos[Y] += dir[Y] * scale;
	if (worldmap[(int)(pos[Y])][(int)(pos[X] + dir[X] * scale)] != '1')
		pos[X] += dir[X] * scale;
	return (1);
}

char			move_ad(t_player *player, char **worldmap, double scale)
{
	double	tmp_x;
	double	tmp_y;
	double	seta;
	double	*pos;
	double	*dir;

	pos = player->pos;
	dir = player->dir;
	seta = (PI / HALF_CYCLE) * 90;
	tmp_y = dir[Y] * cos(seta) - dir[X] * sin(seta);
	tmp_x = dir[Y] * sin(seta) + dir[X] * cos(seta);
	if (worldmap[(int)(pos[Y] + tmp_y * scale)][(int)pos[X]] != '1')
		pos[Y] += tmp_y * scale;
	if (worldmap[(int)pos[Y]][(int)(pos[X] + tmp_x * scale)] != '1')
		pos[X] += tmp_x * scale;
	return (1);
}

char			rotate_player(t_player *player, double seta)
{
	double	tmp;
	double	*plane;
	double	*dir;

	dir = player->dir;
	plane = player->plane;
	tmp = dir[Y];
	dir[Y] = dir[Y] * cos(seta) - dir[X] * sin(seta);
	dir[X] = tmp * sin(seta) + dir[X] * cos(seta);
	tmp = plane[Y];
	plane[Y] = plane[Y] * cos(seta) - plane[X] * sin(seta);
	plane[X] = tmp * sin(seta) + plane[X] * cos(seta);
	return (1);
}

t_player		*set_player(int *location, char dir)
{
	t_player	*player;
	double		seta;

	if (!(player = malloc(sizeof(t_player))))
		return (0);
	player->pos[X] = (double)(location[X]);
	player->pos[Y] = (double)(location[Y]);
	player->dir[X] = 0;
	player->dir[Y] = -1;
	player->plane[X] = 0.66;
	player->plane[Y] = 0;
	seta = 0;
	if (dir == 'W')
		seta = 90;
	else if (dir == 'S')
		seta = 180;
	else if (dir == 'E')
		seta = -90;
	rotate_player(player, seta * (PI / HALF_CYCLE));
	return (player);
}