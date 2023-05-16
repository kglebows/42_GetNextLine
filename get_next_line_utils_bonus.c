/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:26:11 by kglebows          #+#    #+#             */
/*   Updated: 2023/05/16 18:49:02 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	buffer->read = read(fd, buffer->buffer, BUFFER_SIZE);
	if (buffer->read > 0)
		buffer->buffer[buffer->read] = '\0';
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

char	*ft_line(t_buffer *buffer, char *line)
{
	int		i;
	char	*join;
	int		j;

	join = NULL;
	if (buffer == NULL)
		return (NULL);
	i = buffer->i; //TU KURWA!
	j = 0;
	while (buffer->buffer[i] != '\0' && buffer->buffer[i] != '\n')
	{
		i++;
		j++;
	}
	if (buffer->buffer[i] == '\n')
	{
		i++;
		j++;
	}
	if (!line && i > 0)
	{	
		line = malloc((sizeof(char) * (i - buffer->i + 1)));
		if (!line)
			return (NULL);
		line[i - buffer->i] = '\0';
		ft_buffer2line(line, buffer, 0);
		return (line);
	}
	join = ft_line_join(line, i - buffer->i, buffer);
	free(line);
	if (!join)
		return (NULL);
	return (join);
}

void	ft_buffer2line(char *line, t_buffer *buffer, int start)
{	
	int	i;

	i = 0;
	while (buffer->buffer[buffer->i] != '\0' &&
	buffer->buffer[buffer->i] != '\n')
	{
		line[i + start] = buffer->buffer[buffer->i];
		buffer->i++;
		i++;
	}
	if (buffer->buffer[buffer->i] == '\n')
		line[i + start] = '\n';
}

// void	ft_buffer2line(char *line, t_buffer *buffer, int start)
// {	
// 	int	i;

// 	i = 0;
// 	while (buffer->buffer[buffer->i] != '\0' &&
// 	buffer->buffer[buffer->i] != '\n')
// 	{
// 		line[buffer->i + start] = buffer->buffer[buffer->i];
// 		buffer->i++;
// 	}
// 	if (buffer->buffer[buffer->i] == '\n')
// 	{
// 		line[buffer->i + start] = '\n';
// 	}

// }

char	*ft_line_join(char *line, int i, t_buffer *buffer)
{
	char	*join;
	int		line_len;

	if (i == 0)
		return (NULL);
	line_len = 0;
	while (line[line_len] != '\0')
		line_len++;
	join = malloc((sizeof(char) * (i + line_len + 1)));
	if (!join)
		return (NULL);
	join[i + line_len] = '\0';
	ft_buffer2line(join, buffer, line_len);
	while (line_len > 0)
	{
		line_len--;
		join[line_len] = line[line_len];
	}
	return (join);
}