/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_support_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 01:41:54 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/22 01:42:21 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	is_all_walls(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] != '1')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

void	flood_fill(t_game *game, int x, int y, int *collectibles_reached,
		int *exit_reached, char **visited)
{
	if (x < 0 || x >= game->width || y < 0 || y >= game->height || visited[y][x]
		|| game->map[y][x] == '1')
		return ;
	visited[y][x] = 1;
	if (game->map[y][x] == 'C')
		(*collectibles_reached)++;
	if (game->map[y][x] == 'E')
		(*exit_reached)++;
	flood_fill(game, x + 1, y, collectibles_reached, exit_reached, visited);
	flood_fill(game, x - 1, y, collectibles_reached, exit_reached, visited);
	flood_fill(game, x, y + 1, collectibles_reached, exit_reached, visited);
	flood_fill(game, x, y - 1, collectibles_reached, exit_reached, visited);
}
