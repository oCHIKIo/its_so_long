/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_support.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:07:22 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/24 08:45:39 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	update_state(t_flood *state, t_flood new_state)
{
	state->collectibles = new_state.collectibles;
	state->exit = new_state.exit;
}

int	is_valid_position(t_flood state, int x, int y, char *map)
{
	int	pos;

	if (x < 0 || x >= state.width || y < 0 || y >= state.height)
		return (0);
	pos = y * (state.width + 1) + x;
	if (map[pos] == '1' || map[pos] == 'X')
		return (0);
	return (1);
}

t_flood	check_cell(char *map, t_flood state)
{
	int	pos;

	pos = state.y * (state.width + 1) + state.x;
	if (map[pos] == 'C')
		state.collectibles--;
	if (map[pos] == 'E')
		state.exit = 1;
	map[pos] = 'X';
	return (state);
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
