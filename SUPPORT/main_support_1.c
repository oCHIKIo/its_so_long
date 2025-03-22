/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_support_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 00:28:01 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/22 00:35:14 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void free_map_on_error(t_game *game)
{
    int i;

    i = 0;
    while (i < game->height)
    {
        free(game->map[i]);
        i++;
    }
    free(game->map);
}
void free_map(t_game *game)
{
    int x;

    x = 0;
    while (x < game->height)
    {
        free(game->map[x]);
        x++;
    }
    free(game->map);
}
int validate_arguments(int argc, char **argv)
{
    int fd;

    if (argc != 2)
    {
        ft_printf("\033[1;38;5;51mError: Usage: ./so_long <map>.ber\033[0m\n");
        return (0);
    }
    if (ft_strlen(argv[1]) < 4 || ft_strcmp(argv[1] + ft_strlen(argv[1]) - 4, ".ber") != 0)
    {
        ft_printf("\033[1;38;5;51mError: Map file must have a .ber extension\033[0m\n");
        return (0);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        ft_printf("\033[1;38;5;51mError: Map file does not exist or cannot be opened\033[0m\n");
        return (0);
    }
    close(fd);
    return (1);
}
int initialize_map(t_game *game, char *filename)
{
    if (!parse_and_validate_map(game, filename))
        return (0);
    if (!find_exit_position(game))
        return (0);
    return (1);
}
int parse_and_validate_map(t_game *game, char *filename)
{
    parse_map(game, filename);
    if (!validate_map(game))
    {
        free_map_on_error(game);
        return (0);
    }
    game->collectibles = count_collectibles(game);
    return (1);
}