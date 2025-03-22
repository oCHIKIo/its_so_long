/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_support_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 00:49:36 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/22 01:06:10 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void count_map_height(t_game *game, char *content)
{
    char *temp;

    temp = content;
    game->height = 0;

    while (*temp)
    {
        if (*temp == '\n')
            game->height++;
        temp++;
    }
    if (*(temp - 1) != '\n')
        game->height++;
}

void set_map_width(t_game *game)
{
    int width;         

    width = 0;         
    while (game->map[0][width])
        width++;
    game->width = width; 
}

char *resize_buffer(char *buffer, size_t total_bytes, size_t new_size)
{
    char *temp_buffer;
    
    temp_buffer = malloc(new_size);
    if (!temp_buffer)
        return (NULL);
    ft_memcpy(temp_buffer, buffer, total_bytes);
    free(buffer);
    return (temp_buffer);
}

void handle_error(char *buffer, int fd)
{
    free(buffer);
    close(fd);
}

char *read_in_chunks(t_nbr *nbr, char *buffer)
{
    size_t total_bytes = 0;
    size_t buffer_size = 1024;
    
    while (1)
    {
        nbr->bytes = read(nbr->fd, buffer + total_bytes, 1024);
        if (nbr->bytes < 0)
        {
            handle_error(buffer, nbr->fd);
            return (NULL);
        }
        total_bytes += nbr->bytes;
        if (nbr->bytes < 1024)
            break;
        buffer_size += 1024;
        buffer = resize_buffer(buffer, total_bytes, buffer_size);
        if (!buffer)
        {
            close(nbr->fd);
            return (NULL);
        }
    }
    buffer[total_bytes] = '\0';
    return (buffer);
}
