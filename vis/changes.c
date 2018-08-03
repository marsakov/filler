/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 20:58:20 by msakovyc          #+#    #+#             */
/*   Updated: 2018/06/11 20:58:22 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change(t_window *wnd)
{
	t_fdf *p;

	p = wnd->fdf;
	while (p)
	{
		p->x = ((WIDTH / 2) + (p->x_r - wnd->x_sr) * wnd->k) + wnd->sdvig_x;
		p->y = ((HEIGHT / 2) + (p->y_r - wnd->y_sr) * wnd->k) + wnd->sdvig_y;
		p = p->next;
	}
}

void	change_sr(t_window *wnd)
{
	t_fdf	*tmp;
	double	min_x;
	double	max_x;
	double	min_y;
	double	max_y;

	tmp = wnd->fdf;
	max_y = tmp->y_r;
	min_y = tmp->y_r;
	max_x = tmp->x_r;
	min_x = tmp->x_r;
	while (tmp)
	{
		if (tmp->x_r > max_x)
			max_x = tmp->x_r;
		else if (tmp->x_r < min_x)
			min_x = tmp->x_r;
		if (tmp->y_r > max_y)
			max_y = tmp->y_r;
		else if (tmp->y_r < min_y)
			min_y = tmp->y_r;
		tmp = tmp->next;
	}
	wnd->x_sr = (max_x - min_x) / 2;
	wnd->y_sr = (max_y - min_y) / 2;
}

void	start_coordinate(t_window *wnd)
{
	t_fdf	*tmp;

	tmp = wnd->fdf;
	wnd->a = 0.4;
	wnd->b = 0.4;
	wnd->c = 0.4;
	wnd->sdvig_x = 0;
	wnd->sdvig_y = 0;
	wnd->k = fmin(WIDTH / (wnd->height + 1), HEIGHT / (wnd->width + 1));
	while (tmp)
	{
		tmp->x = tmp->x_str;
		tmp->x_r = tmp->x_str;
		tmp->y = tmp->y_str;
		tmp->y_r = tmp->y_str;
		tmp->z = tmp->z_str;
		tmp->z_r = tmp->z_str;
		tmp = tmp->next;
	}
	rotate_coordinate(wnd, 1, 1);
}

void	change_angles(t_window *wnd, int value, int op)
{
	if (value == 1)
		wnd->a = (op) ? wnd->a + 0.1 : wnd->a - 0.1;
	else if (value == 2)
		wnd->b = (op) ? wnd->b + 0.1 : wnd->b - 0.1;
	else
		wnd->c = (op) ? wnd->c + 0.1 : wnd->c - 0.1;
}

void	rotate_coordinate(t_window *wnd, int value, int op)
{
	double	tx;
	double	ty;
	double	tz;
	t_fdf	*p;

	change_angles(wnd, value, op);
	p = wnd->fdf;
	while (p)
	{
		tx = p->x_str;
		ty = p->y_str;
		tz = p->z_str;
		p->y_r = ty * cos(wnd->a) + tz * -sin(wnd->a);
		p->z_r = ty * sin(wnd->a) + tz * cos(wnd->a);
		tz = p->z_r;
		p->x_r = tx * cos(wnd->b) + tz * sin(wnd->b);
		p->z_r = tx * -sin(wnd->b) + tz * cos(wnd->b);
		ty = p->y_r;
		tx = p->x_r;
		p->x_r = tx * cos(wnd->c) + ty * -sin(wnd->c);
		p->y_r = tx * sin(wnd->c) + ty * cos(wnd->c);
		p = p->next;
	}
}
