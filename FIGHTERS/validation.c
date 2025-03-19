/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 03:45:23 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/19 04:09:58 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	validate_map(t_game *game)
{
	int	x = 0;
	int	y = 0;
	int	p_count = 0;
	int	e_count = 0;
	int	c_count = 0;

	while (y < game->height)
	{
		x = 0;
		if (y == 0 || y == game->height - 1)
		{
			while (x < game->width)
			{
				if (game->map[y][x] != '1')
					return (0);
				x++;
			}
		}
		else
		{
			if (game->map[y][0] != '1' || game->map[y][game->width - 1] != '1')
				return (0);
		}
		y++;
	}
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] == 'P')
				p_count++;
			else if (game->map[y][x] == 'E')
				e_count++;
			else if (game->map[y][x] == 'C')
				c_count++;
			else if (game->map[y][x] != '0' && game->map[y][x] != '1')
				return (0);
			x++;
		}
		y++;
	}
	return (p_count == 1 && e_count == 1 && c_count >= 1);
}
