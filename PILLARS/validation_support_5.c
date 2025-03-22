/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_support_5.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 02:26:32 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/22 02:28:59 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	can_reach_collectibles_and_exit(t_game *game)
{
	char	**visited;
	int		collectibles_reached;
	int		exit_reached;
	int		total_collectibles;

	collectibles_reached = 0;
	exit_reached = 0;
	total_collectibles = 0;
	visited = init_visited_array(game);
	if (!visited)
		return (0);
	count_total_collectibles(game, &total_collectibles);
	perform_flood_fill(game, visited, &collectibles_reached, &exit_reached);
	cleanup_visited_array(game, visited);
	return (validate_reachability(collectibles_reached, total_collectibles,
			exit_reached));
}

char	**init_visited_array(t_game *game)
{
	char	**visited;

	visited = malloc(sizeof(char *) * game->height);
	if (!visited)
	{
		ft_printf("\033[1;38;5;51mError: Memory allocation failed for visited array\033[0m\n");
		return (NULL);
	}
	allocate_visited_rows(game, visited, 0);
	return (visited);
}

void	count_total_collectibles(t_game *game, int *total_collectibles)
{
	count_collectibles_recursive(game, 0, 0, total_collectibles);
}

void	cleanup_visited_array(t_game *game, char **visited)
{
	free_visited_rows(game, visited, game->height - 1);
	free(visited);
}

int	validate_reachability(int collectibles_reached, int total_collectibles,
		int exit_reached)
{
	if (collectibles_reached != total_collectibles)
	{
		ft_printf("\033[1;38;5;51mError: Not all collectibles are reachable\033[0m\n");
		return (0);
	}
	if (exit_reached != 1)
	{
		ft_printf("\033[1;38;5;51mError: Exit is not reachable\033[0m\n");
		return (0);
	}
	return (1);
}
