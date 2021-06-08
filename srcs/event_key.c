#include "main.h"

int key_press(int keycode, t_game *game)
{
    if (keycode == 53)
    {
        free_game(game);
        exit(0);
    }
    if (0 <= keycode && keycode <= 2)
        game->player->key[keycode] = 1;
    if (keycode == 13)
        game->player->key[3] = 1;
    if (keycode == 123 || keycode == 124)
        game->player->key[keycode - 119] = 1;
    return (0);
}

int key_release(int keycode, t_game *game)
{
    if (keycode >= 0 && keycode <= 2)
        game->player->key[keycode] = 0;
    if (keycode == 13)
        game->player->key[3] = 0;
    if (keycode == 123 || keycode == 124)
        game->player->key[keycode - 119] = 0;
    return (0);
}

int key_exit(t_game *game)
{
    free_game(game);
    exit(0);
    return (0);
}

int main_loop(t_game *game)
{
    char flag;

    flag = 0;
    if (game->player->key[0] == 1)
        flag = move_ad(game->player, game->data->map, 0.3);
    else if (game->player->key[2] == 1)
        flag = move_ad(game->player, game->data->map, -0.3);
    if (game->player->key[1] == 1)
        flag = move_ws(game->player, game->data->map, -0.3);
    else if (game->player->key[3] == 1)
        flag = move_ws(game->player, game->data->map, 0.3);
    if (game->player->key[4] == 1)
        flag = eyesight_lr(game->player, PIT * 1.5);
    else if (game->player->key[5] == 1)
        flag = eyesight_lr(game->player, PIT * -1.5);
    if (flag)
        ray_casting(game, game->player, game->data);
    return (1);
}
