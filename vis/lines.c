/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 18:04:53 by msakovyc          #+#    #+#             */
/*   Updated: 2018/06/16 18:04:56 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	line_x(t_window *wnd, t_fdf fdf1, t_fdf fdf2, int length)
{
	int x;
	int y;
	int d;
	int dx;
	int dy;

	x = fdf1.x;
	y = fdf1.y;
	dx = (fdf2.x - fdf1.x >= 0 ? 1 : -1);
	dy = (fdf2.y - fdf1.y >= 0 ? 1 : -1);
	d = fabs(fdf2.x - fdf1.x) * -1;
	length++;
	while (length--)
	{
		mlx_pixel_put(wnd->mlx_ptr, wnd->win_ptr, x, y, 0xffffff);
		x += dx;
		d += 2 * fabs(fdf2.y - fdf1.y);
		if (d > 0)
		{
			d -= 2 * fabs(fdf2.x - fdf1.x);
			y += dy;
		}
	}
}

static void	line_y(t_window *wnd, t_fdf fdf1, t_fdf fdf2, int length)
{
	int x;
	int y;
	int d;
	int dx;
	int dy;

	x = fdf1.x;
	y = fdf1.y;
	dx = (fdf2.x - fdf1.x >= 0 ? 1 : -1);
	dy = (fdf2.y - fdf1.y >= 0 ? 1 : -1);
	d = fabs(fdf2.y - fdf1.y) * -1;
	length++;
	while (length--)
	{
		mlx_pixel_put(wnd->mlx_ptr, wnd->win_ptr, x, y, 0xffffff);
		y += dy;
		d += 2 * fabs(fdf2.x - fdf1.x);
		if (d > 0)
		{
			d -= 2 * fabs(fdf2.y - fdf1.y);
			x += dx;
		}
	}
}

void		line(t_window *wnd, t_fdf fdf1, t_fdf fdf2)
{
	int length_x;
	int length_y;
	int length;

	length_x = fabs(fdf2.x - fdf1.x);
	length_y = fabs(fdf2.y - fdf1.y);
	length = fmax(length_x, length_y);
	if (length == 0)
		mlx_pixel_put(wnd->mlx_ptr, wnd->win_ptr, fdf1.x, fdf1.y, 0xffffff);
	if (length_y <= length_x)
		line_x(wnd, fdf1, fdf2, length);
	else
		line_y(wnd, fdf1, fdf2, length);
}
