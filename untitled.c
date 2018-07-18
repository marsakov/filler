#include <stdio.h>
#include "libft/includes/libft.h"

# define GNL(fd, ln) get_next_line(fd, &line)

int main()
{
	char *line;
	int fd;

	fd = open("test", O_WRONLY | O_APPEND);
	while (GNL(0, &line) > 0)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		ft_putnbr(8);
		ft_putchar(' ');
		ft_putnbr(2);
		ft_putchar('\n');
	}
	return (0);
}