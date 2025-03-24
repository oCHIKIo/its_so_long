/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_support.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:10:19 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/24 08:44:27 by bchiki           ###   ########.fr       */
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

	if (game->player_x == game->exit_x && game->player_y == game->exit_y
		&& game->collectibles > 0)
		return ;
	img_index = 4;
	if (game->last_dx == 1)
		img_index = 6;
	else if (game->last_dx == -1)
		img_index = 5;
	else if (game->last_dy == 1)
		img_index = 4;
	else if (game->last_dy == -1)
		img_index = 7;
	if (img_index < 4 || img_index > 9 || !game->img[img_index])
	{
		ft_putstr_fd("\033[1;31mError: Invalid player texture index\033[0m\n",
			2);
		close_window(game);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img[img_index], x
		* TILE_SIZE, y * TILE_SIZE);
}

void	load_textures(t_game *game)
{
	int	w;
	int	h;

	game->img[0] = mlx_xpm_file_to_image(game->mlx, "./textures/floor.xpm", &w,
			&h);
	game->img[1] = mlx_xpm_file_to_image(game->mlx, "./textures/wall.xpm", &w,
			&h);
	game->img[2] = mlx_xpm_file_to_image(game->mlx,
			"./textures/collectible.xpm", &w, &h);
	game->img[3] = mlx_xpm_file_to_image(game->mlx, "./textures/exit.xpm", &w,
			&h);
	game->img[4] = mlx_xpm_file_to_image(game->mlx,
			"./textures/player_looking_direct.xpm", &w, &h);
	game->img[5] = mlx_xpm_file_to_image(game->mlx,
			"./textures/player_looking_left.xpm", &w, &h);
	game->img[6] = mlx_xpm_file_to_image(game->mlx,
			"./textures/player_looking_right.xpm", &w, &h);
	game->img[7] = mlx_xpm_file_to_image(game->mlx,
			"./textures/player_looking_back.xpm", &w, &h);
	game->img[8] = mlx_xpm_file_to_image(game->mlx,
			"./textures/in_top_of_exit.xpm", &w, &h);
	game->img[9] = mlx_xpm_file_to_image(game->mlx, "./textures/exit_open.xpm",
			&w, &h);
}
