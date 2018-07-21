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

	// int fd = open("test", O_WRONLY | O_APPEND);
	i = 0;
	map = malloc(sizeof(char*) * y);
	while (i < y && GNL(0, &line) > 0)
	{
		map[i] = malloc(sizeof(char) * (x + 1));
		if (piece)
			ft_strcpy(map[i++], line);
		else
			ft_strcpy(map[i++], line + 4);
		// /////////////////////
		// write(fd, line, ft_strlen(line));
		// write(fd, "\n", 1);
		// ////////////////////
		free(line);
	}
	return (map);
}

void	count_stars(t_filler *ptr)
{
	int		i;
	int		j;
	int		counter;

	counter = 0;
	i = 0;
	while (i < ptr->piece->y)
	{
		j = 0;
		while (j < ptr->piece->x)
		{
			if (ptr->piece->arr[i][j] == '*')
				counter++;
			j++;
		}
		i++;
	}
	ptr->stars = counter;
}

int		find_place(t_data *ptr, int n, char c)
{
	int		i;
	int		j;

	i = ptr->t_y;
	j = ptr->t_x;
	while (i < ptr->y && i >= 0)
	{
		while (j < ptr->x && j >= 0)
		{
			if (ptr->arr[i][j] == c)
			{
				ptr->t_x = j;
				ptr->t_y = i;
				return (1);
			}
			(n == 2 || n == 3) ? j++ : j--;
		}
		j = (n == 2 || n == 3) ? 0 : ptr->x - 1;
		(n == 2 || n == 4) ? i++ : i--;
	}
	return (0);
}

int		fill_map(t_filler *p, int i, int counter, int n)
{
	int	j;
	int x_p;
	int x_m;

	x_m = p->map->t_x;
	x_p = p->piece->t_x;
	while (p->map->t_y + i >= 0 && p->map->t_y + i < p->map->y && p->piece->t_y + i >= 0 && p->piece->t_y + i < p->piece->y)
	{
		j = 0;
		while (x_m + j >= 0 && x_m + j < p->map->x && x_p + j >= 0 && x_p + j < p->piece->x)
		{
			if (p->map->arr[p->map->t_y + i][x_m + j] != '.' &&
	p->piece->arr[p->piece->t_y + i][x_p + j] != '.' && !(i == 0 && j == 0))
				 return (0);
			else if (p->piece->arr[p->piece->t_y + i][x_p + j] == '*')
				counter++; 
			(n == 1 || n == 4) ? j++ : j--;
		}
		if (i == 0 && (((n == 1 || n == 4) && x_p + j == p->piece->x) || ((n == 2 || n == 3) && x_p + j == -1)))
		{
			x_m = (n == 1 || n == 4) ? x_m - x_p : x_m + (p->piece->x - 1 - x_p);
			x_p = (n == 1 || n == 4) ? 0 : p->piece->x - 1;
		}
		(n == 1 || n == 3) ? i++ : i--;
	}
	return (counter == p->stars) ? (1) : (0);
}

void	loop_writer(char *line, t_filler *ptr)
{
	// int fd = open("test", O_WRONLY | O_APPEND);
	// ///////////////
	// write(fd, line, ft_strlen(line));
	// write(fd, "\n", 1);
	// ///////////////
	ptr->map->y = ft_atoi(ft_strchr(line, ' '));
	ptr->map->x = ft_atoi(ft_strrchr(line, ' '));
	free(line);
	GNL(0, &line);
	// ////////////////
	// write(fd, line, ft_strlen(line));
	// write(fd, "\n", 1);
	// ////////////////
	free(line);
	ptr->map->arr = writer(ptr->map->x, ptr->map->y, 0);

	GNL(0, &line);
	// ///////////////
	// write(fd, line, ft_strlen(line));
	// write(fd, "\n", 1);
	// //////////////
	ptr->piece->y = ft_atoi(ft_strchr(line, ' '));
	ptr->piece->x = ft_atoi(ft_strrchr(line, ' '));
	ptr->piece->arr = writer(ptr->piece->x, ptr->piece->y, 1);
	count_stars(ptr);
	ptr->map->t_y = (ptr->n == 2) ? 0 : ptr->map->y - 1;
	ptr->map->t_x = (ptr->n == 2) ? 0 : ptr->map->x - 1;
	ptr->piece->t_y = (ptr->n == 1) ? 0 : ptr->piece->y - 1;
	ptr->piece->t_x = (ptr->n == 1) ? 0 : ptr->piece->x - 1;
	find_place(ptr->map, ptr->n, ptr->n == 2 ? 'X' : 'O');
	find_place(ptr->piece, ptr->n == 2 ? 1 : 2, '*');
}

int     change_coord(t_filler *ptr)
{
	if (ptr->n == 1 && ptr->map->t_x == ptr->map->x - 1)
	{
		ptr->map->t_x = 0;
		ptr->map->t_y--;
		if (ptr->map->t_y == ptr->map->y)
			return (0);
	}
	else if (ptr->n == 1)
		ptr->map->t_x--;
	else if (ptr->n == 2 && ptr->map->t_x == 0)
	{
		ptr->map->t_x = ptr->map->x - 1;
		ptr->map->t_y++;
		if (ptr->map->t_y < 0)
			return (0);
	}
	else if (ptr->n == 2)
		ptr->map->t_x++;
	return (1);
}

void	print_coord(t_filler ptr, int n)
{
	printf("-----------  try  %d ----------\n", n);
	printf("map->t_x = %d\n", ptr.map->t_x);
	printf("map->t_y = %d\n", ptr.map->t_y);
	printf("piece->t_x = %d\n", ptr.piece->t_x);
	printf("piece->t_y = %d\n", ptr.piece->t_y);
	printf("-------------------------------\n");
}

int		main(void)
{
	char		*line;
	t_filler	ptr;

	// int fd = open("test", O_WRONLY | O_APPEND);

	ptr.map = (t_data*)malloc(sizeof(t_data));
	ptr.piece = (t_data*)malloc(sizeof(t_data));

	GNL(0, &line);
	ptr.n = *(ft_strchr(line,'p') + 1) - '0';
	free(line);
	while (GNL(0, &line) > 0)
	{
		loop_writer(line, &ptr);
		print_coord(ptr, ptr.n);
		while (!fill_map(&ptr, 0, 0, ptr.n))
		{
			print_coord(ptr, 3);
				// N = 3
			ptr.piece->t_y = ptr.piece->y - 1;
			ptr.piece->t_x = 0;
			find_place(ptr.piece, 3, '*');
			if (fill_map(&ptr, 0, 0, 4))
				break;
				// N = 4
			print_coord(ptr, 4);
			ptr.piece->t_y = ptr.piece->y - 1;
			ptr.piece->t_x = 0;
			find_place(ptr.piece, 4, '*');
			if (fill_map(&ptr, 0, 0, 3))
				break;

			print_coord(ptr, ptr.n == 2 ? 1 : 2);
			ptr.piece->t_y = (ptr.n == 2) ? 0 : ptr.piece->y - 1;
			ptr.piece->t_x = (ptr.n == 2) ? 0 : ptr.piece->y - 1;
			find_place(ptr.piece, ptr.n, '*');
			if (!fill_map(&ptr, 0, 0, ptr.n == 2 ? 1 : 2))
			{
				ptr.piece->t_y = (ptr.n == 1) ? 0 : ptr.piece->y - 1;
				ptr.piece->t_x = (ptr.n == 1) ? 0 : ptr.piece->y - 1;
				find_place(ptr.piece, ptr.n == 2 ? 1 : 2, '*');
				if (!change_coord(&ptr))
					return (0);
				find_place(ptr.map, ptr.n, ptr.n == 2 ? 'X' : 'O');
			}
			else
				break ;
		}
		ft_putnbr(ptr.map->t_y - ptr.piece->t_y);
		ft_putchar(' ');
		ft_putnbr(ptr.map->t_x - ptr.piece->t_x);
		ft_putchar('\n');

		// ft_putnbr_fd(ptr.map->t_y - ptr.piece->t_y, fd);
		// ft_putchar_fd(' ', fd);
		// ft_putnbr_fd(ptr.map->t_x - ptr.piece->t_x, fd);
		// ft_putchar_fd('\n', fd);
	}
	return (0);
}
