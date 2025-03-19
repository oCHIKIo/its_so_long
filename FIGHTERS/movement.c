/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 03:44:25 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/19 04:09:44 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	find_player(t_game *game)
{
	int	x = 0;
	int	y = 0;

	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	count_collectibles(t_game *game)
{
	int	x = 0;
	int	y = 0;

	game->collectibles = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] == 'C')
				game->collectibles++;
			x++;
		}
		y++;
	}
}

void	move_player(t_game *game, int dx, int dy)
{
	int	new_x = game->player_x + dx;
	int	new_y = game->player_y + dy;

	if (new_x >= 0 && new_x < game->width && new_y >= 0 && new_y < game->height &&
		game->map[new_y][new_x] != '1')
	{
		if (game->map[new_y][new_x] == 'C')
			game->collectibles--;
		if (game->map[new_y][new_x] == 'E' && game->collectibles == 0)
			close_window(game);
		else if (game->map[new_y][new_x] != 'E')
		{
			game->map[game->player_y][game->player_x] = '0';
			game->player_x = new_x;
			game->player_y = new_y;
			game->map[new_y][new_x] = 'P';
			game->moves++;
			ft_printf("Moves: %d\n", game->moves);
			render_map(game);
		}
	}
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == 13) // W
		move_player(game, 0, -1);
	else if (keycode == 0) // A
		move_player(game, -1, 0);
	else if (keycode == 1) // S
		move_player(game, 0, 1);
	else if (keycode == 2) // D
		move_player(game, 1, 0);
	else if (keycode == 53) // ESC
		close_window(game);
	return (0);
}