/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:52:48 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/22 21:55:38 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int     close_window(t_game *game)
{
    mlx_destroy_window(game->mlx, game->win);
    free(game->map);
    exit(0);
    return (0);
}

int     key_press(int key, t_game *game)
{
    if (key == 65307) // ESC
        close_window(game);
    else if (key == 119 || key == 65362) // W or Up
        move_player(game, 0, -1);
    else if (key == 115 || key == 65364) // S or Down
        move_player(game, 0, 1);
    else if (key == 97 || key == 65361) // A or Left
        move_player(game, -1, 0);
    else if (key == 100 || key == 65363) // D or Right
        move_player(game, 1, 0);
    return (0);
}

void    move_player(t_game *game, int dx, int dy)
{
    int new_x = game->player_x + dx;
    int new_y = game->player_y + dy;
    int new_pos = new_y * (game->width + 1) + new_x;
    int old_pos = game->player_y * (game->width + 1) + game->player_x;
    
    if (game->map[new_pos] != '1')
    {
        if (game->map[new_pos] == 'E')
        {
            if (game->collectibles > 0)
            {
                ft_printf("Collect all items first!\n");
                game->player_x = new_x;
                game->player_y = new_y;
            }
            else
            {
                ft_printf("Moves: %d\nYou won, nice one!\n", game->moves);
                close_window(game);
            }
        }
        else
        {
            game->moves++;
            ft_printf("Moves: %d\n", game->moves);
            if (game->map[new_pos] == 'C')
                game->collectibles--;
            if (game->map[old_pos] != 'E')
                game->map[old_pos] = '0';
            if (game->map[new_pos] != 'E')
                game->map[new_pos] = 'P';
            game->player_x = new_x;
            game->player_y = new_y;
        }
        game->last_dx = dx;
        game->last_dy = dy;
        update_player_texture(game, dx, dy);
        render_map(game);
    }
}

void    update_player_texture(t_game *game, int dx, int dy)
{
    int pos_x = game->player_x * TILE_SIZE;
    int pos_y = game->player_y * TILE_SIZE;
    
    if (game->player_x == game->exit_x && game->player_y == game->exit_y && game->collectibles > 0)
        mlx_put_image_to_window(game->mlx, game->win, game->img[8], pos_x, pos_y); // in_top_of_exit.xpm
    else if (dx == 1)
        mlx_put_image_to_window(game->mlx, game->win, game->img[6], pos_x, pos_y); // player_looking_right.xpm
    else if (dx == -1)
        mlx_put_image_to_window(game->mlx, game->win, game->img[5], pos_x, pos_y); // player_looking_left.xpm
    else if (dy == 1)
        mlx_put_image_to_window(game->mlx, game->win, game->img[4], pos_x, pos_y); // player_looking_direct.xpm
    else if (dy == -1)
        mlx_put_image_to_window(game->mlx, game->win, game->img[7], pos_x, pos_y); // player_looking_back.xpm
}
