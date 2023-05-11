/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:57:51 by kglebows          #+#    #+#             */
/*   Updated: 2023/05/11 21:29:09 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_buffer
{
	int				fd;
	char			buffer[BUFFER_SIZE + 1];
	ssize_t			i;
	ssize_t			cnt;
	struct s_buffer	*next;
}					t_buffer;

char		*get_next_line(int fd);
t_buffer	*ft_buffer_head(t_buffer **head, int fd);
void		ft_buffer_clean(t_buffer *buffer, t_buffer **head);
char		*ft_line(t_buffer *buffer, char *line, ssize_t ret);
char		*ft_line_join(char *line, int i, ssize_t cnt);

#endif