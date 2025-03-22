/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_support_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 01:13:27 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/22 02:17:20 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int handle_exit(t_game *game, int new_x, int new_y)
{
    if (new_x == game->exit_x && new_y == game->exit_y)
    {
        if (game->collectibles == 0)
        {
            game->player_x = new_x;
            game->player_y = new_y;
            game->moves++;
            ft_printf("\033[1;38;5;201mMoves: %d\033[0m\n", game->moves);
            render_map(game);
            game->won = 1;
            close_window(game);
            return (1);
        }
        else
        {
            game->tried_to_exit = 1;
            ft_printf("\033[1;38;5;51mYou need to collect all items first! 🐺\033[0m\n");
        }
    }
    return (0);
}

void update_and_render(t_game *game, int new_x, int new_y)
{
    game->player_x = new_x;
    game->player_y = new_y;
    game->moves++;
    ft_printf("\033[1;38;5;201mMoves: %d\033[0m\n", game->moves);
    render_map(game);
}

long get_current_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
