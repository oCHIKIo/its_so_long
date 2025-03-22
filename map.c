/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:52:24 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/22 20:43:20 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int get_file_size(char *file)
{
    int fd = open(file, O_RDONLY);
    int size = 0;
    char buf[1024];
    int bytes;
    if (fd < 0)
    {
        ft_putstr_fd("Error: Cannot open file\n", 2);
        exit(1);
    }
    while ((bytes = read(fd, buf, 1024)) > 0)
        size += bytes;
    close(fd);
    return (size);
}

char    *read_map(char *file)
{
    int fd = open(file, O_RDONLY);
    int size = get_file_size(file);
    char *map = malloc(size + 1);
    int i = 0;
    char c;
    if (!map)
    {
        ft_putstr_fd("Error: Memory allocation failed\n", 2);
        exit(1);
    }
    while (read(fd, &c, 1) > 0)
        map[i++] = c;
    map[i] = '\0';
    close(fd);
    return (map);
}

int     check_map_validity(t_game *game)
{
    int i = 0;
    int width = 0;

    while (game->map[i] && game->map[i] != '\n')
    {
        width++;
        i++;
    }
    game->width = width;

    i = 0;
    int height = 1;
    while (game->map[i])
    {
        if (game->map[i] == '\n')
            height++;
        i++;
    }
    game->height = height;

    if (!check_walls(game) || !check_empty_lines(game->map))
        return (0);
    count_elements(game);
    if (game->collectibles < 1 || game->player_x == -1 || game->exit_x == -1)
        return (0);
    return (check_accessibility(game));
}

void    count_elements(t_game *game)
{
    int i = 0;
    int x = 0;
    int y = 0;
    game->collectibles = 0;
    game->player_x = -1;
    game->exit_x = -1;
    while (game->map[i])
    {
        if (game->map[i] == '\n')
        {
            x = 0;
            y++;
        }
        else
        {
            if (game->map[i] == 'C')
                game->collectibles++;
            else if (game->map[i] == 'P' && game->player_x == -1)
            {
                game->player_x = x;
                game->player_y = y;
            }
            else if (game->map[i] == 'E' && game->exit_x == -1)
            {
                game->exit_x = x;
                game->exit_y = y;
            }
            x++;
        }
        i++;
    }
}
