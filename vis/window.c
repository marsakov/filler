/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 20:59:03 by msakovyc          #+#    #+#             */
/*   Updated: 2018/06/11 20:59:05 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf		*jump_to(t_fdf *fdf, int n)
{
	t_fdf *tmp;

	tmp = fdf;
	while (tmp && n--)
		tmp = tmp->next;
	return (tmp);
}

void		drawer(t_window *wnd)
{
	int		t;
	int		i;
	int		j;
	t_fdf	*tmp;

	t = 0;
	tmp = wnd->fdf;
	while (tmp->next && ++t)
	{
		mlx_pixel_put(wnd->mlx_ptr, wnd->win_ptr, tmp->x, tmp->y, tmp->color);

		if (t % wnd->width != 0 && t < wnd->width * (wnd->height - 1) + 1 && !(i = 0))
			while (tmp->y + i++ < (jump_to(tmp, wnd->width))->y && !(j = 0))
				while (tmp->x + j++ < tmp->next->x)
					mlx_pixel_put(wnd->mlx_ptr, wnd->win_ptr, tmp->x + j, tmp->y + i, tmp->color);
		if (t % wnd->width != 0)
			line(wnd, *tmp, *(tmp->next));
		if (t < wnd->width * (wnd->height - 1) + 1)
			line(wnd, *tmp, *(jump_to(tmp, wnd->width)));
		tmp = tmp->next;
	}
	mlx_pixel_put(wnd->mlx_ptr, wnd->win_ptr, tmp->x, tmp->y, tmp->color);
	mlx_string_put(wnd->mlx_ptr, wnd->win_ptr, 100, 1000, 0xFFAABB,
		"zoom: +/-");
	mlx_string_put(wnd->mlx_ptr, wnd->win_ptr, 100, 1020, 0xFFAABB,
		"start position: Enter");
	mlx_string_put(wnd->mlx_ptr, wnd->win_ptr, 100, 1040, 0xFFAABB,
		"rotate: 1/7; 2/8; 3/9");
	mlx_string_put(wnd->mlx_ptr, wnd->win_ptr, 100, 1060, 0xFFAABB,
		"share: < v ^ >");
}

int			deal_key(int key, t_window *wnd)
{
	mlx_clear_window(wnd->mlx_ptr, wnd->win_ptr);
	if (key == 53)
	{
		exit(1);
		return (0);
	}
	if (key == 125 || key == 126)
		wnd->sdvig_y = (key == 125) ? wnd->sdvig_y + 5 : wnd->sdvig_y - 5;
	if (key == 123 || key == 124)
		wnd->sdvig_x = (key == 124) ? wnd->sdvig_x + 5 : wnd->sdvig_x - 5;
	if (key == 69 || key == 78)
		wnd->k = (key == 69) ? wnd->k * 1.025 : wnd->k / 1.025;
	if (key == 89 || key == 83)
		rotate_coordinate(wnd, 1, (key == 89) ? 1 : 0);
	if (key == 91 || key == 84)
		rotate_coordinate(wnd, 2, (key == 91) ? 1 : 0);
	if (key == 92 || key == 85)
		rotate_coordinate(wnd, 3, (key == 92) ? 1 : 0);
	if (key == 76)
		start_coordinate(wnd);
	change_sr(wnd);
	change(wnd);
	drawer(wnd);
	return (0);
}

void	create_wind(t_window *wnd)
{
	wnd->mlx_ptr = mlx_init();
	wnd->win_ptr = mlx_new_window(wnd->mlx_ptr, WIDTH, HEIGHT, "filler");
	wnd->sdvig_x = 0;
	wnd->sdvig_y = 0;
	change_sr(wnd);
	wnd->k = fmin(WIDTH / (wnd->height + 1), HEIGHT / (wnd->width + 1));
	// rotate_coordinate(wnd, 1, 1);
	change(wnd);
	drawer(wnd);
}
