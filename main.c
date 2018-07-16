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

void	find_place(t_data *ptr, int n, char c)
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
				return ;
			}
			(n == 2) ? j++ : j--;
		}
		j = (n == 2) ? 0 : ptr->x - 1;
		(n == 2) ? i++ : i--;
	}
}

int		fill_map(t_filler *p)
{
    int m = 0;
    int i = 0;

    p->map->t_x = (p->n == 2) ? p->map->t_x - p->piece->t_x : p->map->t_x + p->piece->t_x;
    p->map->t_y = (p->n == 2) ? p->map->t_y - p->piece->t_y : p->map->t_y + p->piece->t_y;
    p->x_result = p->map->t_x;
    p->y_result = p->map->t_y;
	while (p->map->t_y + i >= 0 && p->map->t_y + i < p->map->y && p->piece->t_y + i >= 0 && p->piece->t_y + i < p->piece->y)
	{
        int j = 0;
		while (p->map->t_x + j >= 0 && p->map->t_x + j < p->map->x && p->piece->t_x + j >= 0 && p->piece->t_x + j < p->piece->x)
		{
			if (p->map->arr[p->map->t_y + i][p->map->t_x + j] != '.')
				if (p->piece->arr[p->piece->t_y + i][p->piece->t_x + j] != '.')
                {
                    // printf("ERROR x = %d    y = %d",p->map->t_x + j, p->map->t_y + i);
                    m++;
                }
			(p->n == 2) ? j++ : j--;
        }
        if (j == 1 || j == -1)
        {
            p->map->t_x = (p->n == 2) ? p->map->t_x + p->piece->t_x : p->map->t_x - p->piece->t_x;
            p->piece->t_x = (p->n == 2) ? 0 : p->piece->x - 1;
        }
		(p->n == 2) ? i++ : i--;
	}
    if (m != 1)
        return (0);
    if (p->n == 1)
    {
        p->x_result -= p->piece->x - 1;
        p->y_result -= p->piece->y - 1;
    }
    return (1);
}

// int		fill_map(t_filler *p)
// {
//     p->map->t_x = (p->n == 2) ? p->map->t_x - p->piece->t_x : p->map->t_x + p->piece->t_x;
//     p->map->t_y = (p->n == 2) ? p->map->t_y - p->piece->t_y : p->map->t_y + p->piece->t_y;
//     p->x_result = p->map->t_x;
//     p->y_result = p->map->t_y;
// 	while (p->map->t_y >= 0 && p->map->t_y < p->map->y && p->piece->t_y >= 0 && p->piece->t_y < p->piece->y)
// 	{
// 		while (p->map->t_x >= 0 && p->map->t_x < p->map->x && p->piece->t_x >= 0 && p->piece->t_x < p->piece->x)
// 		{
// 			if (p->map->arr[p->map->t_y][p->map->t_x] != '.')
// 				if (p->piece->arr[p->piece->t_y][p->piece->t_x] != '.')
// 					return (0);
// 			(p->n == 2) ? p->map->t_x++ : p->map->t_x--;
// 			(p->n == 2) ? p->piece->t_x++ : p->piece->t_x--;
// 		}
//         if (p->map->t_x < 0 || p->piece->t_x < 0 || p->map->t_x == p->map->x || p->piece->t_x == p->piece->x)
//         {

//         }
// 		(p->n == 2) ? p->map->t_y++ : p->map->t_y--;
// 		(p->n == 2) ? p->piece->t_y++ : p->piece->t_y--;
// 	}
// 	return (1);
// }

int		main()
{
	char		*line;
	t_filler	ptr;

	// int fd = open("test", O_RDWR);
	// ft_putendl_fd("111start", fd);
	// ft_putendl_fd("first start", fd); 


    ptr.map = (t_data*)malloc(sizeof(t_data));
    ptr.piece = (t_data*)malloc(sizeof(t_data));
	while (get_next_line(0, &line) > 0 && ft_strstr(line, "msakovyc.filler]") == NULL)
		free(line);
	ptr.n = *(ft_strchr(line,'p') + 1) - '0';


	while (get_next_line(0, &line) > 0 && ft_strstr(line, "== O fin: ") == NULL)
	{
		int k = 0;
		if (ft_strstr(line, "<got"))
			while (k < ptr.map->y + ptr.piece->y + 3 && get_next_line(0, &line) > 0)
				free(line);
		while (ft_strstr(line, "Plateau ") == NULL)
		{
			free(line);
			get_next_line(0, &line);
		}
		ptr.map->y = ft_atoi(ft_strchr(line, ' '));
		ptr.map->x = ft_atoi(ft_strrchr(line, ' '));
		
		get_next_line(0, &line);
		free(line);
		ptr.map->arr = writer(ptr.map->x, ptr.map->y, 0);

		// ft_putendl_fd("map ok", fd);
		// //printf("n = %d | x = %d | y = %d\n", ptr.n, ptr.x, ptr.y);
		// ft_putendl_fd("____WRITER____", fd);
		// int i = 0;
		// while (i < ptr.y)
		// 	ft_putendl_fd(ptr.map[i++], fd);
		// ft_putendl_fd("______________", fd);

		while (get_next_line(0, &line) > 0 && ft_strstr(line, "Piece ") == NULL)
			free(line);
		ptr.piece->y = ft_atoi(ft_strchr(line, ' '));
		ptr.piece->x = ft_atoi(ft_strrchr(line, ' '));
		ptr.piece->arr = writer(ptr.piece->x, ptr.piece->y, 1);

		// ft_putendl_fd("piece ok", fd);
		// // printf("piece x = %d | y = %d\n", x, y);
		// ft_putendl_fd("____WRITER____", fd);
		// i = 0;
		// while (i < ptr.piece_y)
		// 	ft_putendl_fd(ptr.piece[i++], fd);
		// ft_putendl_fd("______________", fd);

		ptr.map->t_y = (ptr.n == 2) ? 0 : ptr.map->y - 1;
		ptr.map->t_x = (ptr.n == 2) ? 0 : ptr.map->x - 1;
		ptr.piece->t_y = (ptr.n == 2) ? 0 : ptr.piece->y - 1;
		ptr.piece->t_x = (ptr.n == 2) ? 0 : ptr.piece->x - 1;
		find_place(ptr.map, ptr.n, ptr.n == 2 ? 'X' : 'O');
		find_place(ptr.piece, ptr.n, '*');

		// printf("place in map : x = %d | y = %d\n", ptr.map->t_x, ptr.map->t_y);
		// printf("place in piece : x = %d | y = %d\n", ptr.piece->t_x, ptr.piece->t_y);

		// find_place(ptr.map, ptr.n, ptr.n == 2 ? 'X' : 'O');
		// find_place(ptr.piece, ptr.n, '*');
		// printf("place in map : x = %d | y = %d\n", ptr.map->t_x, ptr.map->t_y);
		// printf("place in piece : x = %d | y = %d\n", ptr.piece->t_x, ptr.piece->t_y);

		while (!fill_map(&ptr))
		{
			if (ptr.n == 1 && ptr.piece->t_x == ptr.piece->x - 1)
			{
				ptr.map->t_x -= ptr.piece->t_x;
				ptr.piece->t_x = 0;
				ptr.map->t_y++;
				ptr.piece->t_y++;
			}
			else if (ptr.n == 1)
			{
				ptr.map->t_x++;
				ptr.piece->t_x++;
			}
			else if (ptr.n == 2 && ptr.piece->t_x == 0)
			{
				ptr.piece->t_x = ptr.piece->x - 1;
				ptr.map->t_x += ptr.piece->t_x;
				ptr.map->t_y--;
				ptr.piece->t_y--;
			}
			else if (ptr.n == 2)
			{
				ptr.map->t_x--;
				ptr.piece->t_x--;
			}
			find_place(ptr.map, ptr.n, ptr.n == 2 ? 'X' : 'O');
			find_place(ptr.piece, ptr.n, '*');
			// printf("place in map : x = %d | y = %d\n", ptr.map->t_x, ptr.map->t_y);
			// printf("place in piece : x = %d | y = %d\n", ptr.piece->t_x, ptr.piece->t_y);
		}
		// printf("%d %d\n", ptr.x_coord, ptr.y_coord);

		ft_putnbr(ptr.x_result);
		ft_putchar(' ');
		ft_putnbr(ptr.y_result);
		ft_putchar('\n');
	}
	return (0);
}
