#include "main.h"

char eyesight_lr(t_player *player, double seta)
{
    double tmp;
    double *plane;
    double *dir;

    dir = player->dir;
    plane = player->plane;
    tmp = dir[0];
    dir[0] = dir[0] * cos(seta) - dir[1] * sin(seta);
    dir[1] = tmp * sin(seta) + dir[1] * cos(seta);
    tmp = plane[0];
    plane[0] = plane[0] * cos(seta) - plane[1] * sin(seta);
    plane[1] = tmp * sin(seta) + plane[1] * cos(seta);
    return (1);
}

char move_ws(t_player *player, char **worldmap, double flag)
{
    double *pos;
    double *dir;

    pos = player->pos;
    dir = player->dir;
    if (worldmap[(int)(pos[0] + dir[0] * flag)][(int)pos[1]] != '1')
        pos[0] += dir[0] * flag;
    if (worldmap[(int)(pos[0])][(int)(pos[1] + dir[1] * flag)] != '1')
        pos[1] += dir[1] * flag;
    return (1);
}

char move_ad(t_player *player, char **worldmap, double flag)
{
    double tmp_x;
    double tmp_y;
    double seta;
    double *pos;
    double *dir;

    pos = player->pos;
    dir = player->dir;
    seta = PIT * 90;
    tmp_y = dir[0] * cos(seta) - dir[1] * sin(seta);
    tmp_x = dir[0] * sin(seta) + dir[1] * cos(seta);
    if (worldmap[(int)(pos[0] + tmp_y * flag)][(int)pos[1]] != '1')
        pos[0] += tmp_y * flag;
    if (worldmap[(int)pos[0]][(int)(pos[1] + tmp_x * flag)] != '1')
        pos[1] += tmp_x * flag;
    return (1);
}

t_player *set_player(int *location, char dir)
{
    t_player *player;
    double seta;

    player = malloc(sizeof(t_player));
    if (!player)
        return (0);
    player->pos[0] = (double)*(location + 1) + 0.5;
    player->pos[1] = (double)*location + 0.5;
    player->dir[0] = -1;
    player->dir[1] = 0;
    player->plane[0] = 0;
    player->plane[1] = 0.66;
    player->fov = fabs(atan(player->plane[1]) * 180 / 3.14);
    seta = 0;
    if (dir == 'W')
        seta = 90;
    else if (dir == 'S')
        seta = 180;
    else if (dir == 'E')
        seta = -90;
    eyesight_lr(player, seta * PIT);
    return (player);
}