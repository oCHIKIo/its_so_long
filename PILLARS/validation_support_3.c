/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_support_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 01:48:43 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/22 03:16:37 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	handle_map_element(t_game *game, int x, int y, int *p_count, int *e_count,
		int *c_count)
{
	if (game->map[y][x] == 'P')
	{
		(*p_count)++;
		game->player_x = x;
		game->player_y = y;
	}
	else if (game->map[y][x] == 'E')
		(*e_count)++;
	else if (game->map[y][x] == 'C')
		(*c_count)++;
	else if (game->map[y][x] != '0' && game->map[y][x] != '1')
	{
		ft_printf("\033[1;38;5;51mError: Invalid character '%c' in map\033[0m\n",
			game->map[y][x]);
		return (0);
	}
	return (1);
}

int	count_map_elements(t_game *game, int *p_count, int *e_count, int *c_count)
{
	t_nbr	nbr;

	nbr.y = 0;
	while (nbr.y < game->height)
	{
		nbr.x = 0;
		while (nbr.x < game->width)
		{
			if (!handle_map_element(game, nbr.x, nbr.y, p_count, e_count,
					c_count))
				return (0);
			nbr.x++;
		}
		nbr.y++;
	}
	return (1);
}
