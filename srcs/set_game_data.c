#include "main.h"

char *set_game_data(t_game *game)
{
    int *display;

    display = game->data->resol;
    mlx_get_screen_size(game->mlx, &display[0], &display[1]);
    if (!(game->window = mlx_new_window(game->mlx, display[0], display[1], "cub3d")))
        return ("mlx_new_window failed");
    if (!(game->texture = set_texture(game->mlx, game->data->texture)))
        return ("set_texture failed");
    if (!(game->player = set_player(game->data->location, game->data->direction)))
        return ("set_player failed");
    if (!(game->dda = malloc(sizeof(t_dda))))
        return ("dda malloc failed");
    return (0);
}