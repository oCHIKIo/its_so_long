/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_support_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 01:09:10 by bchiki            #+#    #+#             */
/*   Updated: 2025/03/22 03:05:48 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

char	*process_chunk(t_nbr *nbr, char *buffer, size_t *total_bytes,
		size_t *buffer_size)
{
	nbr->bytes = read(nbr->fd, buffer + *total_bytes, 1024);
	if (nbr->bytes < 0)
	{
		handle_error(buffer, nbr->fd);
		return (NULL);
	}
	*total_bytes += nbr->bytes;
	if (nbr->bytes == 1024)
	{
		*buffer_size += 1024;
		buffer = resize_buffer(buffer, *total_bytes, *buffer_size);
		if (!buffer)
		{
			close(nbr->fd);
			return (NULL);
		}
	}
	return (buffer);
}

void	check_trailing_newlines(char *content, size_t len)
{
	size_t	i;

	i = len;
	while (i > 0 && content[i - 1] == '\n')
		i--;
	if (i < len)
	{
		ft_printf("\033[1;38;5;51mError: Intruder line\033[0m\n");
		free(content);
		exit(1);
	}
}

void	check_consecutive_newlines(char *content, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len - 1)
	{
		if (content[i] == '\n' && content[i + 1] == '\n')
		{
			ft_printf("\033[1;38;5;51mError: Intruder line\033[0m\n");
			free(content);
			exit(1);
		}
		i++;
	}
}

void	check_trailing_empty_lines(char *content)
{
	size_t	len;

	len = 0;
	while (content[len] != '\0')
		len++;
	if (len == 0)
		return ;
	check_trailing_newlines(content, len);
	check_consecutive_newlines(content, len);
}
