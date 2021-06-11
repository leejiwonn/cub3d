/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonlee <jiwonlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 02:06:17 by jiwonlee          #+#    #+#             */
/*   Updated: 2021/06/12 02:06:21 by jiwonlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

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
