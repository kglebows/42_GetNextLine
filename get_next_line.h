/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:57:51 by kglebows          #+#    #+#             */
/*   Updated: 2023/05/20 19:29:02 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_buffer
{
	int				fd;
	char			str[BUFFER_SIZE + 1];
	ssize_t			i;
	ssize_t			read;
	struct s_buffer	*next;
}					t_buffer;

char		*get_next_line(int fd);
t_buffer	*ft_buffer_head(t_buffer **head, int fd);
void		ft_buffer_clean(t_buffer *buffer, t_buffer **head);
void		ft_buffer_refill(t_buffer *buffer, int fd);
char		*ft_line(t_buffer *buffer, int fd);

#endif