/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_support3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 06:41:39 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/24 08:45:17 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	check_start_line(t_game *game)
{
	if (game->map[0] == '\n')
	{
		ft_putstr_fd("\033[1;31mError: Empty line in map\033[0m\n", 2);
		return (0);
	}
	return (1);
}

int	get_map_width(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i] && game->map[i] != '\n')
		i++;
	game->width = i;
	return (1);
}

int	get_file_size(char *file)
{
	int		fd;
	int		size;
	char	buf[1024];
	int		bytes;

	fd = open(file, O_RDONLY);
	size = 0;
	if (fd < 0)
	{
		ft_putstr_fd("\033[1;31mError: Cannot open file\033[0m\n", 2);
		exit(1);
	}
	bytes = read(fd, buf, 1024);
	while (bytes > 0)
	{
		size += bytes;
		bytes = read(fd, buf, 1024);
	}
	close(fd);
	return (size);
}

int	check_line_length(t_game *game, int *i, int *all_walls)
{
	int	line_length;
	int	start;

	line_length = 0;
	start = *i;
	while (game->map[*i] && game->map[*i] != '\n')
	{
		if (game->map[*i] != '1')
			*all_walls = 0;
		line_length++;
		(*i)++;
	}
	if (line_length != game->width)
	{
		if (line_length == 0 && game->map[start] == '\n')
			ft_putstr_fd("\033[1;31mError: Empty line in map\033[0m\n", 2);
		else
			ft_putstr_fd("\033[1;31mError: Uneven map lines\033[0m\n", 2);
		return (0);
	}
	return (1);
}

void	init_counts(t_game *game, t_count *count)
{
	count->i = 0;
	count->x = 0;
	count->y = 0;
	count->exit_count = 0;
	count->player_count = 0;
	game->collectibles = 0;
	game->player_x = -1;
	game->exit_x = -1;
}
