#include <stdio.h>
#include "libft/includes/libft.h"

# define GNL(fd, ln) get_next_line(fd, &line)

int main()
{
	char *line;
	int fd;

	fd = open("test", O_RDWR);
	while (GNL(0, &line) > 0)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (0);
}