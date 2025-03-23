/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:52:24 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/23 00:50:32 by bchiki           ###   ########.fr       */
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

static int check_start_line(t_game *game)
{
    if (game->map[0] == '\n')
    {
        ft_putstr_fd("Error: Empty line at start\n", 2);
        return (0);
    }
    return (1);
}

static int get_map_width(t_game *game)
{
    int i = 0;
    while (game->map[i] && game->map[i] != '\n')
        i++;
    game->width = i;
    return (1);
}

static int check_line_length(t_game *game, int *i, int *all_walls)
{
    int line_length = 0;
    while (game->map[*i] && game->map[*i] != '\n')
    {
        if (game->map[*i] != '1')
            *all_walls = 0;
        line_length++;
        (*i)++;
    }
    if (line_length != game->width)
    {
        ft_putstr_fd("Error: Uneven map lines\n", 2);
        return (0);
    }
    return (1);
}

static int check_map_lines(t_game *game, int *all_walls)
{
    int i = 0;
    int height = 1;
    while (game->map[i])
    {
        if (!check_line_length(game, &i, all_walls))
            return (0);
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
    return (1);
}

static int check_final_validations(t_game *game)
{
    if (game->player_x == -1 || game->collectibles < 1)
    {
        if (game->player_x == -1)
            ft_putstr_fd("Error: No player found\n", 2);
        else if (game->collectibles < 1)
            ft_putstr_fd("Error: No collectibles found\n", 2);
        return (0);
    }
    return (check_accessibility(game));
}

static int check_end_conditions(t_game *game, int all_walls)
{
    if (game->map[game->height * (game->width + 1) - 2] == '\n')
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
    return (check_final_validations(game));
}

int check_map_validity(t_game *game)
{
    int all_walls = 1;
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

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

static void init_counts(t_game *game, t_count *count)
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

static int check_symbol(t_game *game, t_count *count)
{
    char c;
    c = game->map[count->i];
    if (c != '0' && c != '1' && c != 'P' && c != 'C' && c != 'E')
    {
        ft_printf("Error: Foreign symbol '%c' found\n", c);
        game->collectibles = -1;
        return (0);
    }
    if (c == 'C')
        game->collectibles++;
    return (1);
}

static int check_player_exit(t_game *game, t_count *count)
{
    char c = game->map[count->i];
    if (c == 'P')
    {
        count->player_count++;
        if (count->player_count > 1)
        {
            ft_putstr_fd("Error: Multiple players found\n", 2);
            game->collectibles = -1;
            return (0);
        }
        game->player_x = count->x;
        game->player_y = count->y;
    }
    else if (c == 'E')
    {
        count->exit_count++;
        if (count->exit_count > 1)
        {
            ft_putstr_fd("Error: Multiple exits found\n", 2);
            game->collectibles = -1;
            return (0);
        }
        game->exit_x = count->x;
        game->exit_y = count->y;
    }
    return (1);
}

void count_elements(t_game *game)
{
    t_count count;
    init_counts(game, &count);
    while (game->map[count.i])
    {
        if (game->map[count.i] == '\n')
        {
            count.x = 0;
            count.y++;
        }
        else
        {
            if (!check_symbol(game, &count) || !check_player_exit(game, &count))
                return;
            count.x++;
        }
        count.i++;
    }
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
