/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 13:40:43 by msakovyc          #+#    #+#             */
/*   Updated: 2018/06/17 13:40:46 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

char	**writer(int x, int y, int piece)
{
	char	**map;
	char	*line;
	int		i;

	i = 0;
	map = malloc(sizeof(char*) * y);
	while (i < y && get_next_line(0, &line) > 0)
	{
		map[i] = malloc(sizeof(char) * (x + 1));
		if (piece)
			ft_strcpy(map[i++], line);
		else
			ft_strcpy(map[i++], line + 4);
		free(line);
	}
	return (map);
}

int		find_place(t_filler *ptr, char c)
{
	int i;
	int j;

	i = (c == 'x') ? 0 : ptr->y - 1;
	while (ptr->map[i])
	{
		j = (c == 'x') ? 0 : ptr->x - 1;
		while (ptr->map[i][j])
		{
			if (ptr->map[i][j] == c || ptr->map[i][j] == ft_toupper(c))
			{
				// printf("found: x = %d, y = %d\n", j, i);
				ptr->x_coord = j;
				ptr->y_coord = i;
				return (0);
			}
			(c == 'x') ? j++ : j--;
		}
		(c == 'x') ? i++ : i--;
	}
	// printf("didn't find anything\n");
	return (0);
}

char	**fill_map(t_filler *ptr)
{
	int	i;

	i = 0;
	find_place(ptr, (ptr->n == 1) ? 'o' : 'x');
	// while (ptr.map[i])
	// {
	// 	if (ptr.map[])
	// }
	return (ptr->map);
}

int		main()
{
	int			x;
	int			y;
	char		*line;
	t_filler	ptr;

	int fd = open("test", O_RDWR);
	ft_putendl_fd("hello", fd);
	while (get_next_line(0, &line) > 0 && ft_strstr(line, "msakovyc.filler]") == NULL)
		free(line);
	ptr.n = *(ft_strchr(line,'p') + 1) - '0';
	while (get_next_line(0, &line) > 0 && ft_strstr(line, "Plateau ") == NULL)
		free(line);
	ptr.y = ft_atoi(ft_strchr(line, ' '));
	ptr.x = ft_atoi(ft_strrchr(line, ' '));
	while (get_next_line(0, &line) > 0)
	{
		free(line);
		ptr.map = writer(ptr.x, ptr.y, 0);
		ft_putendl_fd("map ok", fd);
	
		//printf("n = %d | x = %d | y = %d\n", ptr.n, ptr.x, ptr.y);
		ft_putendl_fd("____WRITER____", fd);
		int i = 0;
		while (i < ptr.y)
			ft_putendl_fd(ptr.map[i++], fd);
		ft_putendl_fd("______________", fd);

		while (get_next_line(0, &line) > 0 && ft_strstr(line, "Piece ") == NULL)
			free(line);
		y = ft_atoi(ft_strchr(line, ' '));
		x = ft_atoi(ft_strrchr(line, ' '));
		ptr.piece = writer(x, y, 1);

		ft_putendl_fd("piece ok", fd);
		// printf("piece x = %d | y = %d\n", x, y);
		ft_putendl_fd("____WRITER____", fd);
		i = 0;
		while (i < y)
			ft_putendl_fd(ptr.piece[i++], fd);
		ft_putendl_fd("______________", fd);

		fill_map(&ptr);
		// printf("%d %d\n", ptr.x_coord, ptr.y_coord);
		ft_putnbr(ptr.x_coord);
		ft_putchar(' ');
		ft_putnbr(ptr.y_coord);
		ft_putchar('\n');
	}
	return (0);
}
