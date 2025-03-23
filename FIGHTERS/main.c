/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:52:12 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/23 05:57:32 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int	ft_strcmp_local(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

static int	check_file_extension(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strcmp_local(filename + len - 4, ".ber") != 0)
	{
		ft_putstr_fd("\033[1;31mError: Invalid file extension (must be .ber)\033[0m\n",
			2);
		return (0);
	}
	return (1);
}

int main(int ac, char **av)
{
    t_game game = {0, 0, {0}, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 
    if (ac != 2)
    {
        ft_putstr_fd("\033[1;31mError: Invalid number of arguments\033[0m\n", 2);
        exit(1);
    }
    if (!check_file_extension(av[1]))
        exit(1);
    game.map = read_map(av[1]);
    if (!check_map_validity(&game))
    {
        free(game.map);
        exit(1);
    }
    ft_putstr_fd("\033[1;36mGame Launched Successfully\033[0m\n", 1);
    init_graphics(&game);
    render_map(&game);
    mlx_hook(game.win, 2, 1L<<0, key_press, &game);
    mlx_loop(game.mlx);
    return (0);
}
