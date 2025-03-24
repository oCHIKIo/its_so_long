/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_support2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:11:28 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/24 08:45:07 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	check_end_conditions(t_game *game, int all_walls)
{
	if (!check_walls(game))
	{
		ft_putstr_fd("\033[1;31mError: Invalid walls\033[0m\n", 2);
		return (0);
	}
	if (all_walls)
	{
		ft_putstr_fd("\033[1;31mError: Map is all walls\033[0m\n", 2);
		return (0);
	}
	count_elements(game);
	if (game->collectibles == -1)
		return (0);
	return (check_final_validations(game));
}

int	check_symbol(t_game *game, t_count *count)
{
	char	c;

	c = game->map[count->i];
	if (c != '0' && c != '1' && c != 'P' && c != 'C' && c != 'E')
	{
		ft_printf("\033[1;31mError: Foreign character '%c' found\033[0m\n", c);
		game->collectibles = -1;
		return (0);
	}
	if (c == 'C')
		game->collectibles++;
	return (1);
}

static int	check_player(t_game *game, t_count *count, char c)
{
	if (c == 'P')
	{
		count->player_count++;
		if (count->player_count > 1)
		{
			game->map[count->i] = '0';
			ft_putstr_fd("\033[1;31mError: Multiple players found\033[0m\n", 2);
			game->collectibles = -1;
			return (0);
		}
		game->player_x = count->x;
		game->player_y = count->y;
	}
	return (1);
}

static int	check_map_exit(t_game *game, t_count *count, char c)
{
	if (c == 'E')
	{
		count->exit_count++;
		if (count->exit_count > 1)
		{
			ft_putstr_fd("\033[1;31mError: Multiple exits found\033[0m\n", 2);
			game->collectibles = -1;
			return (0);
		}
		game->exit_x = count->x;
		game->exit_y = count->y;
	}
	return (1);
}

int	check_player_exit(t_game *game, t_count *count)
{
	char	c;

	c = game->map[count->i];
	if (!check_player(game, count, c))
		return (0);
	if (!check_map_exit(game, count, c))
		return (0);
	return (1);
}
