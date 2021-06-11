/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 20:12:37 by seujeon           #+#    #+#             */
/*   Updated: 2021/06/11 21:40:42 by seujeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		error_print(t_game *game, char *error_msg)
{
	if (game)
		free_game(game);
	printf("Error\n");
	printf("Message : %s\n", error_msg);
	exit(1);
}

int				main(int argc, char **argv)
{
	t_game		*game;
	char		*error_msg;

	if (argc != 2)
		error_print(0, "Invalid argument");
	if ((error_msg = set_game(&game, *(argv + 1))))
		error_print(game, error_msg);
	ray_casting(game, game->player, game->data);
	run_game(game);
}