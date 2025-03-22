/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:52:12 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/22 22:20:38 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int ft_strcmp_local(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int     main(int ac, char **av)
{
    t_game game = {0};
    
    if (ac != 2)
    {
        ft_putstr_fd("Error: Invalid number of arguments\n", 2);
        exit(1);
    }
    if (ft_strlen(av[1]) < 4 || ft_strcmp_local(av[1] + ft_strlen(av[1]) - 4, ".ber") != 0)
    {
        ft_putstr_fd("Error: Invalid file extension\n", 2);
        exit(1);
    }
    game.map = read_map(av[1]);
    if (!check_map_validity(&game))
    {
        free(game.map);
        exit(1);
    }
    ft_putstr_fd("Game Launched Successfully\n", 1);
    init_graphics(&game);
    render_map(&game);
    mlx_hook(game.win, 2, 1L<<0, key_press, &game);
    mlx_hook(game.win, 17, 0, close_window, &game); 
    mlx_loop(game.mlx);
    return (0);
}
