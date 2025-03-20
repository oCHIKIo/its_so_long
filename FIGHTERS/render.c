/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 03:42:49 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/20 08:07:59 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void load_textures(t_game *game)
{
    int width;
    int height;

    game->tex.wall = mlx_xpm_file_to_image(game->mlx, "TEXTURES/wall.xpm", &width, &height);
    game->tex.floor = mlx_xpm_file_to_image(game->mlx, "TEXTURES/floor.xpm", &width, &height);
    game->tex.player_looking_right = mlx_xpm_file_to_image(game->mlx, "TEXTURES/player_looking_right.xpm", &width, &height);
    game->tex.player_looking_left = mlx_xpm_file_to_image(game->mlx, "TEXTURES/player_looking_left.xpm", &width, &height);
    game->tex.player_looking_back = mlx_xpm_file_to_image(game->mlx, "TEXTURES/player_looking_back.xpm", &width, &height);
    game->tex.player_looking_direct = mlx_xpm_file_to_image(game->mlx, "TEXTURES/player_looking_direct.xpm", &width, &height);
    game->tex.collectible = mlx_xpm_file_to_image(game->mlx, "TEXTURES/collectible.xpm", &width, &height);
    game->tex.exit = mlx_xpm_file_to_image(game->mlx, "TEXTURES/exit.xpm", &width, &height);
    game->tex.exit_open = mlx_xpm_file_to_image(game->mlx, "TEXTURES/exit_open.xpm", &width, &height);
    game->tex.in_top_of_exit = mlx_xpm_file_to_image(game->mlx, "TEXTURES/in_top_of_exit.xpm", &width, &height);
}

void render_map(t_game *game)
{
    t_nbr nbr;

    nbr.y = 0;
    while (nbr.y < game->height)
    {
        nbr.x = 0;
        while (nbr.x < game->width)
        {
            if (game->map[nbr.y][nbr.x] == '1')
                mlx_put_image_to_window(game->mlx, game->win, game->tex.wall, nbr.x * TILE_SIZE, nbr.y * TILE_SIZE);
            else
                mlx_put_image_to_window(game->mlx, game->win, game->tex.floor, nbr.x * TILE_SIZE, nbr.y * TILE_SIZE);
            if (game->map[nbr.y][nbr.x] == 'C')
                mlx_put_image_to_window(game->mlx, game->win, game->tex.collectible, nbr.x * TILE_SIZE, nbr.y * TILE_SIZE);
            if (game->map[nbr.y][nbr.x] == 'E')
            {
                if (game->collectibles == 0)
                    mlx_put_image_to_window(game->mlx, game->win, game->tex.exit_open, nbr.x * TILE_SIZE, nbr.y * TILE_SIZE);
                else if (game->player_x == game->exit_x && game->player_y == game->exit_y)
                    mlx_put_image_to_window(game->mlx, game->win, game->tex.in_top_of_exit, nbr.x * TILE_SIZE, nbr.y * TILE_SIZE);
                else
                    mlx_put_image_to_window(game->mlx, game->win, game->tex.exit, nbr.x * TILE_SIZE, nbr.y * TILE_SIZE);
            }
            if (nbr.x == game->player_x && nbr.y == game->player_y &&
                !(game->player_x == game->exit_x && game->player_y == game->exit_y && game->collectibles > 0))
            {
                mlx_put_image_to_window(game->mlx, game->win, game->current_player_tex, nbr.x * TILE_SIZE, nbr.y * TILE_SIZE);
            }
            nbr.x++;
        }
        nbr.y++;
    }
}
