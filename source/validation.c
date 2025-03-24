/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:52:54 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/24 08:44:07 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static t_flood	flood_fill(char *map, t_game *game, t_flood state)
{
	t_flood	new_state;

	if (!is_valid_position(state, state.x, state.y, map))
		return (state);
	state = check_cell(map, state);
	new_state = flood_fill(map, game, (t_flood){state.x - 1, state.y,
			state.collectibles, state.exit, state.width, state.height});
	update_state(&state, new_state);
	new_state = flood_fill(map, game, (t_flood){state.x + 1, state.y,
			state.collectibles, state.exit, state.width, state.height});
	update_state(&state, new_state);
	new_state = flood_fill(map, game, (t_flood){state.x, state.y - 1,
			state.collectibles, state.exit, state.width, state.height});
	update_state(&state, new_state);
	new_state = flood_fill(map, game, (t_flood){state.x, state.y + 1,
			state.collectibles, state.exit, state.width, state.height});
	update_state(&state, new_state);
	return (state);
}

static int	check_top_bottom_walls(t_game *game, t_nbr *nbr)
{
	nbr->i = 0;
	nbr->len = ft_strlen(game->map);
	nbr->last_line_start = nbr->len - game->width - 1;
	while (nbr->last_line_start > 0 && game->map[nbr->last_line_start] != '\n')
		nbr->last_line_start--;
	if (nbr->last_line_start > 0)
		nbr->last_line_start++;
	while (nbr->i < game->width)
	{
		if (game->map[nbr->i] != '1'
			|| game->map[nbr->last_line_start + nbr->i] != '1')
			return (0);
		nbr->i++;
	}
	return (1);
}

static int	check_side_walls(t_game *game, t_nbr *nbr)
{
	nbr->i = 0;
	while (nbr->i < game->height)
	{
		nbr->j = nbr->i * (game->width + 1);
		if (nbr->j >= nbr->len || game->map[nbr->j] != '1'
			|| game->map[nbr->j + game->width - 1] != '1')
			return (0);
		nbr->i++;
	}
	return (1);
}

int	check_accessibility(t_game *game)
{
	char	*map_copy;
	t_flood	state;

	state.x = game->player_x;
	state.y = game->player_y;
	state.collectibles = game->collectibles;
	state.exit = 0;
	state.width = game->width;
	state.height = game->height;
	map_copy = ft_strdup(game->map);
	if (!map_copy)
	{
		ft_putstr_fd("\033[1;31mError: Memory allocation failed\033[0m\n", 2);
		return (0);
	}
	state = flood_fill(map_copy, game, state);
	if (state.collectibles > 0 || state.exit == 0)
	{
		ft_putstr_fd("\033[1;31mError: Unreachable items/exit\033[0m\n", 2);
		free(map_copy);
		return (0);
	}
	free(map_copy);
	return (1);
}

int	check_walls(t_game *game)
{
	t_nbr	nbr;

	if (!check_top_bottom_walls(game, &nbr))
		return (0);
	if (!check_side_walls(game, &nbr))
		return (0);
	return (1);
}
