/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 01:08:10 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/19 04:09:35 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	main(int argc, char **argv)
{
	t_game	game = {0};

	if (argc != 2)
	{
		ft_printf("Error: Usage: ./so_long <map>.ber\n");
		return (1);
	}
	parse_map(&game, argv[1]);
	if (!validate_map(&game))
	{
		ft_printf("Error: Invalid map\n");
		return (1);
	}
	find_player(&game);
	count_collectibles(&game);
	game.mlx = mlx_init();
	if (!game.mlx)
	{
		ft_printf("Error: MiniLibX initialization failed\n");
		return (1);
	}
	game.win = mlx_new_window(game.mlx, game.width * 32, game.height * 32, "So Long");
	if (!game.win)
	{
		ft_printf("Error: Window creation failed\n");
		return (1);
	}
	load_textures(&game);
	render_map(&game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_key_hook(game.win, key_hook, &game);
	mlx_loop(game.mlx);
	return (0);
}
int	close_window(t_game *game)
{
	int	i = 0;

	mlx_destroy_window(game->mlx, game->win);
	while (i < game->height)
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	exit(0);
}