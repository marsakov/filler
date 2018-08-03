/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 17:26:48 by msakovyc          #+#    #+#             */
/*   Updated: 2018/05/25 17:26:50 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <stdio.h>

t_fdf	*create_coordinate(double x, double y, char c)
{
	t_fdf	*elem;

	elem = (t_fdf*)malloc(sizeof(t_fdf));
	elem->x_str = x;
	elem->y_str = y;
	elem->z_str = c == '.' ? 0 : 5;
	elem->x = x;
	elem->y = y;
	elem->z = c == '.' ? 0 : 5;
	elem->x_r = x;
	elem->y_r = y;
	elem->z_r = c == '.' ? 0 : 5;
	if (c == '.')
		elem->color = 0x000000;
	else if (c == 'X' || c == 'x')
		elem->color = 0xb3ffd9;
	else if (c == 'O' || c == 'o')
		elem->color = 0xff9999;
	elem->next = NULL;
	return (elem);
}

t_fdf	*writer(int i, int j, char *line)
{
	int		x;
	int		y;
	t_fdf	*fdf;
	t_fdf	*begin;

	y = 0;
	free(line);
	GNL(0, &line);
	free(line);
	while (y++ < i && GNL(0, &line) == 1)
	{
		x = 0;
		if (y == 1 && ++x == 1)
		{
			fdf = create_coordinate((double)x, (double)y, line[x + 3]);
			begin = fdf;
		}
		while (x++ < j)
		{
			fdf->next = create_coordinate((double)x, (double)y, line[x + 3]);
			fdf = fdf->next;
		}
		free(line);
	}
	return (begin);
}

int 	func(t_window *wnd, char *line)
{
	wnd->fdf = writer(wnd->height, wnd->width, line);
	mlx_clear_window(wnd->mlx_ptr, wnd->win_ptr);
	change_sr(wnd);
	change(wnd);
	drawer(wnd);
	return (1);
}

int		main(void)
{
	char		*line;
	t_window	*wnd;
	t_play		play;

	while (GNL(0, &line) > 0 && !(play.first = ft_strstr(line, "exec p1")))
		free(line);
	while (GNL(0, &line) > 0 && !(play.second = ft_strstr(line, "exec p2")))
		free(line);
	wnd = (t_window*)malloc(sizeof(t_window));
	while (GNL(0, &line) > 0 && !ft_strstr(line, "Plateau "))
		free(line);
	wnd->height = ft_atoi(ft_strchr(line, ' '));
	wnd->width = ft_atoi(ft_strrchr(line, ' '));
	wnd->fdf = writer(wnd->height, wnd->width, line);
	create_wind(wnd);
	while (GNL(0, &line) > 0)
		if (ft_strstr(line, "Plateau "))
			func(wnd, line);
		else
			free(line);
	mlx_key_hook(wnd->win_ptr, deal_key, wnd);
	mlx_loop(wnd->mlx_ptr);
	return (0);
}
