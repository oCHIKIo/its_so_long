/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:10:47 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/22 02:56:07 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	allocate_map(t_game *game, char *content)
{
	game->map = malloc(sizeof(char *) * game->height);
	if (!game->map)
	{
		free(content);
		ft_printf("\033[1;38;5;51mError: Memory allocation failed for map\033[0m\n");
		exit(1);
	}
}

void	parse_map(t_game *game, char *filename)
{
	char	*content;

	content = read_file(filename);
	if (!content)
	{
		ft_printf("\033[1;38;5;51mError: Failed to read map\033[0m\n");
		exit(1);
	}
	check_trailing_empty_lines(content);
	count_map_height(game, content);
	allocate_map(game, content);
	split_map_content(game, content);
	set_map_width(game);
	free(content);
}
