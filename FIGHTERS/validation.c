/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:52:54 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/23 05:57:51 by bchiki           ###   ########.fr       */
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

int	check_walls(t_game *game)
{
	int	i;
	int	j;
	int	len;
	int	last_line_start;

	i = 0;
	len = ft_strlen(game->map);
	last_line_start = len - game->width - 1;
	while (last_line_start > 0 && game->map[last_line_start] != '\n')
		last_line_start--;
	if (last_line_start > 0)
		last_line_start++;
	while (i < game->width)
	{
		if (game->map[i] != '1' || game->map[last_line_start + i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < game->height)
	{
		j = i * (game->width + 1);
		if (j >= len || game->map[j] != '1' || game->map[j + game->width
			- 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_empty_lines(char *map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i] == '\n' && map[i + 1] == '\n')
			return (0);
		i++;
	}
	return (1);
}

int check_accessibility(t_game *game)
{
    char *map_copy = ft_strdup(game->map);
    t_flood state = {game->player_x, game->player_y, game->collectibles, 0, game->width, game->height};
	
    if (!map_copy)
    {
        ft_putstr_fd("\033[1;31mError: Memory allocation failed\033[0m\n", 2);
        return (0);
    }
    state = flood_fill(map_copy, game, state);
    if (state.collectibles > 0 || state.exit == 0)
    {
        ft_putstr_fd("\033[1;31mError: Unreachable collectibles and/or exit\033[0m\n", 2);
        free(map_copy);
        return (0);
    }
    free(map_copy);
    return (1);
}
