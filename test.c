#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"


int	main(void)
{
	int		fd;
	char	*getln;
	int		i;

	i = 0;
	fd = open("test.txt", O_RDONLY);
	getln = get_next_line(fd);
	while (getln != NULL)
	{
	printf("%s", getln);
	getln = get_next_line(fd);
	}
	free(getln);
	return (0);
}