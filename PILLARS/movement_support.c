/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_support.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:08:47 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/23 05:58:22 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	init_move(t_game *game, t_move *move, int dx, int dy)
{
	move->new_x = game->player_x + dx;
	move->new_y = game->player_y + dy;
	move->new_pos = move->new_y * (game->width + 1) + move->new_x;
	move->old_pos = game->player_y * (game->width + 1) + game->player_x;
}

int check_exit(t_game *game, t_move *move)
{
    if (game->collectibles > 0)
    {
        game->early_exit_attempts++;
        if (game->early_exit_attempts == 1)
            ft_printf("\033[1;36mCollect all items first!\033[0m\n");
        else
            ft_printf("\033[1;36mCome on, noobie, keep going!\033[0m\n");
        game->player_x = move->new_x;
        game->player_y = move->new_y;
        return (0);
    }
    ft_printf("\033[1;36mMoves: %d\nYou won, nice one!\033[0m\n", game->moves);
    close_window(game);
    return (1);
}

void update_move(t_game *game, t_move *move)
{
    game->moves++;
    ft_printf("\033[1;36mMoves: %d\033[0m\n", game->moves);
    if (game->map[move->new_pos] == 'C')
        game->collectibles--;
    if (game->map[move->old_pos] != 'E')
        game->map[move->old_pos] = '0'; // Clear old position
    if (game->map[move->new_pos] != 'E')
        game->map[move->new_pos] = 'P'; // Set new position
    game->player_x = move->new_x;
    game->player_y = move->new_y;
}
