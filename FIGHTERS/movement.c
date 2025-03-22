/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 00:13:46 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/22 01:18:29 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void move_player(t_game *game, int dx, int dy)
{
    int new_x;
    int new_y;

    calculate_new_position(game, dx, dy, &new_x, &new_y);
    if (is_valid_move(game, new_x, new_y))
    {
        handle_collectible(game, new_x, new_y);
        if (handle_exit(game, new_x, new_y))
            return;
        if (game->player_x == game->exit_x && game->player_y == game->exit_y)
            game->tried_to_exit = 0;
        update_and_render(game, new_x, new_y);
    }
}
