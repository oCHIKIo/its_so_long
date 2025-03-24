/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_support.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:12:57 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/24 08:44:58 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	check_final_validations(t_game *game)
{
	if (game->player_x == -1 || game->collectibles < 1)
	{
		if (game->player_x == -1)
			ft_putstr_fd("\033[1;31mError: No player found\033[0m\n", 2);
		else if (game->collectibles < 1)
			ft_putstr_fd("\033[1;31mError: No collectibles found\033[0m\n", 2);
		return (0);
	}
	return (check_accessibility(game));
}

static int	process_map_lines(t_game *game, t_nbr *nbr, int *all_walls)
{
	while (nbr->i < nbr->len)
	{
		if (!check_line_length(game, &nbr->i, all_walls))
			return (0);
		if (nbr->i < nbr->len && game->map[nbr->i] == '\n')
		{
			nbr->height++;
			nbr->i++;
			if (nbr->i < nbr->len && game->map[nbr->i] == '\n')
			{
				ft_putstr_fd("\033[1;31mError: Empty line in map\033[0m\n", 2);
				return (0);
			}
		}
	}
	return (1);
}

int	check_map_lines(t_game *game, int *all_walls)
{
	t_nbr	nbr;

	nbr.i = 0;
	nbr.height = 0;
	nbr.len = ft_strlen(game->map);
	if (nbr.len > 0 && game->map[nbr.len - 1] == '\n')
	{
		ft_putstr_fd("\033[1;31mError: Empty line in map\033[0m\n", 2);
		return (0);
	}
	if (!process_map_lines(game, &nbr, all_walls))
		return (0);
	game->height = nbr.height + 1;
	return (1);
}
