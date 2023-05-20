/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:01:01 by kglebows          #+#    #+#             */
/*   Updated: 2023/05/20 19:28:13 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_buffer	*head = NULL;
	t_buffer		*buffer;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	line = NULL;
	buffer = ft_buffer_head(&head, fd);
	if (!buffer || buffer->read == -1 || buffer->read == 0)
		return (ft_buffer_clean(buffer, &head), NULL);
	line = ft_line(buffer, fd);
	if (!line)
		return (ft_buffer_clean(buffer, &head), NULL);
	return (line);
}

t_buffer	*ft_buffer_head(t_buffer **head, int fd)
{
	t_buffer	*buffer;

	buffer = *head;
	while (buffer != NULL)
	{
		if (buffer->fd == fd)
		{
			if (buffer->i >= buffer->read)
				ft_buffer_refill(buffer, fd);
			return (buffer);
		}
		buffer = buffer->next;
	}
	buffer = malloc(sizeof(t_buffer));
	if (!buffer)
		return (NULL);
	buffer->fd = fd;
	buffer->i = 0;
	buffer->read = read(fd, buffer->str, BUFFER_SIZE);
	if (buffer->read > 0)
		buffer->str[buffer->read] = '\0';
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
		*head = temp->next;
	else
	{
		while (temp->next != buffer)
			temp = temp->next;
		temp->next = buffer->next;
	}
	if (buffer->read == -1)
		head = NULL;
	free(buffer);
	buffer = NULL;
}

void	ft_buffer_refill(t_buffer *buffer, int fd)
{
	while (buffer->read > 0)
	{
		buffer->read--;
		buffer->str[buffer->read] = '\0';
	}
	buffer->i = 0;
	buffer->read = read(fd, buffer->str, BUFFER_SIZE);
	if (buffer->read > 0)
		buffer->str[buffer->read] = '\0';
}
//