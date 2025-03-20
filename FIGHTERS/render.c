/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 03:42:49 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/20 04:03:50 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void load_textures(t_game *game)
{
    int width;
    int height;

    game->tex.wall = mlx_xpm_file_to_image(game->mlx, "TEXTURES/wall.xpm", &width, &height);
    if (!game->tex.wall)
        ft_printf("Error: Failed to load TEXTURES/wall.xpm\n");
    game->tex.floor = mlx_xpm_file_to_image(game->mlx, "TEXTURES/floor.xpm", &width, &height);
    if (!game->tex.floor)
        ft_printf("Error: Failed to load TEXTURES/floor.xpm\n");
    game->tex.player_looking_right = mlx_xpm_file_to_image(game->mlx, "TEXTURES/player_looking_right.xpm", &width, &height);
    if (!game->tex.player_looking_right)
        ft_printf("Error: Failed to load TEXTURES/player_looking_right.xpm\n");
    game->tex.player_looking_left = mlx_xpm_file_to_image(game->mlx, "TEXTURES/player_looking_left.xpm", &width, &height);
    if (!game->tex.player_looking_left)
        ft_printf("Error: Failed to load TEXTURES/player_looking_left.xpm\n");
    game->tex.player_looking_back = mlx_xpm_file_to_image(game->mlx, "TEXTURES/player_looking_back.xpm", &width, &height);
    if (!game->tex.player_looking_back)
        ft_printf("Error: Failed to load TEXTURES/player_looking_back.xpm\n");
    game->tex.player_looking_direct = mlx_xpm_file_to_image(game->mlx, "TEXTURES/player_looking_direct.xpm", &width, &height);
    if (!game->tex.player_looking_direct)
        ft_printf("Error: Failed to load TEXTURES/player_looking_direct.xpm\n");
    game->tex.collectible = mlx_xpm_file_to_image(game->mlx, "TEXTURES/collectible.xpm", &width, &height);
    if (!game->tex.collectible)
        ft_printf("Error: Failed to load TEXTURES/collectible.xpm\n");
    game->tex.exit = mlx_xpm_file_to_image(game->mlx, "TEXTURES/exit.xpm", &width, &height);
    if (!game->tex.exit)
        ft_printf("Error: Failed to load TEXTURES/exit.xpm\n");
    game->tex.exit_open = mlx_xpm_file_to_image(game->mlx, "TEXTURES/exit_open.xpm", &width, &height);
    if (!game->tex.exit_open)
        ft_printf("Error: Failed to load TEXTURES/exit_open.xpm\n");
    game->tex.in_top_of_exit = mlx_xpm_file_to_image(game->mlx, "TEXTURES/in_top_of_exit.xpm", &width, &height);
    if (!game->tex.in_top_of_exit)
        ft_printf("Error: Failed to load TEXTURES/in_top_of_exit.xpm\n");
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
            if (game->map[y][x] == '1')
                mlx_put_image_to_window(game->mlx, game->win, game->tex.wall, x * TILE_SIZE, y * TILE_SIZE);
            else
                mlx_put_image_to_window(game->mlx, game->win, game->tex.floor, x * TILE_SIZE, y * TILE_SIZE);
            if (game->map[y][x] == 'C')
                mlx_put_image_to_window(game->mlx, game->win, game->tex.collectible, x * TILE_SIZE, y * TILE_SIZE);
            if (game->map[y][x] == 'E')
            {
                if (game->collectibles == 0)
                    mlx_put_image_to_window(game->mlx, game->win, game->tex.exit_open, x * TILE_SIZE, y * TILE_SIZE);
                else if (game->player_x == x && game->player_y == y)
                    mlx_put_image_to_window(game->mlx, game->win, game->tex.in_top_of_exit, x * TILE_SIZE, y * TILE_SIZE);
                else
                    mlx_put_image_to_window(game->mlx, game->win, game->tex.exit, x * TILE_SIZE, y * TILE_SIZE);
            }
            if (game->map[y][x] == 'P')
                mlx_put_image_to_window(game->mlx, game->win, game->current_player_tex, x * TILE_SIZE, y * TILE_SIZE);
            x++;
        }
        y++;
    }
}