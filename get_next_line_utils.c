/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:26:11 by kglebows          #+#    #+#             */
/*   Updated: 2023/05/08 19:11:00 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_buffer	*ft_buffer_head(t_buffer **head, int fd)
{
	t_buffer	*buffer;

	buffer = *head;
	while (buffer != NULL)
	{
		if (buffer->fd == fd)
			return (buffer);
		buffer = buffer->next;
	}
	buffer = malloc(sizeof(t_buffer));
	if (!buffer)
		return (NULL);
	buffer->fd = fd;
	buffer->i = 0;
	buffer->cnt = 0;
	buffer->next = *head;
	*head = buffer;
	return (buffer);
}

void	ft_buffer_clean(t_buffer *buffer, t_buffer **head)
{
	t_buffer	*temp;

	if (!buffer || !head)
		return ;
	temp = *head;
	if (temp == buffer)
		head = temp->next;
	else
	{
		while (temp->next != buffer)
			temp = temp->next;
		temp->next = buffer->next;
	}
	free(buffer);
}
