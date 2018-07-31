/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 18:24:17 by msakovyc          #+#    #+#             */
/*   Updated: 2018/07/31 18:24:22 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

char	**writter(int x, int y, int piece)
{
	char	**map;
	char	*line;
	int		i;

	i = 0;
	map = malloc(sizeof(char*) * y);
	while (i < y && GNL(0, &line) > 0)
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

void	count_elems(t_filler *ptr)
{
	int		i;
	int		j;

	ptr->counter_p = 0;
	ptr->counter_e = 0;
	i = 0;
	while (i < ptr->map->y)
	{
		j = 0;
		while (j < ptr->map->x)
		{
			if (ptr->map->arr[i][j] == 'O')
				(ptr->n == 1 ? ptr->counter_p++ :
					ptr->counter_e++);
			else if (ptr->map->arr[i][j] == 'X')
				(ptr->n == 2 ? ptr->counter_p++ :
					ptr->counter_e++);
			j++;
		}
		i++;
	}
	ptr->player_coord = malloc(sizeof(t_coord) * ptr->counter_p);
	ptr->enemy_coord = malloc(sizeof(t_coord) * ptr->counter_e);
}

void	mem_elems(t_filler *ptr, int p, int e)
{
	t_coord coord;

	coord.y = -1;
	while (++coord.y < ptr->map->y)
	{
		coord.x = -1;
		while (++coord.x < ptr->map->x)
		{
			if (ptr->map->arr[coord.y][coord.x] == 'O')
			{
				if (ptr->n == 1)
					ptr->player_coord[p++] = coord;
				else
					ptr->enemy_coord[e++] = coord;
			}
			else if (ptr->map->arr[coord.y][coord.x] == 'X')
			{
				if (ptr->n == 2)
					ptr->player_coord[p++] = coord;
				else
					ptr->enemy_coord[e++] = coord;
			}
		}
	}
}

void	loop_writter(char *line, t_filler *ptr)
{
	ptr->map->y = ft_atoi(ft_strchr(line, ' '));
	ptr->map->x = ft_atoi(ft_strrchr(line, ' '));
	free(line);
	GNL(0, &line);
	free(line);
	ptr->map->arr = writter(ptr->map->x, ptr->map->y, 0);
	GNL(0, &line);
	ptr->piece->y = ft_atoi(ft_strchr(line, ' '));
	ptr->piece->x = ft_atoi(ft_strrchr(line, ' '));
	ptr->piece->arr = writter(ptr->piece->x, ptr->piece->y, 1);
	count_stars(ptr);
	count_elems(ptr);
	mem_elems(ptr, 0, 0);
	if (!shortcut(ptr, 0, 0))
	{
		ft_putstr("0 0\n");
		exit(0);
	}
}

int		main(void)
{
	char		*line;
	t_filler	ptr;

	ptr.map = (t_data*)malloc(sizeof(t_data));
	ptr.piece = (t_data*)malloc(sizeof(t_data));
	GNL(0, &line);
	ptr.n = *(ft_strchr(line, (int)'p') + 1) - '0';
	free(line);
	while (GNL(0, &line) > 0)
	{
		loop_writter(line, &ptr);
		ft_putnbr(ptr.result.y);
		ft_putchar(' ');
		ft_putnbr(ptr.result.x);
		ft_putchar('\n');
	}
	return (0);
}
