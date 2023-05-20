/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:01:01 by kglebows          #+#    #+#             */
/*   Updated: 2023/05/20 15:53:20 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>	
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>


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
	while (buffer->read > 0)
	{
		line = ft_line(buffer, line);
		if (!line)
			return (ft_buffer_clean(buffer, &head), NULL);
		if (buffer->buffer[buffer->i] == '\n')
		{
			buffer->i++;
			return (line);
		}
		if (buffer->buffer[buffer->i] == '\0')
			ft_buffer_refill(buffer, fd);
		if (buffer->read == -1)
		{
			free(line);
			line = NULL;
		}
	}
	ft_buffer_clean(buffer, &head);
	return (line);
}

void	ft_buffer_refill(t_buffer *buffer, int fd)
{
	while (buffer->read > 0)
	{
		buffer->read--;		
		buffer->buffer[buffer->read] = '\0';
	}
	buffer->i = 0;
	buffer->read = read(fd, buffer->buffer, BUFFER_SIZE);
	if (buffer->read > 0)
		buffer->buffer[buffer->read] = '\0';
}

// allowed functions : read, malloc, free

// • Repeated calls (e.g., using a loop) to your get_next_line() function 
//should let
// you read the text file pointed to by the file descriptor, one line at a time.

// • Your function should return the line that was read.
// If there is nothing else to read or if an error occurred, it should return 
//NULL.

// • Make sure that your function works as expected both when reading a file 
//and when
// reading from the standard input.

// • Please note that the returned line should include the terminating \n 
//character,
// except if the end of file was reached and does not end with a \n character.

// • Add all the helper functions you need in the get_next_line_utils.c file.

// • Because you will have to read files in get_next_line(), add this option to 
//your
// compiler call: -D BUFFER_SIZE=n
// It will define the buffer size for read().
// The buffer size value will be modified by your peer-evaluators and the 
//Moulinette
// in order to test your code.
// ()We must be able to compile this project with and without the -D
// BUFFER_SIZE flag in addition to the usual flags. You can choose the
// default value of your choice.
// • You will compile your code as follows (a buffer size of 42 is used as 
//an example):
// cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c

// We consider that get_next_line() has an undefined behavior if the 
//file pointed to
// by the file descriptor changed since the last call whereas read() 
//didn’t reach the
// end of file.

// • We also consider that get_next_line() has an undefined behavior 
//when reading
// a binary file. However, you can implement a logical way to handle
//this behavior if
// you want to

// Does your function still work if the BUFFER_SIZE value is 9999? If
// it is 1? 10000000? Do you know why?

// Try to read as little as possible each time get_next_line() is
// called. If you encounter a new line, you have to return the current
// line.
// Don’t read the whole file and then process each line.

// Forbidden
// • You are not allowed to use your libft in this project.
// • lseek() is forbidden.
// • Global variables are forbidden.

// BONUS :

// • Develop get_next_line() using only one static variable

// • Your get_next_line() can manage multiple file descriptors at
// the same time.
// For example, if you can read from the file descriptors 3, 4 and 5,
// you should be
// able to read from a different fd per call without losing the reading
// thread of each
// file descriptor or returning a line from another fd.
// It means that you should be able to call get_next_line() to read from
// fd 3, then
// fd 4, then 5, then once again 3, once again 4, and so forth.

// Append the _bonus.[c\h] suffix to the bonus part files.
// It means that, in addition to the mandatory part files, you will
// turn in the 3 following
// files:
// • get_next_line_bonus.c
// • get_next_line_bonus.h
// • get_next_line_utils_bonus.c