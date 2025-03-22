/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_support_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 03:00:58 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/22 03:02:56 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	handle_player_movement(t_game *game, long current_time)
{
	if (game->keys.w_pressed)
	{
		move_player(game, 0, -1);
		game->last_move_time = current_time;
	}
	else if (game->keys.a_pressed)
	{
		move_player(game, -1, 0);
		game->last_move_time = current_time;
	}
	else if (game->keys.s_pressed)
	{
		move_player(game, 0, 1);
		game->last_move_time = current_time;
	}
	else if (game->keys.d_pressed)
	{
		move_player(game, 1, 0);
		game->last_move_time = current_time;
	}
	return (0);
}

int	update_game(t_game *game)
{
	long	current_time;

	current_time = get_current_time();
	if (current_time - game->last_move_time < 150)
		return (0);
	return (handle_player_movement(game, current_time));
}
