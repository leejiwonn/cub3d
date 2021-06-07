#include "main.h"

static void my_pixel_put(t_game *game, char *dst, char *ref)
{
    int y;
    int flag;
    int *color;
    int *point;

    y = 0;
    point = game->dda->point;
    color = game->data->color;
    while (y < game->data->resol[1])
    {
        if (point[0] <= y && y <= point[1])
            *(unsigned int *)dst = t_color(ref, y - point[0], game->dda->cur);
        else
        {
            flag = 1;
            if (y > point[1])
                flag = 0;
            *(unsigned int *)dst = (unsigned int)color[flag];
        }
        dst += game->leng;
        y++;
    }
}

int ray_casting(t_game *game, t_player *player, t_parse *data)
{
    int x;
    char *dst;

    game->image = mlx_new_image(game->mlx, data->resol[0], data->resol[1]);
    game->adr = mlx_get_data_addr(game->image, &(game->bpp), &(game->leng), &(game->endian));
    game->bpp /= 8;
    x = -1;
    dst = game->adr;
    while (++x < data->resol[0])
    {
        set_dda_value(game->dda, player, data->resol[0], x);
        hit_wall(game->dda, data->worldmap, player->pos);
        draw_point(game->dda, data);
        my_pixel_put(game, dst, select_texture(game->texture, game->dda));
        dst += game->bpp;
    }
    mlx_put_image_to_window(game->mlx, game->window, game->image, 0, 0);
    mlx_destroy_image(game->mlx, game->image);
    return (1);
}