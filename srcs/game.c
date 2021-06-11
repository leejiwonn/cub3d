/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:41:13 by seujeon           #+#    #+#             */
/*   Updated: 2021/06/12 01:25:17 by jiwonlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char		*init_game(t_game **game)
{
	if (!((*game)->mlx = mlx_init()))
		return ("mlx_init failed");
	(*game)->window = 0;
	(*game)->image = 0;
	(*game)->addr = 0;
	(*game)->bpp = 0;
	(*game)->size_line = 0;
	(*game)->endian = 0;
	(*game)->data = 0;
	(*game)->texture = 0;
	(*game)->player = 0;
	(*game)->dda = 0;
	return (0);
}

void		run_game(t_game *game)
{
	mlx_hook(game->window, 2, 0, key_press, game);
	mlx_hook(game->window, 3, 0, key_release, game);
	mlx_hook(game->window, 17, 0, key_exit, game);
	mlx_loop_hook(game->mlx, main_loop, game);
	mlx_loop(game->mlx);
}

int			free_game(t_game *game)
{
	if (game->texture)
		free_texture(game->texture, game->mlx);
	if (game->data)
		free_data(game->data);
	if (game->image)
		mlx_destroy_image(game->mlx, game->image);
	if (game->dda)
		free(game->dda);
	if (game->player)
		free(game->player);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	return (1);
}

int			free_game_exit(t_game *game, char *message)
{
	if (game->texture)
		free_texture(game->texture, game->mlx);
	if (game->data)
		free_data(game->data);
	if (game->image)
		mlx_destroy_image(game->mlx, game->image);
	if (game->dda)
		free(game->dda);
	if (game->player)
		free(game->player);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	printf("Error\nMessage : %s", message);
	exit(1);
	return (1);
}

char		*set_game(t_game *game, char *map_path)
{
	char	*error_msg;

	if ((error_msg = init_game(&game)))
		return (error_msg);
	if ((error_msg = parse(&(game)->data, map_path)))
		return (error_msg);
	return (set_game_data(game));
}
