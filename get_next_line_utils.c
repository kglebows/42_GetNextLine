/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:26:11 by kglebows          #+#    #+#             */
/*   Updated: 2023/05/11 20:04:24 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_buffer	*ft_buffer_head(t_buffer **head, int fd)
{
	t_buffer	*buffer;

	buffer = *head;
	if (!fd)
		return (NULL);
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
	if (*head == NULL)
		buffer->next = NULL;
	else
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
	while (buffer->i > 0)
	{
		buffer->buffer[buffer->i] = 0;
		buffer->i--;
	}
	free(buffer);
}

char	*ft_line(t_buffer *buffer, char *line, ssize_t ret)
{
	int		i;
	char	*join;

	join = NULL;
	i = buffer->i;
	while (i <= ret && buffer->buffer[i] != '\n')
		i++;
	if (buffer->buffer[i] == '\n')
		i++;
	if (!line)
	{
		line = malloc((sizeof(char) * i) + 1); // error tu 
		line[i] = '\0';
		if (!line)
			return (NULL);
		return (line);
	}
	join = ft_line_join(line, i, buffer->cnt);
	free(line);
	return (join);
}

char	*ft_line_join(char *line, int i, ssize_t cnt)
{
	char	*join;

	join = malloc((sizeof(char) * (i + cnt)) + 1);
	join[i + cnt] = '\0';
	if (!join)
		return (NULL);
	while (i >= 0)
	{
		join[i] = line[i];
		i--;
	}
	return (join);
}
