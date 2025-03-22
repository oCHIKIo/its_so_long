/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:52:24 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/22 22:28:00 by bchiki           ###   ########.fr       */
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
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

int     check_map_validity(t_game *game)
{
    int i = 0;
    int width = 0;
    int line_length = 0;
    int height = 1;
    int all_walls = 1;

    if (game->map[0] == '\n')
    {
        ft_putstr_fd("Error: Empty line at start\n", 2);
        return (0);
    }

    while (game->map[i] && game->map[i] != '\n')
    {
        width++;
        i++;
    }
    game->width = width;

    i = 0;
    while (game->map[i])
    {
        line_length = 0;
        while (game->map[i] && game->map[i] != '\n')
        {
            if (game->map[i] != '1')
                all_walls = 0;
            line_length++;
            i++;
        }
        if (line_length != width)
        {
            ft_putstr_fd("Error: Uneven map lines\n", 2);
            return (0);
        }
        if (game->map[i] == '\n')
        {
            if (game->map[i + 1] == '\n' && game->map[i + 2] != '\0')
            {
                ft_putstr_fd("Error: Empty line in middle\n", 2);
                return (0);
            }
            height++;
            i++;
        }
    }
    game->height = height;

    if (game->map[i - 1] == '\n')
    {
        ft_putstr_fd("Error: Empty line at end\n", 2);
        return (0);
    }
    if (!check_walls(game))
    {
        ft_putstr_fd("Error: Invalid walls\n", 2);
        return (0);
    }
    if (all_walls)
    {
        ft_putstr_fd("Error: Map is all walls\n", 2);
        return (0);
    }
    count_elements(game);
    if (game->collectibles == -1)
        return (0);
    if (game->player_x == -1)
    {
        ft_putstr_fd("Error: No player found\n", 2);
        return (0);
    }
    if (game->collectibles < 1)
    {
        ft_putstr_fd("Error: No collectibles found\n", 2);
        return (0);
    }
    return (check_accessibility(game));
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

void    count_elements(t_game *game)
{
    int i = 0;
    int x = 0;
    int y = 0;
    int exit_count = 0;
    int player_count = 0;
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
            if (game->map[i] != '0' && game->map[i] != '1' && game->map[i] != 'P' && game->map[i] != 'C' && game->map[i] != 'E')
            {
                ft_printf("Error: Foreign symbol '%c' found\n", game->map[i]);
                game->collectibles = -1;
                return;
            }
            if (game->map[i] == 'C')
                game->collectibles++;
            else if (game->map[i] == 'P')
            {
                player_count++;
                if (player_count > 1)
                {
                    ft_putstr_fd("Error: Multiple players found\n", 2);
                    game->collectibles = -1;
                    return;
                }
                game->player_x = x;
                game->player_y = y;
            }
            else if (game->map[i] == 'E')
            {
                exit_count++;
                if (exit_count > 1)
                {
                    ft_putstr_fd("Error: Multiple exits found\n", 2);
                    game->collectibles = -1;
                    return;
                }
                game->exit_x = x;
                game->exit_y = y;
            }
            x++;
        }
        i++;
    }
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
