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

int fd = open("test", O_WRONLY | O_APPEND);
	i = 0;
	map = malloc(sizeof(char*) * y);
	while (i < y && GNL(0, &line) > 0)
	{
		map[i] = malloc(sizeof(char) * (x + 1));
		if (piece)
			ft_strcpy(map[i++], line);
		else
			ft_strcpy(map[i++], line + 4);
		/////////////////////
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		////////////////////
		free(line);
	}
	return (map);
}

int		find_place(t_data *ptr, int n, char c)
{
	int		i;
	int		j;

	i = ptr->t_y;
	while (ptr->arr[i])
	{
		j = ptr->t_x;
		while (ptr->arr[i][j])
		{
			if (ptr->arr[i][j] == c || ptr->arr[i][j] == ft_tolower(c))
			{
				ptr->t_x = j;
				ptr->t_y = i;
				return (0);
			}
			(n == 2) ? j++ : j--;
		}
		j = (n == 2) ? 0 : ptr->x - 1;
		(n == 2) ? i++ : i--;
	}
	return (0);
}

int		fill_map(t_filler *ptr)
{
	int	i;
	int	j;
	int x_p;
	int x_m;

	i = 0;
	x_m = ptr->map->t_x;
	x_p = ptr->piece->t_x;
	while (ptr->map->t_y + i < ptr->map->y && ptr->piece->t_y + i < ptr->piece->y)
	{
		j = 0;
		while (x_m + j < ptr->map->x && x_p + i < ptr->piece->x)
		{
			if (ptr->map->arr[ptr->map->t_y + i][x_m + j] != '.')
				if (ptr->piece->arr[ptr->piece->t_y + i][x_p + j] != '.')
					if (!(i == 0 && j == 0))
						return (0);
			j++;
		}
		if (i == 0 && x_p + j == ptr->piece->x)
		{
			x_m -= x_p;
			x_p = 0;
		}
		i++;
	}
	// printf("fill ok\n");
	return (1);
}

int		main(void)
{
	char		*line;
	t_filler	ptr;

	int fd = open("test", O_WRONLY | O_APPEND);

    ptr.map = (t_data*)malloc(sizeof(t_data));
    ptr.piece = (t_data*)malloc(sizeof(t_data));

    GNL(0, &line);
	ptr.n = *(ft_strchr(line,'p') + 1) - '0';
	free(line);
	while (GNL(0, &line) > 0)
	{
		///////////////
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		///////////////
		ptr.map->y = ft_atoi(ft_strchr(line, ' '));
		ptr.map->x = ft_atoi(ft_strrchr(line, ' '));
		free(line);
		GNL(0, &line);
		////////////////
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		////////////////
		free(line);
		ptr.map->arr = writer(ptr.map->x, ptr.map->y, 0);

		GNL(0, &line);
		///////////////
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		//////////////
		ptr.piece->y = ft_atoi(ft_strchr(line, ' '));
		ptr.piece->x = ft_atoi(ft_strrchr(line, ' '));
		ptr.piece->arr = writer(ptr.piece->x, ptr.piece->y, 1);

		ptr.map->t_y = (ptr.n == 2) ? 0 : ptr.map->y - 1;
		ptr.map->t_x = (ptr.n == 2) ? 0 : ptr.map->x - 1;
		ptr.piece->t_y = 0;
		ptr.piece->t_x = 0;
		find_place(ptr.map, ptr.n, ptr.n == 2 ? 'X' : 'O');
		find_place(ptr.piece, 2, '*');
		// printf("map place : x = %d | y = %d\n", ptr.map->t_x, ptr.map->t_y);
		while (!fill_map(&ptr))
		{
			if (ptr.n == 1 && ptr.map->t_x == ptr.map->x - 1)
			{
				ptr.map->t_x = 0;
				ptr.map->t_y--;
				if (ptr.map->t_y == ptr.map->y)
				{
					printf("if1\n");
					return (0);
				}
			}
			else if (ptr.n == 1)
				ptr.map->t_x--;
			else if (ptr.n == 2 && ptr.map->t_x == 0)
			{
				ptr.map->t_x = ptr.map->x - 1;
				ptr.map->t_y++;
				if (ptr.map->t_y < 0)
				{
					printf("if2\n");
					return (0);
				}
			}
			else if (ptr.n == 2)
				ptr.map->t_x++;
			if (!find_place(ptr.map, ptr.n, ptr.n == 2 ? 'X' : 'O'))
			{
				printf("if3\n");
				return (0);
			}
		}
		ft_putnbr(ptr.map->t_y - ptr.piece->t_y);
		ft_putchar(' ');
		ft_putnbr(ptr.map->t_x - ptr.piece->t_x);
		ft_putchar('\n');

		ft_putnbr_fd(ptr.map->t_y - ptr.piece->t_y, fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd(ptr.map->t_x - ptr.piece->t_x, fd);
		ft_putchar_fd('\n', fd);
	}
	return (0);
}
