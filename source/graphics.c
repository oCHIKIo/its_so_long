/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:52:38 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/29 05:19:54 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	destroy_images(t_game *game)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		if (game->img[i])
			mlx_destroy_image(game->mlx, game->img[i]);
		i++;
	}
}

void	init_graphics(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_putstr_fd("\033[1;31mError: MLX initialization failed\033[0m\n", 2);
		free(game->map);
		exit(1);
	}
	game->win = mlx_new_window(game->mlx, game->width * TILE_SIZE, game->height
			* TILE_SIZE, "so_long");
	if (!game->win)
	{
		ft_putstr_fd("\033[1;31mError: Window creation failed\033[0m\n", 2);
		free(game->map);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		exit(1);
	}
	mlx_hook(game->win, 17, 0, close_window, game);
	load_textures(game);
}

static void	render_tile(t_game *game, t_nbr *nbr)
{
	mlx_put_image_to_window(game->mlx, game->win, game->img[0], nbr->x
		* TILE_SIZE, nbr->y * TILE_SIZE);
	if (game->map[nbr->i] == '1')
		mlx_put_image_to_window(game->mlx, game->win, game->img[1], nbr->x
			* TILE_SIZE, nbr->y * TILE_SIZE);
	else if (game->map[nbr->i] == 'C')
		mlx_put_image_to_window(game->mlx, game->win, game->img[2], nbr->x
			* TILE_SIZE, nbr->y * TILE_SIZE);
	else if (game->map[nbr->i] == 'E')
		render_exit(game, nbr->x, nbr->y);
	if (nbr->x == game->player_x && nbr->y == game->player_y)
		render_player(game, nbr->x, nbr->y);
}

static void	render_row(t_game *game, t_nbr *nbr)
{
	nbr->x = 0;
	while (nbr->x < game->width)
	{
		render_tile(game, nbr);
		nbr->x++;
		nbr->i++;
	}
	if (game->map[nbr->i] == '\n')
		nbr->i++;
}

void	render_map(t_game *game)
{
	t_nbr	nbr;

	nbr.y = 0;
	nbr.x = 0;
	nbr.i = 0;
	while (nbr.y < game->height)
	{
		render_row(game, &nbr);
		nbr.y++;
	}
}
