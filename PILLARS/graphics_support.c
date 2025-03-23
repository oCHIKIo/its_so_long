/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_support.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:10:19 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/23 02:35:38 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	render_exit(t_game *game, int x, int y)
{
	if (game->collectibles > 0)
		mlx_put_image_to_window(game->mlx, game->win, game->img[3], x
			* TILE_SIZE, y * TILE_SIZE);
	else
		mlx_put_image_to_window(game->mlx, game->win, game->img[9], x
			* TILE_SIZE, y * TILE_SIZE);
	if (game->player_x == x && game->player_y == y && game->collectibles > 0)
		mlx_put_image_to_window(game->mlx, game->win, game->img[8], x
			* TILE_SIZE, y * TILE_SIZE);
}

void	render_player(t_game *game, int x, int y)
{
	int	img_index;

	img_index = 4;
	if (game->last_dx == 1)
		img_index = 6;
	else if (game->last_dx == -1)
		img_index = 5;
	else if (game->last_dy == 1)
		img_index = 4;
	else if (game->last_dy == -1)
		img_index = 7;
	mlx_put_image_to_window(game->mlx, game->win, game->img[img_index], x
		* TILE_SIZE, y * TILE_SIZE);
}
