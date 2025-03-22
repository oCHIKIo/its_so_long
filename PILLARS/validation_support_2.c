/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_support_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 01:42:37 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/22 03:14:11 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	check_for_empty_lines(t_game *game)
{
	int	y;

	y = 0;
	while (y < game->height)
	{
		if (game->map[y][0] == '\0')
		{
			ft_printf("\033[1;38;5;51mError: Intruder line\033[0m\n");
			return (0);
		}
		y++;
	}
	return (1);
}

int	check_map_walls(t_game *game)
{
	t_nbr	nbr;

	nbr.y = 0;
	while (nbr.y < game->height)
	{
		nbr.x = 0;
		while (nbr.x < game->width)
		{
			if ((nbr.y == 0 || nbr.y == game->height - 1)
				&& game->map[nbr.y][nbr.x] != '1')
			{
				ft_printf("\033[1;38;5;51mError: Top or bottom wall is not fully '1'\033[0m\n");
				return (0);
			}
			if ((nbr.x == 0 || nbr.x == game->width - 1)
				&& game->map[nbr.y][nbr.x] != '1')
			{
				ft_printf("\033[1;38;5;51mError: Left or right wall is not fully '1'\033[0m\n");
				return (0);
			}
			nbr.x++;
		}
		nbr.y++;
	}
	return (1);
}

int	check_empty_lines_and_walls(t_game *game)
{
	if (!check_for_empty_lines(game))
		return (0);
	if (!check_map_walls(game))
		return (0);
	return (1);
}

int	validate_element_counts(int p_count, int e_count, int c_count)
{
	if (p_count != 1)
	{
		ft_printf("\033[1;38;5;51mError: Map must have exactly one player (P)\033[0m\n");
		return (0);
	}
	if (e_count != 1)
	{
		ft_printf("\033[1;38;5;51mError: Map must have exactly one exit (E)\033[0m\n");
		return (0);
	}
	if (c_count == 0)
	{
		ft_printf("\033[1;38;5;51mError: Map must have at least one collectible (C)\033[0m\n");
		return (0);
	}
	return (1);
}

int	check_player_surrounded(t_game *game)
{
	if (game->player_x > 0 && game->player_x < game->width - 1
		&& game->player_y > 0 && game->player_y < game->height - 1)
	{
		if (game->map[game->player_y - 1][game->player_x] == '1'
			&& game->map[game->player_y + 1][game->player_x] == '1'
			&& game->map[game->player_y][game->player_x - 1] == '1'
			&& game->map[game->player_y][game->player_x + 1] == '1')
		{
			ft_printf("\033[1;38;5;51mError: Player is completely surrounded by walls noobie\033[0m\n");
			return (0);
		}
	}
	return (1);
}
