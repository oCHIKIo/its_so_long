/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:52:38 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/23 04:04:40 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void init_graphics(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        ft_putstr_fd("\033[1;31mError: MLX initialization failed\033[0m\n", 2);
        exit(1);
    }
    game->win = mlx_new_window(game->mlx, game->width * TILE_SIZE, 
                              game->height * TILE_SIZE + (TILE_SIZE / 2), "so_long"); // Add half a tile for border
    if (!game->win)
    {
        ft_putstr_fd("\033[1;31mError: Window creation failed\033[0m\n", 2);
        exit(1);
    }
    mlx_hook(game->win, 17, 0, close_window, game);
    load_textures(game);
}

void	load_textures(t_game *game)
{
	int w, h;
	game->img[0] = mlx_xpm_file_to_image(game->mlx, "./TEXTURES/floor.xpm", &w,
			&h);
	game->img[1] = mlx_xpm_file_to_image(game->mlx, "./TEXTURES/wall.xpm", &w,
			&h);
	game->img[2] = mlx_xpm_file_to_image(game->mlx,
			"./TEXTURES/collectible.xpm", &w, &h);
	game->img[3] = mlx_xpm_file_to_image(game->mlx, "./TEXTURES/exit.xpm", &w,
			&h);
	game->img[4] = mlx_xpm_file_to_image(game->mlx,
			"./TEXTURES/player_looking_direct.xpm", &w, &h);
	game->img[5] = mlx_xpm_file_to_image(game->mlx,
			"./TEXTURES/player_looking_left.xpm", &w, &h);
	game->img[6] = mlx_xpm_file_to_image(game->mlx,
			"./TEXTURES/player_looking_right.xpm", &w, &h);
	game->img[7] = mlx_xpm_file_to_image(game->mlx,
			"./TEXTURES/player_looking_back.xpm", &w, &h);
	game->img[8] = mlx_xpm_file_to_image(game->mlx,
			"./TEXTURES/in_top_of_exit.xpm", &w, &h);
	game->img[9] = mlx_xpm_file_to_image(game->mlx, "./TEXTURES/exit_open.xpm",
			&w, &h);
}

void render_map(t_game *game)
{
    int x, y = 0;
    int i = 0;
    
    while (y < game->height)
    {
        x = 0;
        while (x < game->width)
        {
                mlx_put_image_to_window(game->mlx, game->win, game->img[0], x * TILE_SIZE, y * TILE_SIZE);
            if (game->map[i] == '1')
                mlx_put_image_to_window(game->mlx, game->win, game->img[1], x * TILE_SIZE, y * TILE_SIZE);
            else if (game->map[i] == 'C')
                mlx_put_image_to_window(game->mlx, game->win, game->img[2], x * TILE_SIZE, y * TILE_SIZE);
            else if (game->map[i] == 'E')
                render_exit(game, x, y);
            else if (game->map[i] == 'P' && game->player_x == x && game->player_y == y)
                render_player(game, x, y);
            
            x++;
            i++;
        }
        i++;
        y++;
    }
}

