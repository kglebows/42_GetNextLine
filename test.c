#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"


int	main(void)
{
	int		fd;
	char	*getln;
	int		i;
	char	c;

	c = 0;
	i = 0;
	fd = open("test.txt", O_RDONLY);
	getln = get_next_line(fd);
	printf("%s", getln);
	read(fd, &c, 1);
	printf("\n#%c#", c);
	// while (getln != NULL)
	// {
	// printf("%s", getln);
	// getln = get_next_line(fd);
	// }
	free(getln);
	return (0);
}