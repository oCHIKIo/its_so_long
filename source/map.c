/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:52:24 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/24 08:43:48 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

char	*read_map(char *file)
{
	t_nbr	nbr;
	char	*map;
	char	c;

	nbr.fd = open(file, O_RDONLY);
	nbr.size = get_file_size(file);
	map = malloc(nbr.size + 1);
	if (!map)
	{
		ft_putstr_fd("\033[1;31mError: Memory allocation failed\033[0m\n", 2);
		exit(1);
	}
	nbr.i = 0;
	while (read(nbr.fd, &c, 1) > 0)
		map[nbr.i++] = c;
	map[nbr.i] = '\0';
	close(nbr.fd);
	return (map);
}

int	check_map_validity(t_game *game)
{
	int	all_walls;

	all_walls = 1;
	if (!check_start_line(game))
		return (0);
	if (!get_map_width(game))
		return (0);
	if (!check_map_lines(game, &all_walls))
		return (0);
	if (!check_end_conditions(game, all_walls))
		return (0);
	return (1);
}

void	count_elements(t_game *game)
{
	t_count	count;

	init_counts(game, &count);
	while (count.y < game->height)
	{
		count.x = 0;
		while (count.x < game->width)
		{
			if (!check_symbol(game, &count))
				return ;
			if (!check_player_exit(game, &count))
				return ;
			count.x++;
			count.i++;
		}
		count.i++;
		count.y++;
	}
}
