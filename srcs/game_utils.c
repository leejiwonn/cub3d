#include "main.h"

char *init_game(t_game **game)
{
    if (!(*game = malloc(sizeof(t_game))))
        return ("malloc failed");
    if (!((*game)->mlx = mlx_init()))
        return ("mlx_init failed");
    (*game)->mlx = mlx_init();
    (*game)->window = 0;
    (*game)->image = 0;
    (*game)->adr = 0;
    (*game)->bpp = 0;
    (*game)->leng = 0;
    (*game)->endian = 0;
    (*game)->data = 0;
    (*game)->texture = 0;
    (*game)->player = 0;
    (*game)->data = 0;
    (*game)->dda = 0;
    return (0);
}

void run_game(t_game *game)
{
    mlx_hook(game->window, 2, 0, key_press, game);
    mlx_hook(game->window, 3, 0, key_release, game);
    mlx_hook(game->window, 17, 0, key_exit, game);
    mlx_loop_hook(game->mlx, main_loop, game);
    mlx_loop(game->mlx);
}

void free_game(t_game *game)
{
    if (game->texture)
        free_texture(game->texture, game->mlx);
    if (game->data)
        free_data(game->data);
    if (game->dda)
        free(game->dda);
    if (game->player)
        free(game->player);
    if (game->window)
        mlx_destroy_window(game->mlx, game->window);
    if (game->mlx)
        free(game->mlx);
    free(game);
}