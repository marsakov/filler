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

void	find_place(t_filler *ptr)
{
	int		i;
	int		j;
	char	c;

	c = (ptr->n == 2) ? 'x' : 'o';
	i = (ptr->n == 2) ? 0 : ptr->y - 1;
	while (ptr->map[i])
	{
		j = (ptr->n == 2) ? 0 : ptr->x - 1;
		while (ptr->map[i][j])
		{
			if (ptr->map[i][j] == c || ptr->map[i][j] == ft_toupper(c))
			{
				ptr->x_coord = i;
				ptr->y_coord = j;
				return ;
			}
			(ptr->n == 2) ? j++ : j--;
		}
		(ptr->n == 2) ? i++ : i--;
	}
}

void	find_star(t_filler *ptr)
{
	int i;
	int j;

	i = 0;
	while (ptr->piece[i])
	{
		j = 0;
		while (ptr->piece[i][j])
		{
			if (ptr->piece[i][j] == '*')
			{
				ptr->p_x = j;
				ptr->p_y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

int		fill_map(t_filler *ptr, int fd)
{
	int	i;
	int j;
	int counter;

	counter = (ptr->p_x + 1) * (ptr->p_y + 1);
	printf("ptr->p_x = %d | ptr->p_y = %d | counter = %d\n", ptr->p_x, ptr->p_y, counter);
	find_place(ptr);
	while (counter != ptr->piece_x * ptr->piece_y)
	{
		counter = (ptr->p_x + 1) * (ptr->p_y + 1);
		i = ptr->y_coord;
		while (i < ptr->y && i - ptr->y_coord + ptr->p_y < ptr->piece_y)
		{
			j = ptr->x_coord;
			while (j < ptr->x && j - ptr->x_coord + ptr->p_x < ptr->piece_x)
			{
				printf("map[%d][%d] = %c | piece[%d][%d] = %c\n", i, j, ptr->map[i][j], i - ptr->y_coord + ptr->p_y, j - ptr->x_coord + ptr->p_x, ptr->piece[i - ptr->y_coord + ptr->p_y][j - ptr->x_coord + ptr->p_x]);
				if (ptr->map[i][j] == '.')
					counter++;
				j++;
			}
			i++;
		}
		ft_putstr_fd("ptr->x_coord = ", fd);
		ft_putnbr_fd(ptr->x_coord, fd);
		ft_putstr_fd(" ptr->y_coord = ", fd);
		ft_putnbr_fd(ptr->y_coord, fd);
		ft_putstr_fd(" counter = ", fd);
		ft_putnbr_fd(counter, fd);
		ft_putchar_fd('\n', fd);
		if (counter != ptr->piece_x * ptr->piece_y)
		{
			if ((ptr->x_coord - 1 == ptr->x && ptr->n == 2) || (ptr->x_coord == 0 && ptr->n == 1))
			{
				ptr->x_coord = (ptr->n == 2) ? 0 : ptr->x - 1;
				(ptr->n == 2) ? ptr->y_coord++ : ptr->y_coord--;
			}
			else
				(ptr->n == 2) ? ptr->x_coord++ : ptr->x_coord--;
			ft_putendl_fd("TRY AGAIN WITH:", fd);
			ft_putstr_fd("ptr->x_coord = ", fd);
			ft_putnbr_fd(ptr->x_coord, fd);
			ft_putstr_fd(" ptr->y_coord = ", fd);
			ft_putnbr_fd(ptr->y_coord, fd);
			ft_putstr_fd(" counter = ", fd);
			ft_putnbr_fd(counter, fd);
			ft_putchar_fd('\n', fd);
		}
	}
	return (counter);
}

int		main()
{
	char		*line;
	t_filler	ptr;

	int fd = open("test", O_RDWR);
	// ft_putendl_fd("111start", fd);
	// ft_putendl_fd("first start", fd);

	while (get_next_line(0, &line) > 0 && ft_strstr(line, "msakovyc.filler]") == NULL)
		free(line);
	ptr.n = *(ft_strchr(line,'p') + 1) - '0';


	while (get_next_line(0, &line) > 0 && ft_strstr(line, "== O fin: ") == NULL)
	{
		int k = 0;
		if (ft_strstr(line, "<got"))
			while (k < ptr.y + ptr.piece_y + 3 && get_next_line(0, &line) > 0)
				free(line);
		while (ft_strstr(line, "Plateau ") == NULL)
		{
			free(line);
			get_next_line(0, &line);
		}
		ptr.y = ft_atoi(ft_strchr(line, ' '));
		ptr.x = ft_atoi(ft_strrchr(line, ' '));
		
		get_next_line(0, &line);
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
		ptr.piece_y = ft_atoi(ft_strchr(line, ' '));
		ptr.piece_x = ft_atoi(ft_strrchr(line, ' '));
		ptr.piece = writer(ptr.piece_x, ptr.piece_y, 1);
		find_star(&ptr);

		// find_place(&ptr);

		ft_putendl_fd("piece ok", fd);
		// printf("piece x = %d | y = %d\n", x, y);
		ft_putendl_fd("____WRITER____", fd);
		i = 0;
		while (i < ptr.piece_y)
			ft_putendl_fd(ptr.piece[i++], fd);
		ft_putendl_fd("______________", fd);

		fill_map(&ptr, fd);
		// printf("%d %d\n", ptr.x_coord, ptr.y_coord);

		ft_putnbr(ptr.x_coord);
		ft_putchar(' ');
		ft_putnbr(ptr.y_coord);
		ft_putchar('\n');
	}
	return (0);
}
