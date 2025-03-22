/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_support_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 01:11:23 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/22 03:09:57 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	key_release(int keycode, t_game *game)
{
	if (keycode == 119)
		game->keys.w_pressed = 0;
	else if (keycode == 97)
		game->keys.a_pressed = 0;
	else if (keycode == 115)
		game->keys.s_pressed = 0;
	else if (keycode == 100)
		game->keys.d_pressed = 0;
	return (0);
}

void	calculate_new_position(t_game *game, int dx, int dy, int *new_x,
		int *new_y)
{
	*new_x = game->player_x + dx;
	*new_y = game->player_y + dy;
}

int	count_collectibles(t_game *game)
{
	int		collectible_count;
	t_nbr	nbr;

	collectible_count = 0;
	nbr.y = 0;
	while (nbr.y < game->height)
	{
		nbr.x = 0;
		while (nbr.x < game->width)
		{
			if (game->map[nbr.y][nbr.x] == 'C')
				collectible_count++;
			nbr.x++;
		}
		nbr.y++;
	}
	return (collectible_count);
}

int	is_valid_move(t_game *game, int new_x, int new_y)
{
	return (new_x >= 0 && new_x < game->width && new_y >= 0
		&& new_y < game->height && game->map[new_y][new_x] != '1');
}

void	handle_collectible(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == 'C')
	{
		game->collectibles--;
		game->map[new_y][new_x] = '0';
		if (game->collectibles == 0)
			game->tried_to_exit = 0;
	}
}
