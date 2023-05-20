/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:26:11 by kglebows          #+#    #+#             */
/*   Updated: 2023/05/20 19:20:47 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_buffer2line(char *line, t_buffer *buffer, int start)
{	
	int	i;

	i = 0;
	while (buffer->str[buffer->i] != '\0'
		&& buffer->str[buffer->i] != '\n')
	{
		line[i + start] = buffer->str[buffer->i];
		buffer->i++;
		i++;
	}
	if (buffer->str[buffer->i] == '\n')
	{
		line[i + start] = '\n';
	}
}

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

char	*ft_line_create(t_buffer *buffer, char *line)
{
	int		i;
	char	*join;

	join = NULL;
	if (buffer == NULL)
		return (NULL);
	i = buffer->i;
	while (buffer->str[i] != '\0' && buffer->str[i] != '\n')
		i++;
	if (buffer->str[i] == '\n')
		i++;
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

char	*ft_line(t_buffer *buffer, int fd)
{
	char	*line;

	line = NULL;
	while (buffer->read > 0)
	{
		line = ft_line_create(buffer, line);
		if (!line)
			return (NULL);
		if (buffer->str[buffer->i] == '\n')
		{
			buffer->i++;
			return (line);
		}
		if (buffer->str[buffer->i] == '\0')
			ft_buffer_refill(buffer, fd);
		if (buffer->read == -1)
		{
			free(line);
			line = NULL;
		}
	}
	return (line);
}

//