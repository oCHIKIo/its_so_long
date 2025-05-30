/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:34:47 by bchiki            #+#    #+#             */
/*   Updated: 2024/11/11 20:04:11 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
	{
		return (NULL);
	}
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
/*#include <stdio.h>
int	main(void)
{
	t_list  *node = ft_lstnew("hiloo");

	if (node == NULL)
	{
		return (1);
	}
	printf("CONTENT: %s\n", (char *)node->content);
	if (node->next == NULL)
	{
		printf("(next is NULL).\n");
	}
	free(node);
}*/