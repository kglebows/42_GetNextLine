/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:26:11 by kglebows          #+#    #+#             */
/*   Updated: 2023/05/10 19:54:49 by kglebows         ###   ########.fr       */
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
	buffer->buffer[BUFFER_SIZE] = '\0';
	buffer->fd = fd;
	buffer->i = 0; // jaka rola ?
	buffer->cnt = 0; // jaka rola ?
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
		head = &temp->next;
	else
	{
		while (temp->next != buffer)
			temp = temp->next;
		temp->next = buffer->next;
	}
	free(buffer);
}

char	*ft_line(t_buffer *buffer, char *line)
{
	int		i;
	int		j;
	char	*join;

	join = NULL;
	i = buffer->i;
	j = 0;
	while (buffer->buffer[i] != '\0' && buffer->buffer[i] != '\n')
		i++;
	if (!line)
	{
		line = malloc((sizeof(char) * i) + 1);
		if (!line)
			return (NULL);
		line[i] = '\0';
		return (line);
	}
	join = ft_line_join(line, i);
	free(line);
	return (join);
}

char	*ft_line_join(char *line, int i)
{
	char	*join;
	int		j;

	j = 0;
	while (line[j] != '\0') // przemyslec i oraz cnt oraz czy tego nie uzyc
		j++;
	join = malloc((sizeof(char) * (i + j)) + 1);
	if (!join)
		return (NULL);
	join[i + j] = '\0';
	while (i-- >= 0)
		join[i] = line[i];
	return (join);
}
