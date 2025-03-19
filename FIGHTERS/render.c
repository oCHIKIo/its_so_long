/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 03:42:49 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/19 18:12:53 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void load_textures(t_game *game)
{
    int width = TILE_SIZE;
    int height = TILE_SIZE;

    game->tex.wall = mlx_xpm_file_to_image(game->mlx, "TEXTURES/wall.xpm", &width, &height);
    if (!game->tex.wall)
        ft_printf("Error: Failed to load wall.xpm\n");
    game->tex.floor = mlx_xpm_file_to_image(game->mlx, "TEXTURES/floor.xpm", &width, &height);
    if (!game->tex.floor)
        ft_printf("Error: Failed to load floor.xpm\n");
    game->tex.player_right = mlx_xpm_file_to_image(game->mlx, "TEXTURES/player_looking_right.xpm", &width, &height);
    if (!game->tex.player_right)
        ft_printf("Error: Failed to load player_looking_right.xpm\n");
    game->tex.player_left = mlx_xpm_file_to_image(game->mlx, "TEXTURES/player_looking_left.xpm", &width, &height);
    if (!game->tex.player_left)
        ft_printf("Error: Failed to load player_looking_left.xpm\n");
    game->tex.player_back = mlx_xpm_file_to_image(game->mlx, "TEXTURES/player_looking_back.xpm", &width, &height);
    if (!game->tex.player_back)
        ft_printf("Error: Failed to load player_looking_back.xpm\n");
    game->tex.collectible = mlx_xpm_file_to_image(game->mlx, "TEXTURES/collectible.xpm", &width, &height);
    if (!game->tex.collectible)
        ft_printf("Error: Failed to load collectible.xpm\n");
    game->tex.exit = mlx_xpm_file_to_image(game->mlx, "TEXTURES/exit.xpm", &width, &height);
    if (!game->tex.exit)
        ft_printf("Error: Failed to load exit.xpm\n");
    game->tex.exit_open = mlx_xpm_file_to_image(game->mlx, "TEXTURES/exit_open.xpm", &width, &height);
    if (!game->tex.exit_open)
        ft_printf("Error: Failed to load exit_open.xpm\n");
}

void render_map(t_game *game)
{
    int x;
    int y;

    y = 0;
    while (y < game->height)
    {
        x = 0;
        while (x < game->width)
        {
            if (game->map[y][x] == '1' && game->tex.wall)
                mlx_put_image_to_window(game->mlx, game->win, game->tex.wall, x * TILE_SIZE, y * TILE_SIZE);
            else if (game->map[y][x] == '0' && game->tex.floor)
                mlx_put_image_to_window(game->mlx, game->win, game->tex.floor, x * TILE_SIZE, y * TILE_SIZE);
            else if (game->map[y][x] == 'C' && game->tex.collectible)
                mlx_put_image_to_window(game->mlx, game->win, game->tex.collectible, x * TILE_SIZE, y * TILE_SIZE);
            else if (game->map[y][x] == 'E')
            {
                if (game->collectibles == 0 && game->tex.exit_open)
                    mlx_put_image_to_window(game->mlx, game->win, game->tex.exit_open, x * TILE_SIZE, y * TILE_SIZE);
                else if (game->tex.exit)
                    mlx_put_image_to_window(game->mlx, game->win, game->tex.exit, x * TILE_SIZE, y * TILE_SIZE);
            }
            x++;
        }
        y++;
    }

    y = 0;
    while (y < game->height)
    {
        x = 0;
        while (x < game->width)
        {
            if (game->map[y][x] == 'P' && game->current_player_tex)
                mlx_put_image_to_window(game->mlx, game->win, game->current_player_tex, x * TILE_SIZE, y * TILE_SIZE);
            x++;
        }
        y++;
    }
}