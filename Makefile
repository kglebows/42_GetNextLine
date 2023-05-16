# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/24 09:34:22 by pcazac            #+#    #+#              #
#    Updated: 2023/05/16 16:08:09 by kglebows         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = test

SRC = get_next_line.c get_next_line_utils.c test.c

#-fsanitize=address

$(NAME):
	gcc -g -Wall -Wextra -Werror -D BUFFER_SIZE=1 $(SRC)

all:
	clear && gcc -g -Wall -Wextra -Werror -D BUFFER_SIZE=1 $(SRC) && ./a.out

fclean:
	rm -f a.out

memory:
	clear && gcc -g -fsanitize=address -Wall -Wextra -Werror -D BUFFER_SIZE=5 $(SRC) && ./a.out