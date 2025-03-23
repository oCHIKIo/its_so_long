/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_support.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:12:57 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/23 06:05:49 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int get_file_size(char *file)
{
    int fd;
    int size;
    char buf[1024];
    int bytes;

    fd = open(file, O_RDONLY);
    size = 0;
    if (fd < 0)
    {
        ft_putstr_fd("\033[1;31mError: Cannot open file\033[0m\n", 2);
        exit(1);
    }
    while ((bytes = read(fd, buf, 1024)) > 0)
        size += bytes;
    close(fd);
    return (size);
}

int check_start_line(t_game *game)
{
    if (game->map[0] == '\n')
    {
        ft_putstr_fd("\033[1;31mError: Empty line in map\033[0m\n", 2);
        return (0);
    }
    return (1);
}

int get_map_width(t_game *game)
{
    int i;

    i = 0;
    while (game->map[i] && game->map[i] != '\n')
        i++;
    game->width = i;
    return (1);
}

int check_line_length(t_game *game, int *i, int *all_walls)
{
    int line_length;
    int start;

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

int check_map_lines(t_game *game, int *all_walls)
{
    int i = 0;
    int height = 0;
    int len = ft_strlen(game->map);

    if (len > 0 && game->map[len - 1] == '\n')
    {
        ft_putstr_fd("\033[1;31mError: Empty line in map\033[0m\n", 2);
        return (0);
    }

    while (i < len)
    {
        if (!check_line_length(game, &i, all_walls))
            return (0);
        if (i < len && game->map[i] == '\n')
        {
            height++;
            i++;
            if (i < len && game->map[i] == '\n')
            {
                ft_putstr_fd("\033[1;31mError: Empty line in map\033[0m\n", 2);
                return (0);
            }
        }
    }
    // Add 1 to height to account for the last row (no trailing newline)
    game->height = height + 1;
    return (1);
}