/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 03:44:25 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/20 07:38:00 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void count_collectibles(t_game *game)
{
    int x;
    int y;

    game->collectibles = 0;
    y = 0;
    while (y < game->height)
    {
        x = 0;
        while (x < game->width)
        {
            if (game->map[y][x] == 'C')
                game->collectibles++;
            x++;
        }
        y++;
    }
}

void move_player(t_game *game, int dx, int dy)
{
    int new_x = game->player_x + dx;
    int new_y = game->player_y + dy;

    if (new_x >= 0 && new_x < game->width && new_y >= 0 && new_y < game->height &&
        game->map[new_y][new_x] != '1')
    {
        if (game->map[new_y][new_x] == 'C')
        {
            game->collectibles--;
            game->map[new_y][new_x] = '0'; // Clear the collectible
        }
        if (game->map[new_y][new_x] == 'E')
        {
            if (game->collectibles == 0) // Only allow exiting if all collectibles are gathered
            {
                game->won = 1; // Set the won flag to indicate the player won
                close_window(game);
            }
            else
            {
                game->tried_to_exit = 1; // Set flag to indicate player tried to exit
                ft_printf("\033[1;35mYou need to collect all items first! 🐺\033[0m\n");
                return; // Don't move the player onto the exit
            }
        }
        else
        {
            game->map[game->player_y][game->player_x] = '0';
            game->player_x = new_x;
            game->player_y = new_y;
            game->map[new_y][new_x] = 'P';
            game->moves++;
            ft_printf("Moves: %d\n", game->moves);
            render_map(game);
        }
    }
}

int key_hook(int keycode, t_game *game)
{
    if (keycode == 119) // W
    {
        game->current_player_tex = game->tex.player_looking_back;
        move_player(game, 0, -1);
    }
    else if (keycode == 97) // A
    {
        game->current_player_tex = game->tex.player_looking_left;
        move_player(game, -1, 0);
    }
    else if (keycode == 115) // S
    {
        game->current_player_tex = game->tex.player_looking_direct;
        move_player(game, 0, 1);
    }
    else if (keycode == 100) // D
    {
        game->current_player_tex = game->tex.player_looking_right;
        move_player(game, 1, 0);
    }
    else if (keycode == 65307) // ESC
    {
        // Print the exit message in purple and exit immediately without delay
        if (!game->won)
        {
            ft_printf("\033[1;35mWhy did you leave, bro? 🐺\033[0m\n");
        }
        cleanup_and_exit(game);
    }
    return (0);
}