/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_support_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 01:05:55 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/22 01:10:36 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

char *read_and_process(t_nbr *nbr, char *buffer)
{
    buffer = read_in_chunks(nbr, buffer);
    if (buffer)
        close(nbr->fd);
    return (buffer);
}

char *read_file(char *filename)
{
    t_nbr nbr;
    char *buffer;

    buffer = open_and_allocate(filename, &nbr);
    if (!buffer)
        return (NULL);
    return (read_and_process(&nbr, buffer));
}

char *open_and_allocate(char *filename, t_nbr *nbr)
{
    char *buffer;

    nbr->fd = open(filename, O_RDONLY);
    if (nbr->fd < 0)
        return (NULL);
    buffer = malloc(1024);
    if (!buffer)
    {
        close(nbr->fd);
        return (NULL);
    }
    return (buffer);
}

void split_map_line(t_game *game, char *temp, int i, char *content)
{
    int len;

    len = 0;
    while (temp[len] && temp[len] != '\n')
        len++;
    game->map[i] = ft_strndup(temp, len);
    if (!game->map[i])
    {
        while (i > 0)
            free(game->map[--i]);
        free(game->map);
        free(content);
        ft_printf("\033[1;38;5;51mError: Memory allocation failed for map line\033[0m\n");
        exit(1);
    }
}
void split_map_content(t_game *game, char *content)
{
    char *temp;  
    int i;           

    temp = content;     
    i = 0;              

    while (i < game->height)
    {
        split_map_line(game, temp, i, content);
        while (*temp && *temp != '\n')
            temp++;
        if (*temp == '\n')
            temp++;
        i++;
    }
}
