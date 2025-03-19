/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 03:35:11 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/19 04:09:39 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static char	*read_file(char *filename)
{
	int		fd = open(filename, O_RDONLY);
	char	*buffer = malloc(1024);
	char	*line = NULL;
	ssize_t	bytes;

	if (fd < 0)
	{
		perror("Error opening file");
		return (NULL);
	}
	bytes = read(fd, buffer, 1024);
	if (bytes <= 0)
	{
		free(buffer);
		close(fd);
		return (NULL);
	}
	buffer[bytes] = '\0';
	line = buffer;
	close(fd);
	return (line);
}

void	parse_map(t_game *game, char *filename)
{
	char	*content = read_file(filename);
	char	*temp = content;
	int		i = 0;

	if (!content)
	{
		ft_printf("Error: Failed to read map\n");
		exit(1);
	}
	game->height = 0;
	while (*temp)
	{
		if (*temp == '\n')
			game->height++;
		temp++;
	}
	game->height++;
	game->map = malloc(sizeof(char *) * game->height);
	temp = content;
	while (i < game->height)
	{
		game->map[i] = temp;
		while (*temp && *temp != '\n')
			temp++;
		if (*temp == '\n')
		{
			*temp = '\0';
			temp++;
		}
		i++;
	}
	game->width = 0;
	while (game->map[0][game->width])
		game->width++;
	free(content);
}