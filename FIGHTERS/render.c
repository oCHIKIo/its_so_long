/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 03:42:49 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/19 04:09:54 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	load_textures(t_game *game)
{
	int	width = 32;
	int	height = 32;

	game->tex.wall = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm", &width, &height);
	game->tex.floor = mlx_xpm_file_to_image(game->mlx, "textures/floor.xpm", &width, &height);
	game->tex.player = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm", &width, &height);
	game->tex.collectible = mlx_xpm_file_to_image(game->mlx, "textures/collectible.xpm", &width, &height);
	game->tex.exit = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm", &width, &height);
}

void	render_map(t_game *game)
{
	int	x = 0;
	int	y = 0;

	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->tex.wall, x * 32, y * 32);
			else if (game->map[y][x] == '0')
				mlx_put_image_to_window(game->mlx, game->win, game->tex.floor, x * 32, y * 32);
			else if (game->map[y][x] == 'P')
				mlx_put_image_to_window(game->mlx, game->win, game->tex.player, x * 32, y * 32);
			else if (game->map[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, game->tex.collectible, x * 32, y * 32);
			else if (game->map[y][x] == 'E')
				mlx_put_image_to_window(game->mlx, game->win, game->tex.exit, x * 32, y * 32);
			x++;
		}
		y++;
	}
}