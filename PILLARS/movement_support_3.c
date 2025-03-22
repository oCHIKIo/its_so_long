/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_support_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 01:16:09 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/22 02:17:23 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void handle_movement_keys(int keycode, t_game *game)
{
    if (keycode == 119) // W
    {
        game->keys.w_pressed = 1;
        game->current_player_tex = game->tex.player_looking_back;
    }
    else if (keycode == 97) // A
    {
        game->keys.a_pressed = 1;
        game->current_player_tex = game->tex.player_looking_left;
    }
    else if (keycode == 115) // S
    {
        game->keys.s_pressed = 1;
        game->current_player_tex = game->tex.player_looking_direct;
    }
    else if (keycode == 100) // D
    {
        game->keys.d_pressed = 1;
        game->current_player_tex = game->tex.player_looking_right;
    }
}

int key_press(int keycode, t_game *game)
{
    handle_movement_keys(keycode, game);
    if (keycode == 65307) // ESC
    {
        if (!game->won)
            ft_printf("\033[1;38;5;51mWhy did you leave, noobie? 🐺\033[0m\n");
        cleanup_and_exit(game);
    }
    return (0);
}
