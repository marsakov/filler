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

#include <stdio.h>
#include "libft/includes/libft.h"

char	**writer(int x, int y)
{
	char	**map;
	char	*line;
	int		i;

	i = 0;
	map = malloc(sizeof(char*) * y);
	while (get_next_line(0, &line) > 0 && i < y)
	{
		map[i] = malloc(sizeof(char) * (x + 1));
		ft_strcpy(map[i++], line);
		free(line);
	}
	return (map);
}

char	**fill_map(char **map, char **piece)
{
	int		i;

	i = 1;
	while (map[i])
	{
		
	}
	return (map);
}

int		main()
{
	int		n;
	int		x;
	int		y;
	char	**map;
	char	*line;

	while (get_next_line(0, &line) > 0 && ft_strstr(line, "msakovyc.filler]") == NULL)
		free(line);
	n = *(ft_strchr(line,'p') + 1) - '0';
	while (get_next_line(0, &line) > 0 && ft_strstr(line, "Plateau ") == NULL)
		free(line);
	x = ft_atoi(ft_strchr(line, ' '));
	y = ft_atoi(ft_strrchr(line, ' ')) + 1;
	printf("n = %d | x = %d | y = %d\n", n, x, y);
	map = writer(x, y);
	while (get_next_line(0, &line) > 0 && ft_strstr(line, "Piece ") == NULL)
		free(line);
	x = ft_atoi(ft_strchr(line, ' '));
	y = ft_atoi(ft_strrchr(line, ' '));
	fill_map(map, writer(x, y));
	return (0);
}